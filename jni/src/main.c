#include<stdio.h>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "calendar.h"
#include "calendarView.h"

//窗口变量
SDL_Window* window = NULL;

//渲染变量
SDL_Renderer* render = NULL;

//背景图
SDL_Surface *bkg = NULL;
SDL_Texture *bkgtex = NULL;

//字体
TTF_Font *font = NULL;
Font_Texture *pFT = NULL; 
	
//按键动作变量
SDL_Event event;

//变量日期
int year = 2022;
int month = 6;
int day = 18;

//记录今天
int now_year = 2022;
int now_month = 6;
int now_day = 18;

//存放每个月月份天数的数组，这是全局变量
int monthDays[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};


char *week[7] = {"日", "一", "二", "三", "四", "五", "六"};
//月天数
char *days[32] = {"0","01","02","03","04","05","06","07","08","09",
				"10","11","12","13","14","15","16","17","18","19",
				"20","21","22","23","24","25","26","27","28","29",
				"30","31"};

int init(){
	
	//启动画面
  	bkg = IMG_Load("bkg.jpg");
  	if (bkg == NULL) {
   	 	return 1;
  	}
	
 	bkgtex = SDL_CreateTextureFromSurface(render, bkg);
    SDL_FreeSurface(bkg);
	SDL_SetTextureAlphaMod(bkgtex, 0);
    SDL_RenderCopy(render, bkgtex, NULL, NULL);
  	//SDL_RenderPresent(render);
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
	font = TTF_OpenFont("GB2312.ttf", 200);
	SDL_Color textColor = { 125, 60, 255 };
	pFT = newFont(font, &textColor);
	
	//矩形
	SDL_Rect rect = { 90,250,120,140 };
	
	//记录被点击位置
	char flag = 0;
	int x = 0, y = 0, quit = 1;
	
	//滑动距离
	int x1=0, xx=0, a=0, b=0, z=50;
	
	//帧
	int fps = 0;
	
	//获取当前年月
	date(&now_year, &now_month, &now_day);
	year = now_year;
	month = now_month;
	//day = now_day;
	
	init();
	//主循环
	while (quit){
		
		//保证使用时时间跳转
		date(&now_year, &now_month, &now_day);
		
		//计算开始结束
		int s=dayOftheWeekThisYearQueryMonth(year,month);
		int e=monthDays[month]+1;
		int k = (e+s-1)%7==0?(e+s-1)/7:(e+s-1)/7+1;
		int h = k * 150 - 10;
		
		//绘制大背景
		//SDL_RenderClear(render);
		SDL_RenderCopy(render, bkgtex, NULL, NULL);
			
		//画标题
		char ss[20]={'0'};
		setRect(&rect, 430, 80, 220, 100);
		setTextColor(&textColor, 125, 60, 255);
		setFont( pFT, datestr(year, month, ss, "."), 200, 90);
		drawFont(render, pFT, rect);
		//text(render, font, datestr(year, month, ss, "."), textColor, rect, 15);
		
		//画日历背景
		setRect(&rect, 80, 390, 920, h+20);
		changeRect(&rect, xx, 0, 0, 0);
		fillrect(render, &rect, 255, 255, 255, 255);

		//画周几
		setRect(&rect, 90, 240, 120, 140);
		changeRect(&rect, xx, 0, 0, 0);
		setTextColor(&textColor, 250, 0, 250);
		for(int i=0;i<7;i++){
			fillrect(render, &rect, 100, 200, 50, 0);
			setFont(pFT, week[i], 90, 110);
			drawFont(render, pFT, rect);
			//text(render, font, week[i], textColor, rect, 20);
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
			}else{
				setTextColor(&textColor, 0, 50, 250);
				
			}
			setFont(pFT, days[i], 70, 80);
			drawFont(render, pFT, rect);
			//text(render, font, days[i], textColor, rect, 30);
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
			setRect(&rect, x-10, y-10, 20, 20);
			fillrect(render, &rect, 250, 0, 250, 0);
		}
		
		//手滑动效果
		if(flag==2){
			xx = (xx+a)%2000+b;
			if(xx<z-1000) nextmonth(&year, &month);
			if(xx>-(z-1000)) lastmonth(&year, &month); 
			if(xx>-z&&xx<z)
			{
				xx=0;
				flag=0;
			}
		}
		
		//未达最大距离返回
		if(flag==3){
			if(xx<=-z)
				xx += 30;
			if(xx>=z)
				xx -= 30;
			if(xx>-z&&xx<z)
			{
				xx=0;
				flag=0;
			}
		}
		
		//帧数
		fps = SDL_GetTicks() - fps;
		if (fps < 20) {
			SDL_Delay(20 - fps);
		}
		
		//显示
		SDL_RenderPresent(render);
		fps = SDL_GetTicks();
		
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
				if(xx>0)
				{
					a=z+1000;
					b=z-1000;
				}
				if(xx<0)
				{
					a=-(z+1000);
					b=-(z-1000);
				}
				flag = 1;
			}
			
			//抬起动作
			if(event.type == SDL_MOUSEBUTTONUP){
				if(xx>200||xx<-200){
					flag = 2;
				}else{
					flag = 3;
				}		
				//break;
			}
		}
	}
	
	//释放font
	destroyFont(pFT);
	
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
