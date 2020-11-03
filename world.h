#ifndef WORLD_H
#define WORLD_H

#include <SDL2/SDL.h>
#include "unit.h"
#include "event.h"

struct World;

struct World *world_create
(float width, float height);

float world_width
(struct World *world);

float world_height
(struct World *world);

struct Unit *world_spawn_unit
(struct World *world, char *texture_path, float x, float y, float w, float h);

void world_remove_unit
(struct World *world, struct Unit *unit);

int world_tick
(struct World *world, SDL_Renderer *renderer, float delta);

void world_on_unit_collision
(struct World *world, struct Unit *unit, collision_callback cb);

void world_on_unit_tick
(struct World *world, struct Unit *unit, tick_callback cb);

void world_on_unit_keypress
(struct World *world, struct Unit *unit, keypress_callback cb);

void world_on_unit_remove
(struct World *world, struct Unit *unit, remove_unit_callback cb);

#endif
