#include<stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "calendarh.c"
#include "calendar.c"

//窗口变量
SDL_Window* window = NULL;

//渲染变量
SDL_Renderer* render = NULL;

//背景图
SDL_Surface *bkg = NULL;
SDL_Texture *bkgtex = NULL;

//字体
TTF_Font *font = NULL;	
SDL_Surface *tmp = NULL;
SDL_Texture *fonttex = NULL;
	
//按键动作变量
SDL_Event event;

//变量日期
int year = 2022;
int month = 6;
int day = 18;

//获取两者最小值
int min(int a, int b)
{
	return a<b?a:b;
}

//更新rect
void changeRect(SDL_Rect *prect, int x, int y, int w, int h)
{
	(*prect).x += x;
	(*prect).y += y;
	(*prect).w += w;
	(*prect).h += h;
}

//画字
void text(SDL_Renderer *render, char * str, SDL_Color textColor, SDL_Rect dstrect, int margin)
{
	SDL_Rect frect = dstrect;
	int m = min(margin, min(frect.w/2-5, frect.h/2-5));
	frect.x += m;
	frect.y += m;
	frect.w -= m*2;
	frect.h -= m*2;
	tmp = TTF_RenderUTF8_Solid( font, str, textColor );
	fonttex = SDL_CreateTextureFromSurface(render, tmp);
	SDL_RenderCopy(render, fonttex, NULL, &frect);
	SDL_FreeSurface(tmp);
	SDL_DestroyTexture(fonttex);		
}

//画框
void drawrect(SDL_Renderer * renderer, SDL_Rect * rect, Uint8 r, Uint8 g, Uint8 b,  Uint8 a)
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

//main
int main(int argc, char *argv[]){

	//sdl初始化
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	//创建窗口
	window = SDL_CreateWindow("Canlendar SDL", 
								SDL_WINDOWPOS_CENTERED, 
								SDL_WINDOWPOS_CENTERED,
								1080, 2480, 
								SDL_WINDOW_SHOWN);

	/*创建渲染器*/
	render = SDL_CreateRenderer(window, -1,0);
	
	//创建字体
	font = TTF_OpenFont("GB2312.ttf", 100);
	
	//矩形
	const SDL_Rect rect = { 90,250,120,140 };
	//游标
	SDL_Rect rect0 = { 110,120,20,20 };
	//标题框
	SDL_Rect rect1 = { 430,80,220,100 };
	//背景框
	SDL_Rect rect2 = { 90,400,900,890 };
	SDL_Rect rect01, rect02;
	//calendarView
	//CalendarView *pcv = (CalendarView *)malloc(sizeof(CalendarView));
	//getRects((SDL_Rect *)pcv,90,250,120,140,130,150,0,7);
	
	//记录被点击位置
	char flag = 0;
	int x = 0, y = 0, quit = 1;
	
	//滑动距离
	int x1=0,x2=0,xx=0;
	
	//获取当前年月
	date();
	year = now_year;
	month = now_month;
	day = now_month;
	
	//启动画面
  	bkg = IMG_Load("bkg.jpg");
  	if (bkg == NULL) {
   	 	return 1;
  	}
 	bkgtex = SDL_CreateTextureFromSurface(render, bkg);
    SDL_FreeSurface(bkg);
	SDL_SetTextureAlphaMod(bkgtex, 0);
    SDL_RenderCopy(render, bkgtex, NULL, NULL);
  	SDL_RenderPresent(render);
	
	//主循环
	while (quit){
		
		//保证使用时时间跳转
		date();
		
		//计算开始结束
		int s=dayOftheWeekThisYearQueryMonth(year,month);
		int e=monthDays[month]+1;
		int k = (e+s-1)%7==0?(e+s-1)/7:(e+s-1)/7+1;
		rect2.h = k * 150 - 10;
		
		//绘制大背景
		SDL_RenderClear(render);
		SDL_RenderCopy(render, bkgtex, NULL, NULL);
		
		//画背景墙
		SDL_Rect brect =rect2;
		changeRect(&brect, xx, 0, 0, 0);
		fillrect(render, &brect, 200, 200, 250, 0);
		
		//画标题
		SDL_Color textColor = { 125, 60, 255 };
		char ss[20]={'0'};
		text(render, datestr(year, month, ss, "."), textColor, rect1, 15);
		
		//画周几
		SDL_Color textColor3 = { 250, 0, 250 };
		rect01 = rect;
		changeRect(&rect01, xx, 0, 0, 0);
		for(int i=0;i<7;i++){
			fillrect(render, &rect01, 100, 200, 50, 0);
			text(render, week[i], textColor3, rect01, 20);
			changeRect(&rect01, 130, 0, 0, 0);
		}
		
		//画数字
		SDL_Color textColor4 = { 0, 100, 255 };
		rect02 = rect;
		changeRect(&rect02, xx+s*130, 150, 0, 0);
		for(int i=1;i<e;i++){
			drawrect(render, &rect02, 200, 0, 250, 0);
			if(year==now_year && month==now_month && i==now_day)
			{
				fillrect(render, &rect02, 250, 150, 200, 0);
				SDL_Color textColor = { 255, 0, 0 };
				text(render, days[i], textColor, rect02, 30);
			}else{
				text(render, days[i], textColor4, rect02, 30);
			}
			changeRect(&rect02, 130, 0, 0, 0);
			//修正
			if((i+s)%7==0)
			{
				changeRect(&rect02, -7*130, 0, 0, 0);
				changeRect(&rect02, 0, 150, 0, 0);
			}
		}
		
		//画点击效果
		if(flag==1){
			rect0.x = x;
			rect0.y = y;
			fillrect(render, &rect0, 250, 0, 250, 0);
		}
		
		if(flag==2){
			if(xx<-100){
				xx -= 10;
				if(xx<-1000) {
					nextmonth(&year, &month);
					xx=1000;
					flag=3;
				}
			}else if(xx>100){
				xx += 10;
				if(xx>1000){
					lastmonth(&year, &month); 
					xx=-1000;
					flag=3;
				} 
			}else{
				xx=0;
			}
		}
		
		if(flag==3){
			if(xx>0)
			{
				xx -= 10;
			}else if(xx<0){
				xx += 10;
			}else{
				flag = 0;
			}
		}
		
		//显示
		SDL_RenderPresent(render);
		
		//获取事件
		while (SDL_PollEvent(&event)) {
      
			//获取按键动作，按esc退出
			if (event.type == SDL_QUIT) {
				quit = 0;
				break;
			}

			if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				x1 = event.button.x;
			}
			if(event.type == SDL_MOUSEMOTION){
				x = event.button.x;
				y = event.button.y;
				xx = x -x1;
				flag = 1;
			}
			
			//抬起动作
			if(event.type == SDL_MOUSEBUTTONUP){
				flag = 2;
				break;
			}
		}
	}
	
	//释放
	SDL_DestroyTexture(bkgtex);	
	
	//关闭font
    TTF_CloseFont( font );
	
	//释放渲染器
	SDL_DestroyRenderer(render);

	//关闭窗口
	SDL_DestroyWindow(window);

	//退出
	SDL_Quit();
	
	return 0;

}
