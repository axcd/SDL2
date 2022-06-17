#include<stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "calender.c"

//窗口变量
SDL_Window* window = NULL;

//渲染变量
SDL_Renderer* render = NULL;

//字体
TTF_Font *font = NULL;	
SDL_Surface *tmp = NULL;
SDL_Texture *fonttex = NULL;
	
//按键动作变量
SDL_Event event;

//获取两者最小值
int min(int a, int b)
{
	return a<b?a:b;
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
	window = SDL_CreateWindow("Canlender SDL", 
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
	SDL_Rect rect0 = { 110,120,60,60 };
	//标题框
	SDL_Rect rect1 = { 430,80,220,100 };
	//背景框
	SDL_Rect rect2 = { 90,400,900,890 };
	//last框
	SDL_Rect rect3 = { 30,50,250,100 };
	//next框
	SDL_Rect rect4 = { 800,50,250,100 };
	
	//记录被点击位置
	char flag = 0;
	int x=0, y=0, quit = 1;
	
	//获取当前年月
	date();
	
	//启动画面
	for(int i=0;i<10;i++)
	{
		SDL_SetRenderDrawColor(render, (25*i)%255, (25*i)%255, (25*i)%255, (25*i)%255);
		SDL_RenderClear(render);
		SDL_RenderPresent(render);
		SDL_Delay(50);
	}
	
	//主循环
	while (quit){
		
		//计算开始结束
		int s=dayOftheWeekThisYearQueryMonth(year,month)-1;
		int e=monthDays[month]+1;
		int k = (e+s)%7==0?(e+s)/7:(e+s)/7+1;
		rect2.h = k * 150 - 10;
		
		//绘制大背景
		SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
		SDL_RenderClear(render);
		
		//画背景墙
		fillrect(render, &rect2, 200, 200, 250, 0);
		
		//画标题
		SDL_Color textColor = { 25, 100, 255 };
		char ss[20]={'0'};
		text(render, datestr(ss, "."), textColor, rect1, 15);
		
		//画周几
		SDL_Color textColor3 = { 250, 0, 250 };
		for(int i=0;i<7;i++){
			SDL_Rect rect01 = rect;
			rect01.x += i*130;
			fillrect(render, &rect01, 100, 200, 50, 0);
			text(render, week[i], textColor3, rect01, 20);
		}
		
		//画数字
		SDL_Color textColor4 = { 0, 100, 255 };
		for(int i=1;i<e;i++){
			SDL_Rect rect02 = rect;
			rect02.x += ((i+s)%7)*130;
			rect02.y += ((i+s)/7+1)*150;
			drawrect(render, &rect02, 200, 0, 250, 0);
			text(render, day[i], textColor4, rect02, 30);
		}
		
		//画点击效果
		if(flag==1){
			if(x>30 && x<280 && y>50 && y<180) {
				fillrect(render, &rect3, 20, 0, 250, 0);
			}else if(x>800 && x< 1050 && y> 50&& y<180) {
				fillrect(render, &rect4, 20, 0, 250, 0);
			}else{
				rect0.x = x;
				rect0.y = y;
				fillrect(render, &rect0, 250, 0, 250, 0);
			}	
		}
		
		//画前一月
		SDL_Color textColor1 = { 50, 150, 250 };
		text(render, "前一月", textColor1, rect3, 20);
		
		//画后一月
		SDL_Color textColor2 = { 50, 150, 250 };
		text(render, "后一月", textColor2, rect4, 20);
		
		//显示
		SDL_RenderPresent(render);
		
		//获取事件
		while (SDL_PollEvent(&event)) {
      
			//获取按键动作，按esc退出
			if (event.type == SDL_QUIT) {
				quit = 0;
				break;
			}

			if(event.type == SDL_MOUSEMOTION){
				x = event.button.x;
				y = event.button.y;
				flag = 1;
			}
			
			//抬起动作
			if(event.type == SDL_MOUSEBUTTONUP){
				if(x>30 && x<280 && y>50 && y<180) 
					lastmonth(&year, &month);
				else if(x>800 && x< 1050 && y> 50&& y<180) {
					nextmonth(&year, &month);
				}
				flag = 0;
				break;
			}
		}
	}
	
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
