#include "collision.h"

int collision_between_units
(struct Unit *a, struct Unit *b)
{
        struct Vector a_position;
        struct Vector b_position;

        if (!a) return 0;
        if (!b) return 0;
        if (a == b) return 0;

        unit_position(a, &a_position);
        unit_position(b, &b_position);

        return (
                a_position.x < b_position.x + unit_width(b) &&
                a_position.x + unit_width(a) > b_position.x &&
                a_position.y < b_position.y + unit_height(b) &&
                a_position.y + unit_height(b) > b_position.y
        );
}
