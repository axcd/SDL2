#include<math.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#define PI 3.14159265

int Window_WIDTH = 720;
int Window_HEIGHT = 1280;

const int UP = 1;
const int DWON = 2;
const int LEFT = 3;
const int RIGHT = 4;

SDL_Window *window = NULL;
SDL_Renderer *render = NULL;
SDL_Texture *bkgtex = NULL;
SDL_Texture *footex = NULL;
SDL_Texture *joytex = NULL;

SDL_Event event;
SDL_Rect dstrect;
SDL_Rect srcrect;

int x, y, R, r;
int xc, yc, rc;
int Min_X, Min_Y, Max_X, Max_Y, Joy_X, Joy_Y;
int Foo_W, Foo_H, Foo_X, Foo_Y;
int code = 0;

int get_data() {

  SDL_DisplayMode displayMode;
  if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0)
    return 1;
    
  Window_WIDTH = displayMode.w;
  Window_HEIGHT = displayMode.h;

  R = floor(0.25 * Window_HEIGHT);
  r = floor(0.5 * R);
  Joy_X = floor(0.3 * R);
  Joy_Y = Window_HEIGHT-floor(2.3 * R);
  Min_X = floor(0.0 * Window_WIDTH);
  Min_Y = floor(0.4 * Window_HEIGHT);
  Max_X = floor(0.95 * Window_WIDTH);
  Max_Y = floor(0.75 * Window_HEIGHT);
  Foo_X = floor(0.0 * Window_WIDTH);
  Foo_Y = floor(0.4 * Window_HEIGHT);
  Foo_W = floor(0.05 * Window_WIDTH);
  Foo_H = floor(0.25 * Window_HEIGHT);

  srcrect.x = 0;
  srcrect.y = 205;
  srcrect.w = 64;
  srcrect.h = 205;

  dstrect.x = Foo_X;
  dstrect.y = Foo_Y;
  dstrect.w = Foo_W;
  dstrect.h = Foo_H;
  
  return 0;
}

int Init() {

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0 )
    return 1;
  if (get_data() != 0)
    return 1;
  window = SDL_CreateWindow("SDL2 RUN",
                            SDL_WINDOWPOS_UNDEFINED, 
                            SDL_WINDOWPOS_UNDEFINED, 
                             Window_WIDTH,
                             Window_HEIGHT, 
                             SDL_WINDOW_FULLSCREEN);

  if (window == NULL) {
    return 1;
  }

  render = SDL_CreateRenderer(window, -1,
                              SDL_RENDERER_ACCELERATED |
                              SDL_RENDERER_PRESENTVSYNC);

  if (render == NULL) {
    return 1;
  }
  
  if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0){
	  return 1;
  }

  return 0;
}

int load_image() {

  SDL_Surface *bkg = NULL;
  SDL_Surface *foo = NULL;
  SDL_Surface *joy = NULL;

  bkg = IMG_Load("resource/background.png");
  if (bkg == NULL) {
    return 1;
  }
  bkgtex = SDL_CreateTextureFromSurface(render, bkg);
  SDL_FreeSurface(bkg);

  foo = IMG_Load("resource/foo.png");
  if (foo == NULL) {
    return 1;
  }
  Uint32 colorkey = SDL_MapRGB(foo->format, 0, 0xFF, 0xFF);
  SDL_SetColorKey(foo, 1, colorkey);
  footex = SDL_CreateTextureFromSurface(render, foo);
  SDL_FreeSurface(foo);

  joy = IMG_Load("resource/joystick.png");
  if (joy == NULL) {
    return 1;
  }
  joytex = SDL_CreateTextureFromSurface(render, joy);
  SDL_FreeSurface(joy);

  return 0;
}

void handle_input() {

  if (event.type == SDL_MOUSEMOTION) {

    if ((1.0 * xc / rc) > cos(PI / 4)) {
      code = UP;
    }

    if ((1.0 * xc / rc) < -cos(PI / 4)) {
      code = DWON;
    }

    if ((1.0 * yc / rc) < -cos(PI / 4)) {
      code = LEFT;
    }

    if ((1.0 * yc / rc) > cos(PI / 4)) {
      code = RIGHT;
    }

    if (pow(xc, 2) + pow(yc, 2) > pow(R, 2)) {
      code = 0;
    }

    if (pow(xc, 2) + pow(yc, 2) < pow(r, 2)) {
      code = 0;
    }

  }

  if (event.type == SDL_MOUSEBUTTONUP) {
    code = 0;
  }
}

void move() {

  if (code == UP) {
    srcrect.y = 0;
    if (dstrect.x <= Max_X)
      dstrect.x += floor(Foo_W / 4);
  }

  if (code == DWON) {
    srcrect.y = 205;
    if (dstrect.x >= Min_X)
      dstrect.x -= floor(Foo_W / 4);
  }

  if (code == LEFT) {
    srcrect.y = 0;
    if (dstrect.y >= Min_Y)
      dstrect.y -= floor(Foo_W / 4);
  }

  if (code == RIGHT) {
    srcrect.y = 205;
    if (dstrect.y <= Max_Y)
      dstrect.y += floor(Foo_W / 4);
  }
  
  if (code != 0){	
	Mix_Music *sound = Mix_LoadMUS("audio/low.wav");
	Mix_PlayMusic(sound, 1);
    srcrect.x += 64;
    srcrect.x = srcrect.x % 256;
  }

}

void put_joystick() {
  SDL_Rect drect;
  drect.x = Joy_X;
  drect.y = Joy_Y;
  drect.w = 2 * R;
  drect.h = 2 * R;
  SDL_RenderCopy(render, joytex, NULL, &drect);
}

void display() {
  SDL_RenderClear(render);
  SDL_RenderCopy(render, bkgtex, NULL, NULL);
  SDL_RenderCopy(render, footex, &srcrect, &dstrect);
  put_joystick();
  SDL_RenderPresent(render);
}

void clean_up() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(render);
  SDL_DestroyTexture(bkgtex);
  SDL_DestroyTexture(footex);
  SDL_DestroyTexture(joytex);
  Mix_CloseAudio();
  SDL_Quit();
}

int main(int argc, char **args) {

  int fps = 0;
  int quit = 0;

  if (Init())
    return 1;
  if (load_image())
    return 1;

  while (!quit) {
    fps = SDL_GetTicks();

    display();
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = 1;
      }
      x = event.button.x;
      y = event.button.y;
      xc = x - (R + Joy_X);
      yc = y - (R + Joy_Y);
      rc = sqrt(pow(xc, 2) + pow(yc, 2));
      handle_input();
    }

    move();

    fps = SDL_GetTicks() - fps;
    if (fps < 100) {
      SDL_Delay(100 - fps);
    }
  }

  clean_up();

  return 0;
}
