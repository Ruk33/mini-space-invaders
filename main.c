#include <stdio.h>
#include "list.h"

// #include <stdio.h>
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include "world.h"
// #include "player.h"
// #include "enemy.h"

// #define FPS 60
// #define SCREEN_TICK 1000 / FPS
// #define WINDOW_WIDTH 640
// #define WINDOW_HEIGHT 480

// static void init_sdl_or_die()
// {
//         int sdl_initialed = SDL_Init(SDL_INIT_VIDEO) == 0;
//         if (sdl_initialed) return;

//         printf("Failed to initialize SDL. Error: %s\n", SDL_GetError());
//         exit(1);
// }

// static void init_img_or_die()
// {
//         int png_initialized = IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG;
//         if (png_initialized) return;

//         printf("Failed to initialize PNG. Error: %s\n", IMG_GetError());
//         exit(1);
// }

// static SDL_Window *create_main_window_or_die()
// {
//         SDL_Window *window = SDL_CreateWindow(
//                 "Space invaders",
//                 SDL_WINDOWPOS_CENTERED,
//                 SDL_WINDOWPOS_CENTERED,
//                 640,
//                 480,
//                 SDL_WINDOW_OPENGL
//         );

//         if (window) return window;
//         exit(1);
// }

// static void create_enemies
// (struct World *world, int how_many, int start_x, int start_y)
// {
//         float space_between_units = 64;
//         for (int i = 0; i < how_many; i++) {
//                 enemy_spawn(
//                         world,
//                         start_x + space_between_units * i,
//                         start_y
//                 );
//         }
// }

// int main
// (int argc, char *argv[])
// {
//         Uint32 ticks = 0;
//         Uint32 delta = 0;
//         int quit = 0;

//         SDL_Window *window = NULL;
//         SDL_Renderer *renderer = NULL;

//         struct World *world = NULL;
//         int enemies_count = 8;

//         init_sdl_or_die();
//         init_img_or_die();

//         window = create_main_window_or_die();

//         renderer = SDL_CreateRenderer(
//                 window,
//                 -1,
//                 SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
//         );
//         SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);

//         world = world_create(WINDOW_WIDTH, WINDOW_HEIGHT);
//         player_spawn(world, WINDOW_WIDTH / 2, WINDOW_HEIGHT - 32);
//         create_enemies(world, enemies_count, 0, 0);

//         while (!quit) {
//                 delta = SDL_GetTicks() - ticks;
//                 if (delta < SCREEN_TICK) continue;
//                 quit = world_tick(world, renderer, ((float) delta) / 1000);
//                 ticks = SDL_GetTicks();
//         }

//         return 0;
// }

int main
(int argc, char **argv)
{
        struct List *list = list_create();
        struct List *iterator = NULL;
        int *value = NULL;

        int a = 42;
        int b = 24;
        int c = 33;

        list_add(list, &a);
        list_add(list, &b);
        list_add(list, &c);

        iterator = list;

        do {
                value = list_value(iterator);
                printf("%d\n", *value);
                iterator = list_next(iterator);
        } while (iterator);

        list_remove(list, &b);

        iterator = list;

        do {
                value = list_value(iterator);
                printf("%d\n", *value);
                iterator = list_next(iterator);
        } while (iterator);
}
