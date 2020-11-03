#ifndef UNIT_H
#define UNIT_H

#include <SDL2/SDL.h>
#include "vector.h"

struct Unit;

struct Unit *unit_spawn
(char *texture_path, float x, float y, float w, float h);

void unit_set_data
(struct Unit *unit, void *data);

void *unit_data
(struct Unit *unit);

void unit_move
(struct Unit *unit, float x, float y);

void unit_position
(struct Unit *unit, struct Vector *position);

float unit_width
(struct Unit *unit);

float unit_height
(struct Unit *unit);

void unit_render
(struct Unit *unit, SDL_Renderer *renderer);

void unit_destroy
(struct Unit *unit);

#endif
