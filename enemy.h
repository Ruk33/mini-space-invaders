#ifndef ENEMY_H
#define ENEMY_H

#include "world.h"

struct Enemy;

struct Enemy *enemy_spawn
(struct World *world, float x, float y);

void enemy_destroy
(struct Enemy *enemy);

#endif
