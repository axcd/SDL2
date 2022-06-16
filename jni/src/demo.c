#include<stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "calender.c"

#define SDL_MAIN_HANDLED

int main(int argc, char *argv[]){

	//窗口变量
	SDL_Window* window;

	//渲染变量
	SDL_Renderer* render;

	//按键动作变量
	SDL_Event event;
	
	//字体
	TTF_Font *font = NULL;	
	SDL_Surface *tmp = NULL;
	SDL_Texture *fonttex = NULL;
	
	//sdl初始化
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	//创建窗口
	window = SDL_CreateWindow("Hello SDL", 
								SDL_WINDOWPOS_CENTERED, 
								SDL_WINDOWPOS_CENTERED,
								1080, 2480, 
								SDL_WINDOW_SHOWN);

	/*创建渲染器*/
	render = SDL_CreateRenderer(window, -1,0);
	
	//创建字体
	font = TTF_OpenFont("FZKTJW.TTF", 100);
	SDL_Color textColor = { 255, 0, 255 };
	
	//矩形
	const SDL_Rect rect = { 90,250,120,140 };
	//游标
	SDL_Rect rect0 = { 110,120,60,60 };
	//标题框
	SDL_Rect rect1 = { 450,80,200,100 };
	//背景框
	SDL_Rect rect2 = { 90,400,900,890 };
	//last框
	SDL_Rect rect3 = { 30,50,250,100 };
	//next框
	SDL_Rect rect4 = { 800,50,250,100 };
	
	//矩形数组框
	SDL_Rect rects[9][7];

	for(int i=0;i<9;i++){
			for(int j=0;j<7;j++){
				rects[i][j] = rect;
				rects[i][j].x += j*130;
				rects[i][j].y += i*150;
		}
	}
	
	//记录被点击位置
	char flag = 0;
	int x=0,y=0;
	
	//获取当前年月
	date();
	
	//主循环
	while (1){
			
		//计算开始结束
		int s=dayOftheWeekThisYearQueryMonth(year,month)-1;
		int e=monthDays[month]+1;
		int k = (e+s)%7==0?(e+s)/7:(e+s)/7+1;
		rect2.h = k * 150 - 10;
		
		//绘制大背景
		SDL_SetRenderDrawColor(render, 255, 255, 255, 0);
		SDL_RenderClear(render);
		
		//画背景墙
		SDL_SetRenderDrawColor(render, 200, 200, 250, 0);
		SDL_RenderFillRect(render, &rect2);
		
		//画周几
		SDL_Color textColor0 = { 250, 0, 250 };
		for(int i=0;i<7;i++){
			SDL_SetRenderDrawColor(render, 100, 200, 50, 50);
			SDL_RenderFillRect(render, &rects[0][i]);
			
			tmp = TTF_RenderUTF8_Solid( font, week[i], textColor0 );
			fonttex = SDL_CreateTextureFromSurface(render, tmp);
				
			SDL_RenderCopy(render, fonttex, NULL, &rects[0][i]);
				
			SDL_FreeSurface(tmp);
			SDL_DestroyTexture(fonttex);	
		}
		
		//画数字
		SDL_Color textColor1 = { 0, 100, 255 };
		for(int i=8;i<e+7;i++){
			int j = i+s;
			SDL_SetRenderDrawColor(render, 250, 0, 250, 250);
			SDL_RenderDrawRect(render, &rects[j/7][j%7]);
				
			tmp = TTF_RenderText_Solid( font, day[i-7], textColor1 );
			fonttex = SDL_CreateTextureFromSurface(render, tmp);
				
			SDL_RenderCopy(render, fonttex, NULL, &rects[j/7][j%7]);
				
			SDL_FreeSurface(tmp);
			SDL_DestroyTexture(fonttex);	
		}
		
		//画标题
		char ss[20]={'0'};
		itoa(year, ss);
		char s1[11]={'0'};
		itoa(month, s1);
		strcat(ss, ".");
		strcat(ss, s1);
		
		tmp = TTF_RenderText_Solid( font, ss, textColor );
		fonttex = SDL_CreateTextureFromSurface(render, tmp);
		SDL_RenderCopy(render, fonttex, NULL, &rect1);
		SDL_FreeSurface(tmp);
		SDL_DestroyTexture(fonttex);
		
		//画last
		tmp = TTF_RenderText_Solid( font, "last", textColor );
		fonttex = SDL_CreateTextureFromSurface(render, tmp);
		SDL_RenderCopy(render, fonttex, NULL, &rect3);
		SDL_FreeSurface(tmp);
		SDL_DestroyTexture(fonttex);
	
		//画next
		tmp = TTF_RenderText_Solid( font, "next", textColor );
		fonttex = SDL_CreateTextureFromSurface(render, tmp);
		SDL_RenderCopy(render, fonttex, NULL, &rect4);
		SDL_FreeSurface(tmp);
		SDL_DestroyTexture(fonttex);
	
		if(flag==1){
			if(x>30 && x<280 && y>50 && y<180) {
				SDL_SetRenderDrawColor(render, 20, 0, 250, 0);
				SDL_RenderFillRect(render, &rect3);
			}else if(x>800 && x< 1050 && y> 50&& y<180) {
				SDL_SetRenderDrawColor(render, 20, 0, 250, 0);
				SDL_RenderFillRect(render, &rect4);
			}else{
				rect0.x = x;
				rect0.y = y;
				//填充矩形
				SDL_SetRenderDrawColor(render, 250, 0, 250, 0);
				SDL_RenderFillRect(render, &rect0);	
			}
			
		}
		
		//显示
		SDL_RenderPresent(render);
		
		while (SDL_PollEvent(&event)) {
      
			//获取按键动作，按esc退出
			if (event.type == SDL_QUIT) break;

			if(event.type == SDL_MOUSEMOTION){
				x = event.button.x;
				y = event.button.y;
				flag = 1;
				//break;
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
	
	//释放渲染器
	SDL_DestroyRenderer(render);

	//关闭窗口
	SDL_DestroyWindow(window);

	//退出
	SDL_Quit();
	
	return 0;

}
