/**
 * This software is the simplest program transplant SDL2 to Android platform.
 * It shows a BMP file on the screen.
 */

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "log.h"

int main(int argc, char *argv[]) {
    struct SDL_Window *window = NULL;
    struct SDL_Renderer *render = NULL;

    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("SDL HelloWorld!", 100, 100, 640, 480,
            SDL_WINDOW_SHOWN);
    
    render = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    TTF_Init();
    SDL_Color textColor = { 255, 255, 255 };
    TTF_Font *font = TTF_OpenFont( "ttf/lazy.ttf", 200 );
    SDL_Surface *text = TTF_RenderText_Solid( font, "HELLO", textColor );  
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface( render, text );
    
    SDL_RenderClear(render);
   
    SDL_Rect src = { 0, 0, text->w, text->h };
    SDL_Rect dest = { 100, 500, text->w, text->h };
    SDL_RenderCopy( render, text_texture, &src, &dest );
    
    SDL_RenderPresent(render);

    SDL_Delay(10000);
    
    SDL_FreeSurface(text);
    SDL_DestroyTexture(text_texture);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
