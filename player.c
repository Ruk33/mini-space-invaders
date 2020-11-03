#include <stdlib.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include "unit.h"
#include "player.h"

#define PLAYER_MOVEMENT 15
#define BULLET_MOVEMENT 240

struct Player {
        struct World *world;
        struct Unit *unit;
        struct Unit *bullet;
};

static void player_move_left
(struct Player *player)
{
        assert(player);

        struct Vector position;
        unit_position(player->unit, &position);
        unit_move(player->unit, position.x - PLAYER_MOVEMENT, position.y);
}

static void player_move_right
(struct Player *player)
{
        assert(player);

        struct Vector position;
        unit_position(player->unit, &position);
        unit_move(player->unit, position.x + PLAYER_MOVEMENT, position.y);
}

static float player_safe_x
(struct Player *player, float x)
{
        assert(player);

        float max_width = world_width(player->world);
        float width = unit_width(player->unit);
        if (x < 0) return 0;
        if (x + width > max_width) return max_width - width;
        return x;
}

static void player_handle_collision
(struct Player *player)
{
        assert(player);
        float safe_x = 0;
        struct Vector position;

        unit_position(player->unit, &position);

        safe_x = player_safe_x(player, position.x);
        unit_move(player->unit, safe_x, position.y);
}

void player_destroy
(struct Player *player)
{
        if (player) free(player);
}

static void player_bullet_movement_handler
(struct Unit *bullet, float delta)
{
        struct Player *player = NULL;
        struct Vector position;
        float movement = BULLET_MOVEMENT * delta;

        if (!bullet) return;

        player = unit_data(bullet);

        if (!player) return;

        unit_position(bullet, &position);
        unit_move(bullet, position.x, position.y - movement);

        if (position.y < 0) world_remove_unit(player->world, bullet);
}

static void player_bullet_collision_handler
(struct Unit *bullet, struct Unit *target)
{
        struct Player *player = unit_data(bullet);

        if (player->unit == target) return;

        world_remove_unit(player->world, target);
        world_remove_unit(player->world, bullet);
}

static void player_bullet_remove_handler
(struct Unit *bullet)
{
        struct Player *player = NULL;

        if (!bullet) return;

        player = unit_data(bullet);

        if (!player) return;

        player->bullet = NULL;
}

static void player_shot
(struct Player *player)
{
        assert(player);

        struct Vector position;
        float width_bullet = 32;
        float height_bullet = 32;

        if (player->bullet) return;

        unit_position(player->unit, &position);

        player->bullet = world_spawn_unit(
                player->world,
                "resources/shot.png",
                position.x,
                position.y - unit_height(player->unit),
                width_bullet,
                height_bullet
        );

        unit_set_data(player->bullet, player);

        world_on_unit_tick(
                player->world,
                player->bullet,
                player_bullet_movement_handler
        );

        world_on_unit_collision(
                player->world,
                player->bullet,
                player_bullet_collision_handler
        );

        world_on_unit_remove(
                player->world,
                player->bullet,
                player_bullet_remove_handler
        );
}

static void player_keypress_handler
(struct Unit *unit, SDL_KeyboardEvent *event)
{
        struct Player *player = NULL;
        int is_left = 0;
        int is_right = 0;
        int is_space = 0;

        if (!unit) return;
        if (!event) return;

        player = unit_data(unit);

        if (!player) return;

        is_left = event->keysym.sym == SDLK_LEFT;
        is_right = event->keysym.sym == SDLK_RIGHT;
        is_space = event->keysym.sym == SDLK_SPACE;

        if (is_left) player_move_left(player);
        if (is_right) player_move_right(player);
        if (is_space) player_shot(player);

        player_handle_collision(player);
}

struct Player *player_spawn
(struct World *world, float x, float y)
{
        assert(world);

        struct Player *player = calloc(1, sizeof(struct Player));
        float width = 32;
        float height = 32;

        player->world = world;
        player->unit = world_spawn_unit(
                world,
                "resources/player.png",
                x,
                y,
                width,
                height
        );
        player->bullet = NULL;

        unit_set_data(player->unit, player);
        world_on_unit_keypress(world, player->unit, player_keypress_handler);

        return player;
}
