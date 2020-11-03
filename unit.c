#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "texture.h"
#include "unit.h"

struct Unit {
        SDL_Texture *texture;
        char *texture_path;
        struct Vector position;
        float width;
        float height;
        void *data;
};

void unit_move
(struct Unit *unit, float x, float y)
{
        assert(unit);
        unit->position.x = x;
        unit->position.y = y;
}

void unit_position
(struct Unit *unit, struct Vector *position)
{
        assert(unit);
        assert(position);
        position->x = unit->position.x;
        position->y = unit->position.y;
}

float unit_width
(struct Unit *unit)
{
        assert(unit);
        return unit->width;
}

float unit_height
(struct Unit *unit)
{
        assert(unit);
        return unit->height;
}

struct Unit *unit_spawn
(char *texture_path, float x, float y, float w, float h)
{
        assert(texture_path);

        struct Unit *unit = calloc(1, sizeof(struct Unit));
        size_t texture_length = strlen(texture_path);

        unit->texture = NULL;
        unit->data = NULL;
        unit->width = w;
        unit->height = h;

        unit->texture_path = calloc(texture_length + 1, sizeof(char));
        memcpy(unit->texture_path, texture_path, texture_length + 1);

        unit_move(unit, x, y);

        return unit;
}

void unit_set_data
(struct Unit *unit, void *data)
{
        assert(unit);
        unit->data = data;
}

void *unit_data
(struct Unit *unit)
{
        assert(unit);
        return unit->data;
}

static void unit_load_texture
(struct Unit *unit, SDL_Renderer *renderer)
{
        assert(unit);
        assert(renderer);
        if (unit->texture) return;
        unit->texture = load_png_texture(renderer, unit->texture_path);
}

void unit_render
(struct Unit *unit, SDL_Renderer *renderer)
{
        assert(unit);
        assert(renderer);

        SDL_Rect rect;

        rect.w = 32;
        rect.h = 32;
        rect.x = (int) unit->position.x;
        rect.y = (int) unit->position.y;

        unit_load_texture(unit, renderer);
        if (SDL_RenderCopy(renderer, unit->texture, NULL, &rect) == 0) return;
        SDL_Log(SDL_GetError());
}

void unit_destroy
(struct Unit *unit)
{
        assert(unit);
        if (unit->texture) SDL_DestroyTexture(unit->texture);
        free(unit->texture_path);
        free(unit);
}
