#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>

SDL_Texture *load_png_texture
(SDL_Renderer *renderer, char *png_file_path);

#endif
