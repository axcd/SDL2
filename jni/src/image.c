/**
 * This software is the simplest program transplant SDL2 to Android platform.
 * It shows a BMP file on the screen.
 */

#include "SDL.h"
#include "SDL_log.h"
#include "SDL_main.h"
#include "log.h"

int main(int argc, char *argv[]) {
    struct SDL_Window *window = NULL;
    struct SDL_Renderer *render = NULL;
    struct SDL_Surface *bmp = NULL;
    struct SDL_Texture *texture = NULL;

    char *filepath = "image/test.bmp";

    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("SDL HelloWorld!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    bmp = SDL_LoadBMP(filepath);

    texture = SDL_CreateTextureFromSurface(render, bmp);
    SDL_FreeSurface(bmp);

    SDL_RenderClear(render);
    SDL_RenderCopy(render, texture, NULL, NULL);
    SDL_RenderPresent(render);

    SDL_Delay(10000);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    //Quit SDL
    SDL_Quit();
    return 0;
}
