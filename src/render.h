#ifdef RENDER_H
#else

#include "game.h"
#include "ui.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *spriteSheet;

void render_ui(SDL_Renderer *renderer, GameState *state) {

  int srcx = UI_BTN_UP_X;
  int srcy = UI_BTN_DOWN_Y;
  
  SDL_Rect scanButtonSrcRect = {srcx, srcy,
                                SPRITE_W, SPRITE_H};
  
  SDL_Rect scanButtonDstRect = {state->scanButton.x,
                                state->scanButton.y,
                                SPRITE_W, SPRITE_H};
  SDL_RenderCopy(renderer,
                 spriteSheet,
                 &scanButtonSrcRect,
                 &scanButtonDstRect);                 
}

int x_log_to_real(float x) {
  return (int) x * WIDTH_FAC; // trunc the result
}

int y_log_to_real(float y) {
  return (int) y * HEIGHT_FAC;
}

SDL_Texture* load_texture(SDL_Renderer *renderer,
                          char *filename) {

  SDL_Texture *texture = NULL;
  SDL_Surface *loadedSurface = NULL;
  
  loadedSurface = IMG_Load(filename);

  if(loadedSurface == NULL) {
    printf("Failed to load image file: %s for reason: %s",
           filename,
           IMG_GetError());
  }
  
  SDL_SetColorKey(loadedSurface,
                  SDL_TRUE,
                  SDL_MapRGB(loadedSurface->format,
                             0xFF,
                             0,
                             0xFF));
  
  texture = SDL_CreateTextureFromSurface(renderer,
                                         loadedSurface);

  SDL_FreeSurface(loadedSurface);

  return texture;
}

int render_init() {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialise video %s",
           SDL_GetError());
    return 1;
  }
  
  if(!IMG_Init(IMG_INIT_PNG)) {
    printf("SDL could not initialise PNG %s",
           SDL_GetError());
    return 1;
  }
  
  window = SDL_CreateWindow("Path",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            WINDOW_WIDTH, WINDOW_HEIGHT,
                            SDL_WINDOW_SHOWN);
  
  renderer = SDL_CreateRenderer(window,
                                -1,
                                SDL_RENDERER_ACCELERATED);
  
  if(renderer == NULL) {
    printf("SDL could not create renderer: %s",
           SDL_GetError());
    return 1;
  }
  
  SDL_SetRenderDrawColor(renderer,
                         0x00,
                         0x00,
                         0x00,
                         0xFF);

  spriteSheet = load_texture(renderer,
                             "res/minespritesheet.bmp");

  return 0;
}


#define RENDER_H
#endif
