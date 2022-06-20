#include "SDL.h"



typedef struct{
	SDL_Rect head[7];
	SDL_Rect body_rect[32];
	SDL_Rect body_bkg;
} CalendarView;

void getRects(SDL_Rect *prect, int x, int y, int w, int h, int a, int b, int s, int n)
{
	
	for(int i=0;i<n;i++){
		(*prect).x = x;
		(*prect).y = y;
		(*prect).w = w;
		(*prect).h = h;
	
		x += a;
		y += b;
		prect++;
	}
}

