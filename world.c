#include <stdlib.h>
#include <assert.h>
#include "unit.h"
#include "event.h"
#include "collision.h"
#include "world.h"

#define MAX_UNITS 50

struct World {
        struct EventManager *event_manager;

        float width;
        float height;

        struct Unit *units[MAX_UNITS];
        int units_count;

        struct Unit *removed_units[MAX_UNITS];
        int removed_units_count;
};

struct World *world_create
(float width, float height)
{
        struct World *world = calloc(1, sizeof(struct World));
        world->event_manager = event_manager_new();
        world->width = width;
        world->height = height;
        world->units_count = 0;
        world->removed_units_count = 0;
        return world;
}

float world_width
(struct World *world)
{
        assert(world);
        return world->width;
}

float world_height
(struct World *world)
{
        assert(world);
        return world->height;
}

struct Unit *world_spawn_unit
(struct World *world, char *texture_path, float x, float y, float w, float h)
{
        assert(world);
        assert(world->units_count < MAX_UNITS);
        assert(texture_path);

        struct Unit *unit = unit_spawn(texture_path, x, y, w, h);
        world->units[world->units_count] = unit;
        world->units_count++;
        return unit;
}

void world_remove_unit
(struct World *world, struct Unit *unit)
{
        assert(world);
        assert(unit);

        for (int i = 0; i < world->removed_units_count; i++) {
                if (world->removed_units[i] == unit) return;
        }

        world->removed_units[world->removed_units_count] = unit;
        world->removed_units_count++;
}

static void world_handle_unit_collision
(struct World *world, struct Unit *unit)
{
        assert(world);
        assert(unit);

        struct Unit *units_colliding[MAX_UNITS];
        int colliding = 0;

        for (int i = 0; i < world->units_count; i++) {
                if (!world->units[i]) continue;
                if (!collision_between_units(unit, world->units[i])) continue;

                units_colliding[colliding] = world->units[i];
                colliding++;
        }

        for (int i = 0; i < colliding; i++) {
                event_trigger_unit_collision(
                        world->event_manager,
                        unit,
                        units_colliding[i]
                );
        }
}

static void world_handle_keypress
(struct World *world, SDL_KeyboardEvent *event)
{
        assert(world);
        assert(event);

        for (int i = 0; i < world->units_count; i++) {
                if (!world->units[i]) continue;

                event_trigger_unit_keypress(
                        world->event_manager,
                        world->units[i],
                        event
                );
        }
}

static void world_handle_collisions
(struct World *world)
{
        for (int i = 0; i < world->units_count; i++) {
                if (!world->units[i]) continue;
                world_handle_unit_collision(world, world->units[i]);
        }
}

static int world_handle_keyboard_events
(struct World *world)
{
        int quit = 0;
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                        quit = 1;
                        break;
                case SDL_KEYDOWN:
                        world_handle_keypress(world, &event.key);
                        break;
                }
        }

        return quit;
}

static void world_handle_removed_units
(struct World *world)
{
        struct Unit *removed_unit = NULL;

        for (int i = 0; i < world->removed_units_count; i++) {
                removed_unit = world->removed_units[i];

                for (int z = 0; z < world->units_count; z++) {
                        if (removed_unit != world->units[z]) continue;
                        world->units[z] = NULL;
                }

                event_trigger_unit_remove(world->event_manager, removed_unit);
                unit_destroy(removed_unit);
        }

        world->removed_units_count = 0;
}

static void world_handle_unit_ticks
(struct World *world, float delta)
{
        for (int i = 0; i < world->units_count; i++) {
                if (!world->units[i]) continue;
                event_trigger_unit_tick(
                        world->event_manager,
                        world->units[i],
                        delta
                );
        }
}

static void world_handle_render
(struct World *world, SDL_Renderer *renderer)
{
        struct Vector position;
        struct Unit *unit = NULL;
        int is_unit_visible = 0;

        if (SDL_RenderClear(renderer) != 0) SDL_Log(SDL_GetError());

        for (int i = 0; i < world->units_count; i++) {
                unit = world->units[i];

                if (!unit) continue;

                unit_position(world->units[i], &position);

                is_unit_visible = (
                        position.x + unit_width(unit) <= world->width &&
                        position.x >= 0 &&
                        position.y + unit_height(unit) <= world->height &&
                        position.y >= 0
                );

                if (!is_unit_visible) continue;

                unit_render(world->units[i], renderer);
        }

        SDL_RenderPresent(renderer);
}

int world_tick
(struct World *world, SDL_Renderer *renderer, float delta)
{
        assert(world);
        assert(renderer);

        int quit = 0;

        world_handle_removed_units(world);
        world_handle_collisions(world);
        quit = world_handle_keyboard_events(world);
        world_handle_unit_ticks(world, delta);
        world_handle_render(world, renderer);

        return quit;
}

void world_on_unit_collision
(struct World *world, struct Unit *unit, collision_callback cb)
{
        assert(world);
        assert(unit);
        assert(cb);
        event_on_unit_collision(world->event_manager, unit, cb);
}

void world_on_unit_tick
(struct World *world, struct Unit *unit, tick_callback cb)
{
        assert(world);
        assert(unit);
        assert(cb);
        event_on_unit_tick(world->event_manager, unit, cb);
}

void world_on_unit_keypress
(struct World *world, struct Unit *unit, keypress_callback cb)
{
        assert(world);
        assert(unit);
        assert(cb);
        event_on_unit_keypress(world->event_manager, unit, cb);
}

void world_on_unit_remove
(struct World *world, struct Unit *unit, remove_unit_callback cb)
{
        assert(world);
        assert(unit);
        assert(cb);
        event_on_unit_remove(world->event_manager, unit, cb);
}
