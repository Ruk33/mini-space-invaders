#include <stdlib.h>
#include <assert.h>
#include "event.h"

struct EventManager {
        collision_callback unit_collision_cbs[50];
        struct Unit *unit_collision_units[50];
        int unit_collision_cb_count;

        tick_callback unit_tick_cbs[50];
        struct Unit *unit_tick_units[50];
        int unit_tick_cb_count;

        keypress_callback unit_keypress_cbs[50];
        struct Unit *unit_keypress_units[50];
        int unit_keypress_cb_count;

        remove_unit_callback unit_remove_cbs[50];
        struct Unit *unit_remove_units[50];
        int unit_remove_cb_count;
};

struct EventManager *event_manager_new()
{
        return calloc(1, sizeof(struct EventManager));
}

void event_on_unit_collision
(struct EventManager *manager, struct Unit *unit, collision_callback cb)
{
        assert(manager);
        assert(unit);
        assert(cb);
        manager->unit_collision_cbs[manager->unit_collision_cb_count] = cb;
        manager->unit_collision_units[manager->unit_collision_cb_count] = unit;
        manager->unit_collision_cb_count++;
}

void event_on_unit_tick
(struct EventManager *manager, struct Unit *unit, tick_callback cb)
{
        assert(manager);
        assert(unit);
        assert(cb);
        manager->unit_tick_cbs[manager->unit_tick_cb_count] = cb;
        manager->unit_tick_units[manager->unit_tick_cb_count] = unit;
        manager->unit_tick_cb_count++;
}

void event_on_unit_keypress
(struct EventManager *manager, struct Unit *unit, keypress_callback cb)
{
        assert(manager);
        assert(unit);
        assert(cb);
        manager->unit_keypress_cbs[manager->unit_keypress_cb_count] = cb;
        manager->unit_keypress_units[manager->unit_keypress_cb_count] = unit;
        manager->unit_keypress_cb_count++;
}

void event_on_unit_remove
(struct EventManager *manager, struct Unit *unit, remove_unit_callback cb)
{
        assert(manager);
        assert(unit);
        assert(cb);
        manager->unit_remove_cbs[manager->unit_remove_cb_count] = cb;
        manager->unit_remove_units[manager->unit_remove_cb_count] = unit;
        manager->unit_remove_cb_count++;
}

void event_trigger_unit_collision
(struct EventManager *manager, struct Unit *a, struct Unit *b)
{
        assert(manager);
        assert(a);
        assert(b);
        for (int i = 0; i < manager->unit_collision_cb_count; i++) {
                if (manager->unit_collision_units[i] != a) continue;
                manager->unit_collision_cbs[i](a, b);
        }
}

void event_trigger_unit_tick
(struct EventManager *manager, struct Unit *unit, float delta)
{
        assert(manager);
        assert(unit);
        for (int i = 0; i < manager->unit_tick_cb_count; i++) {
                if (manager->unit_tick_units[i] != unit) continue;
                manager->unit_tick_cbs[i](unit, delta);
        }
}

void event_trigger_unit_keypress
(struct EventManager *manager, struct Unit *unit, SDL_KeyboardEvent *event)
{
        assert(manager);
        assert(unit);
        assert(event);
        for (int i = 0; i < manager->unit_keypress_cb_count; i++) {
                if (manager->unit_keypress_units[i] != unit) continue;
                manager->unit_keypress_cbs[i](unit, event);
        }
}

void event_trigger_unit_remove
(struct EventManager *manager, struct Unit *unit)
{
        assert(manager);
        assert(unit);
        for (int i = 0; i < manager->unit_remove_cb_count; i++) {
                if (manager->unit_remove_units[i] != unit) continue;
                manager->unit_remove_cbs[i](unit);
        }
}
