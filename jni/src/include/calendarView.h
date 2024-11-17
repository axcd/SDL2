#ifndef CALENDARVIEW_h_
#define CALENDARVIEW_h_

#include<stdlib.h>
#include "SDL.h"
#include "SDL_ttf.h"

typedef struct{
	char * str;
	TTF_Font *font;
	SDL_Color *textColor;
	int w;
	int h;
} Font_Texture;

//获取两者最小值
int min(int a, int b);

Font_Texture *newFont(TTF_Font *font, SDL_Color *textColor);

void setFont(Font_Texture *pft, char *str, int w, int h);

void drawFont(SDL_Renderer *render, Font_Texture *pft, SDL_Rect frect);

void destroyFont(Font_Texture *pft);

//设置颜色
void setTextColor(SDL_Color *pTextColor, int r, int g, int b);

//更新rect
void setRect(SDL_Rect *prect, int x, int y, int w, int h);

//改变rect
void changeRect(SDL_Rect *prect, int x, int y, int w, int h);

//画字
void text(SDL_Renderer *render, TTF_Font *font, char * str, SDL_Color textColor, SDL_Rect frect, int margin);

//画框
void drawrect(SDL_Renderer * render, SDL_Rect * rect, Uint8 r, Uint8 g, Uint8 b,  Uint8 a);

//填充框
void fillrect(SDL_Renderer * render, SDL_Rect * rect, Uint8 r, Uint8 g, Uint8 b,  Uint8 a);

#endif   /* CALENDARVIEW_h_ */
