#ifndef EVENT_H
#define EVENT_H

#include "unit.h"

struct EventManager;

typedef void (* collision_callback)
(struct Unit *a, struct Unit *b);

typedef void (* tick_callback)
(struct Unit *unit, float delta);

typedef void (* keypress_callback)
(struct Unit *unit, SDL_KeyboardEvent *event);

typedef void (* remove_unit_callback)
(struct Unit *unit);

struct EventManager *event_manager_new();

void event_on_unit_collision
(struct EventManager *manager, struct Unit *unit, collision_callback cb);

void event_on_unit_tick
(struct EventManager *manager, struct Unit *unit, tick_callback cb);

void event_on_unit_keypress
(struct EventManager *manager, struct Unit *unit, keypress_callback cb);

void event_on_unit_remove
(struct EventManager *manager, struct Unit *unit, remove_unit_callback cb);

void event_trigger_unit_collision
(struct EventManager *manager, struct Unit *a, struct Unit *b);

void event_trigger_unit_tick
(struct EventManager *manager, struct Unit *unit, float delta);

void event_trigger_unit_keypress
(struct EventManager *manager, struct Unit *unit, SDL_KeyboardEvent *event);

void event_trigger_unit_remove
(struct EventManager *manager, struct Unit *unit);

#endif
