#include "game.h"

void render_ui(SDL_Renderer *renderer, GameState *state) {

  //draw buttons
  SDL_Rect buttonSrcRect_up = {UI_BTN_UP_X, UI_BTN_UP_Y,
                               SPRITE_W, SPRITE_H};
  
  SDL_Rect buttonSrcRect_down = {UI_BTN_DOWN_X, UI_BTN_DOWN_Y,
                                 SPRITE_W, SPRITE_H};
  
  SDL_Rect scanButtonDstRect ={x_log_to_real(state->scanButton.x),
                               y_log_to_real(state->scanButton.y),
                               x_log_to_real(SPRITE_W_GAME),
                               y_log_to_real(SPRITE_H_GAME)};

  SDL_Rect mineButtonDstRect ={x_log_to_real(state->mineButton.x),
                               y_log_to_real(state->mineButton.y),
                               x_log_to_real(SPRITE_W_GAME),
                               y_log_to_real(SPRITE_H_GAME)};

  SDL_Rect *activeBtnSrc = &buttonSrcRect_up;

  if(state->scanButton.down) {
    activeBtnSrc = &buttonSrcRect_down;
  }

  SDL_RenderCopy(renderer,
                 spriteSheet,
                 activeBtnSrc,
                 &scanButtonDstRect);

  if(state->mineButton.down) {
    activeBtnSrc = &buttonSrcRect_down;
  } else {
    activeBtnSrc = &buttonSrcRect_up;
  }

  SDL_RenderCopy(renderer,
                 spriteSheet,
                 activeBtnSrc,
                 &mineButtonDstRect);

  //draw lights
  SDL_Rect mineLightRect_off = {UI_MN_LT_OFF_X,
                                UI_MN_LT_OFF_Y,
                                SPRITE_W,
                                SPRITE_H};
  
  SDL_Rect mineLightRect_on = {UI_MN_LT_ON_X,
                               UI_MN_LT_ON_Y,
                               SPRITE_W,
                               SPRITE_H};

  SDL_Rect mineLightDstRect = {x_log_to_real(state->mineLight.x),
                               y_log_to_real(state->mineLight.y),
                               x_log_to_real(SPRITE_W_GAME),
                               y_log_to_real(SPRITE_H_GAME)};
  
  SDL_Rect scanLightRect_off = {UI_SC_LT_OFF_X,
                                UI_SC_LT_OFF_Y,
                                SPRITE_W,
                                SPRITE_H};
  
  SDL_Rect scanLightRect_on = {UI_SC_LT_ON_X,
                               UI_SC_LT_ON_Y,
                               SPRITE_W,
                               SPRITE_H};

  SDL_Rect scanLightDstRect = {x_log_to_real(state->scanLight.x),
                               y_log_to_real(state->scanLight.y),
                               x_log_to_real(SPRITE_W_GAME),
                               y_log_to_real(SPRITE_H_GAME)};

  //draw mine light
  SDL_Rect *activeMineLightSrc = &mineLightRect_off;
  if(state->mineLight.on) {
    activeMineLightSrc = &mineLightRect_on;
  }

  SDL_RenderCopy(renderer,
                 spriteSheet,
                 activeMineLightSrc,
                 &mineLightDstRect);

  //draw scan light
  SDL_Rect *activeScanLightSrc = &scanLightRect_off;
  if(state->scanLight.on) {
    activeScanLightSrc = &scanLightRect_on;
  }

  SDL_RenderCopy(renderer,
                 spriteSheet,
                 activeScanLightSrc,
                 &scanLightDstRect);
}

int x_log_to_real(int x) {
  return x * (WINDOW_WIDTH/GAME_WIDTH); // trunc the result
}

int y_log_to_real(int y) {
  return y * (WINDOW_HEIGHT/GAME_HEIGHT);
}

int x_real_to_log(int x) {
  return x / (WINDOW_WIDTH/GAME_WIDTH);
}

int y_real_to_log(int y) {
  return y / (WINDOW_HEIGHT/GAME_HEIGHT);
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
