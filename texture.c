#include <assert.h>
#include "png.h"
#include "texture.h"

SDL_Texture *load_png_texture
(SDL_Renderer *renderer, char *png_file_path)
{
        assert(renderer);
        assert(png_file_path);

        SDL_Surface *surface = png_load(png_file_path);
        SDL_Texture *texture = NULL;

        assert(surface);

        texture = SDL_CreateTextureFromSurface(renderer, surface);

        if (!texture) {
                printf(
                        "Unable to create texture for %s. Error: %s",
                        png_file_path,
                        SDL_GetError()
                );
        }

        SDL_FreeSurface(surface);

        return texture;
}
