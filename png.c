#include <assert.h>
#include <SDL2/SDL_image.h>
#include "png.h"

SDL_Surface *png_load
(char *path)
{
        assert(path);
        SDL_Surface *image = IMG_Load(path);

        if (!image) {
                printf("Failed to load %s. Error: %s\n", path, IMG_GetError());
                return NULL;
        }

        return image;
}
