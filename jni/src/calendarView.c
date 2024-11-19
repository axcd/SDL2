#include<stdlib.h>

#include "SDL.h"
#include "SDL_ttf.h"

#include "calendarView.h"

//获取两者最小值
int min(int a, int b)
{
	return a<b?a:b;
}

Font_Texture *newFont(TTF_Font *font, SDL_Color *textColor)
{
	Font_Texture *pft = (Font_Texture *)malloc(sizeof(Font_Texture));
	pft->str = "";
	pft->font = font;
	pft->textColor = textColor;
	pft->w = 80;
	pft->h = 80;
	return pft;
}

void setFont(Font_Texture *pft, char *str, int w, int h)
{
	pft->str = str;
	pft->w = w;
	pft->h = h;
	return;
}

void drawFont(SDL_Renderer *render, Font_Texture *pft, SDL_Rect frect)
{
	frect.x += (frect.w-pft->w)/2;
	frect.y += (frect.h-pft->h)/2;
	frect.w = pft->w;
	frect.h = pft->h;
	
	SDL_Surface * tmp = TTF_RenderUTF8_Solid(pft->font, pft->str, *(pft->textColor));
	SDL_Texture * fonttex = SDL_CreateTextureFromSurface(render, tmp);
	SDL_RenderCopy(render, fonttex, NULL, &frect);
	SDL_FreeSurface(tmp);
	SDL_DestroyTexture(fonttex);	
}

void destroyFont(Font_Texture *pft)
{
	free(pft);
	pft = NULL;
}

//设置颜色
void setTextColor(SDL_Color *pTextColor, int r, int g, int b)
{
	(*pTextColor).r = r;
	(*pTextColor).g = g;
	(*pTextColor).b = b;
}

//更新rect位置
void setRect(SDL_Rect *prect, int x, int y, int w, int h)
{
	(*prect).x = x;
	(*prect).y = y;
	(*prect).w = w;
	(*prect).h = h;
}

//改变rect
void changeRect(SDL_Rect *prect, int x, int y, int w, int h)
{
	(*prect).x += x;
	(*prect).y += y;
	(*prect).w += w;
	(*prect).h += h;
}

//画字
void text(SDL_Renderer *render, TTF_Font *font, char * str, SDL_Color textColor, SDL_Rect frect, int margin)
{
	//SDL_Rect frect = dstrect;
	int m = min(margin, min(frect.w/2-5, frect.h/2-5));
	frect.x += m;
	frect.y += m;
	frect.w -= m*2;
	frect.h -= m*2;
	
	SDL_Surface * tmp = TTF_RenderUTF8_Solid(font, str, textColor );
	SDL_Texture * fonttex = SDL_CreateTextureFromSurface(render, tmp);
	SDL_RenderCopy(render, fonttex, NULL, &frect);
	SDL_FreeSurface(tmp);
	SDL_DestroyTexture(fonttex);		
}

//画框
void drawrect(SDL_Renderer * render, SDL_Rect * rect, Uint8 r, Uint8 g, Uint8 b,  Uint8 a)
{
	SDL_SetRenderDrawColor(render, r, g, b, a);
	SDL_RenderDrawRect(render, rect);
}

//填充框
void fillrect(SDL_Renderer * render, SDL_Rect * rect, Uint8 r, Uint8 g, Uint8 b,  Uint8 a)
{
	SDL_SetRenderDrawColor(render, r, g, b, a);
	SDL_RenderFillRect(render, rect);
}

