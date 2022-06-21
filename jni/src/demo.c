#include<stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "calendarView.c"
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
	
//按键动作变量
SDL_Event event;

//变量日期
int year = 2022;
int month = 6;
int day = 18;

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
	SDL_Color textColor = { 125, 60, 255 };
	
	//矩形
	SDL_Rect rect = { 90,250,120,140 };
	
	//记录被点击位置
	char flag = 0;
	int x = 0, y = 0, quit = 1;
	
	//滑动距离
	int x1=0, xx=0;
	
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
		int h = k * 150 - 10;
		
		//绘制大背景
		SDL_RenderClear(render);
		SDL_RenderCopy(render, bkgtex, NULL, NULL);
			
		//画标题
		setRect(&rect, 430, 80, 220, 100);
		setTextColor(&textColor, 125, 60, 255);
		char ss[20]={'0'};
		text(render, font, datestr(year, month, ss, "."), textColor, rect, 15);
		
		//画日历背景
		setRect(&rect, 90, 400, 900, h);
		changeRect(&rect, xx, 0, 0, 0);
		fillrect(render, &rect, 200, 200, 250, 0);
	
		//画周几
		setTextColor(&textColor, 250, 0, 250);
		setRect(&rect, 90, 250, 120, 140);
		changeRect(&rect, xx, 0, 0, 0);
		for(int i=0;i<7;i++){
			fillrect(render, &rect, 100, 200, 50, 0);
			text(render, font, week[i], textColor, rect, 20);
			changeRect(&rect, 130, 0, 0, 0);
		}
		
		//画数字
		setRect(&rect, 90, 250, 120, 140);
		changeRect(&rect, xx+s*130, 150, 0, 0);
		for(int i=1;i<e;i++){
			drawrect(render, &rect, 200, 0, 250, 0);
			if(year==now_year && month==now_month && i==now_day)
			{
				fillrect(render, &rect, 250, 150, 200, 0);
				setTextColor(&textColor, 250, 0, 0);
				text(render, font, days[i], textColor, rect, 30);
			}else{
				setTextColor(&textColor, 0, 50, 250);
				text(render, font, days[i], textColor, rect, 30);
			}
			changeRect(&rect, 130, 0, 0, 0);
			//修正
			if((i+s)%7==0)
			{
				changeRect(&rect, -7*130, 0, 0, 0);
				changeRect(&rect, 0, 150, 0, 0);
			}
		}
		
		//画点击效果
		if(flag==1){
			setRect(&rect, x, y, 20, 20);
			fillrect(render, &rect, 250, 0, 250, 0);
		}
		
		//手滑动效果
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
		
		//自动滑动效果
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
