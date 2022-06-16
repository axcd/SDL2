#include <SDL.h>

int main(int rgc,char**argv)
{
SDL_Event e;
SDL_Window* win=SDL_CreateWindow("567",1,1,100,100,SDL_WINDOW_SHOWN);
SDL_Renderer* ren=SDL_CreateRenderer(win,-1,0);
SDL_Texture* tex=SDL_CreateTexture(ren,0,100,100,0);
SDL_SetRenderDrawColor(ren,0,255,0,0);
SDL_RenderClear(ren);
SDL_RenderPresent(ren);
SDL_Surface* sur;
while(1)
{
SDL_PollEvent(&e);
switch(e.type)
{
case SDL_FINGERMOTION:
 SDL_SetRenderDrawColor(ren,0,e.tfinger.x*200,e.tfinger.y*200,0);
SDL_RenderClear(ren);
SDL_RenderPresent(ren);
break;
case SDL_QUIT:
 exit(0);
break;
}
}
}
