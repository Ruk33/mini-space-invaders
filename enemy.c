#include <stdlib.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include "unit.h"
#include "enemy.h"

#define ENEMY_MOVEMENT 180

struct Enemy {
        struct Unit *unit;
        int x_toggle;
        int is_moving_right;
};

static void enemy_toggle_direction
(struct Enemy *enemy)
{
        struct Vector position;
        struct Vector new_position;

        if (!enemy) return;

        unit_position(enemy->unit, &position);

        new_position.y = position.y + unit_height(enemy->unit);
        new_position.x = (
                enemy->is_moving_right ?
                enemy->x_toggle - unit_width(enemy->unit) :
                0
        );

        unit_move(enemy->unit, new_position.x, new_position.y);

        enemy->is_moving_right = !enemy->is_moving_right;
}

static void enemy_handle_collision
(struct Enemy *enemy)
{
        struct Vector position;
        int collides = 0;

        if (!enemy) return;

        unit_position(enemy->unit, &position);

        collides = (
                position.x < 0 ||
                position.x + unit_width(enemy->unit) > enemy->x_toggle
        );

        if (!collides) return;

        enemy_toggle_direction(enemy);
}

static void enemy_move
(struct Enemy *enemy, float delta)
{
        struct Vector position;
        int moving_right = 0;
        float movement = ENEMY_MOVEMENT * delta;
        float new_x = 0;

        if (!enemy) return;

        moving_right = enemy->is_moving_right;

        unit_position(enemy->unit, &position);

        new_x = moving_right ? position.x + movement : position.x - movement;
        unit_move(enemy->unit, new_x, position.y);
}

void enemy_destroy
(struct Enemy *enemy)
{
        if (enemy) free(enemy);
}

static void enemy_tick_handler
(struct Unit *unit, float delta)
{
        struct Enemy *enemy = NULL;

        if (!unit) return;

        enemy = unit_data(unit);
        if (!enemy) return;

        enemy_move(enemy, delta);
        enemy_handle_collision(enemy);
}

static void enemy_remove_handler
(struct Unit *unit)
{
        struct Enemy *enemy = NULL;

        if (!unit) return;

        enemy = unit_data(unit);

        if (!enemy) return;

        enemy_destroy(enemy);
}

struct Enemy *enemy_spawn
(struct World *world, float x, float y)
{
        assert(world);

        struct Enemy *enemy = calloc(1, sizeof(struct Enemy));
        float width = 32;
        float height = 32;

        enemy->unit = world_spawn_unit(
                world,
                "resources/enemy.png",
                x,
                y,
                width,
                height
        );
        enemy->x_toggle = world_width(world);
        enemy->is_moving_right = 1;

        unit_set_data(enemy->unit, enemy);
        world_on_unit_tick(world, enemy->unit, enemy_tick_handler);
        world_on_unit_remove(world, enemy->unit, enemy_remove_handler);

        return enemy;
}
