#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "world.h"

struct Player;

struct Player *player_spawn
(struct World *world, float x, float y);

void player_destroy
(struct Player *player);

#endif
