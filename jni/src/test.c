/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

//Screen dimension constants
int SCREEN_WIDTH = 1080;
int SCREEN_HEIGHT = 2400;


int main( int argc, char* args[] )
{
	
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	Mix_Chunk *low = NULL;
	
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface( window );
			
			//Fill the surface white
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x0F, 0xFF, 0xF0 ) );
			
			//Update the surface
			SDL_UpdateWindowSurface( window );
		
			Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
			
			Mix_Music *sound = Mix_LoadMUS("test.mp3");		
			low = Mix_LoadWAV( "low.wav" );
			
			Mix_PlayMusic(sound, 1);	

			while(1==1){
				Mix_PlayChannel( -1, low, 0 );
				SDL_Delay( 1000 );
			}		

			//Wait two seconds
			SDL_Delay( 20000 );
		}
	}

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
