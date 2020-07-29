/**
 * This software is the simplest program transplant SDL2_mixer to Android platform.
 */

#include "SDL.h"
#include "SDL_mixer.h"

int main(int argc, char *argv[]) {
    
    SDL_Init(SDL_INIT_EVERYTHING);

    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 1024 );
    
    Mix_Chunk* sound = Mix_LoadWAV("audio/beat.wav");  
    int channel = Mix_PlayChannel( -1, sound, 10 );
    Mix_Pause( channel );
    Mix_Resume( channel );

    SDL_Delay(10000);
    
    Mix_FreeChunk( sound );
    Mix_CloseAudio();
    Mix_Quit();

    SDL_Quit();
    return 0;
}
