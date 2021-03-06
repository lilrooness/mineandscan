#include "game.h"

void render_gameover_screen(SDL_Renderer *renderer, GameState *state) {
    SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF};
    SDL_Texture *text = text_to_texture("GAME OVER - press 'R' to restart", textColor);
    int textWidth;
    int textHeight;
    SDL_QueryTexture(text, NULL, NULL, &textWidth, &textHeight);
    SDL_Rect textDst = {WINDOW_WIDTH/2 - textWidth-2, WINDOW_HEIGHT/2 - textHeight/2, textWidth, textHeight};
    SDL_Rect textSrc = {0, 0, textWidth, textHeight};
    SDL_RenderCopy(renderer, text, &textSrc, &textDst);
}

void render_ui(SDL_Renderer *renderer, GameState *state) {

  //draw screen
  SDL_Rect tileDstRect;
  SDL_Rect tileSrcRect = {
    UI_CENTER_X,
    UI_CENTER_Y,
    SPRITE_W,
    SPRITE_H
  };

  int i = 0;
  for(i=0; i<SCREEN_TILES_LENGTH; i++) {
    int x = i%(DISPLAY_SCREEN_WIDTH);
    int y = i / DISPLAY_SCREEN_HEIGHT;

    tileDstRect.x = x_log_to_real(x*SPRITE_W_GAME
                                  + DISPLAY_SCREEN_X);
    tileDstRect.y = y_log_to_real(y*SPRITE_H_GAME
                                  + DISPLAY_SCREEN_Y);
    tileDstRect.w = x_log_to_real(SPRITE_W_GAME);
    tileDstRect.h = y_log_to_real(SPRITE_H_GAME);


    switch(SCREEN_TILES[i]) {
    case 1:
      tileSrcRect.x = UI_EDGE_TL_X;
      break;
    case 2:
      tileSrcRect.x = UI_EDGE_T_X;
      break;
    case 3:
      tileSrcRect.x = UI_EDGE_TR_X;
      break;
    case 4:
      tileSrcRect.x = UI_EDGE_L_X;
      break;
    case 5:
      tileSrcRect.x = UI_CENTER_X;
      break;
    case 6:
      tileSrcRect.x = UI_EDGE_R_X;
      break;
    case 7:
      tileSrcRect.x = UI_EDGE_BL_X;
      break;
    case 8:
      tileSrcRect.x = UI_EDGE_B_X;
      break;
    case 9:
      tileSrcRect.x = UI_EDGE_BR_X;
      break;
    default:
      tileSrcRect.x = UI_CENTER_X;
    }

    SDL_RenderCopy(renderer,
                   spriteSheet,
                   &tileSrcRect,
                   &tileDstRect);

  }

  SDL_Rect reticleDstRect = {x_log_to_real(DISPLAY_SCREEN_X + (DISPLAY_SCREEN_WIDTH*SPRITE_W_GAME)/2 - SPRITE_W_GAME/2),
                             y_log_to_real(DISPLAY_SCREEN_Y + (DISPLAY_SCREEN_HEIGHT*SPRITE_H_GAME)/2 - SPRITE_H_GAME/2),
                             x_log_to_real(SPRITE_W_GAME),
                             y_log_to_real(SPRITE_H_GAME)};

  SDL_RenderCopy(renderer, spriteSheet, &RETICLE_SRC_RECT, &reticleDstRect);

  //render text
  char textBuff[100];
  sprintf(textBuff, "X: %d - Y: %d",
          state->playerX,
          state->playerY);

  SDL_Texture *text;
  text = text_to_texture(textBuff,
                         (SDL_Color){
                           0xFF,
                             0xFF,
                             0xFF,
                             0xFF});
  int textWidth;
  int textHeight;

  SDL_QueryTexture(text, NULL, NULL, &textWidth, &textHeight);

  SDL_Rect textSrcRect = {0, 0, textWidth, textHeight};
  SDL_Rect textDstRect = {x_log_to_real(DISPLAY_SCREEN_X + 35),
                          y_log_to_real(DISPLAY_SCREEN_Y + 67),
                          textWidth,
                          textHeight};

  SDL_RenderCopy(renderer, text,
                 &textSrcRect,
                 &textDstRect);

    SDL_SetRenderDrawColor(renderer,
                         0x00,
                         0x00,
                         0x00,
                         0xFF);

  //draw buttons
  SDL_Rect scanButtonDstRect ={x_log_to_real(state->scanButton.x),
                               y_log_to_real(state->scanButton.y),
                               x_log_to_real(SPRITE_W_GAME),
                               y_log_to_real(SPRITE_H_GAME)};

  SDL_Rect mineButtonDstRect ={x_log_to_real(state->mineButton.x),
                               y_log_to_real(state->mineButton.y),
                               x_log_to_real(SPRITE_W_GAME),
                               y_log_to_real(SPRITE_H_GAME)};

  SDL_Rect *activeBtnSrc = &BUTTON_SRC_RECT_UP;

  if(state->scanButton.down) {
    activeBtnSrc = &BUTTON_SRC_RECT_DOWN;
  }

  SDL_RenderCopy(renderer,
                 spriteSheet,
                 activeBtnSrc,
                 &scanButtonDstRect);

  if(state->mineButton.down) {
    activeBtnSrc = &BUTTON_SRC_RECT_DOWN;
  } else {
    activeBtnSrc = &BUTTON_SRC_RECT_UP;
  }

  SDL_RenderCopy(renderer,
                 spriteSheet,
                 activeBtnSrc,
                 &mineButtonDstRect);

  //draw enemies

  //scan mode
  if(state->screen_mode == 2) {
    render_enemies(state);
  } else if(state->screen_mode == 1) {
    //mine mode
    render_mines(state);
  }

  //draw lights
  SDL_Rect mineLightDstRect = {x_log_to_real(state->mineLight.x),
                               y_log_to_real(state->mineLight.y),
                               x_log_to_real(SPRITE_W_GAME),
                               y_log_to_real(SPRITE_H_GAME)};


  SDL_Rect scanLightDstRect = {x_log_to_real(state->scanLight.x),
                               y_log_to_real(state->scanLight.y),
                               x_log_to_real(SPRITE_W_GAME),
                               y_log_to_real(SPRITE_H_GAME)};

  //draw mine light
  SDL_Rect *activeMineLightSrc = &MINE_LIGHT_SRC_RECT_OFF;
  if(state->mineLight.on) {
    activeMineLightSrc = &MINE_LIGHT_SRC_RECT_ON;
  }

  SDL_RenderCopy(renderer,
                 spriteSheet,
                 activeMineLightSrc,
                 &mineLightDstRect);

  //draw scan light
  SDL_Rect *activeScanLightSrc = &SCAN_LIGHT_SRC_RECT_OFF;
  if(state->scanLight.on) {
    activeScanLightSrc = &SCAN_LIGHT_SRC_RECT_ON;
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
  if(SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO) < 0) {
    printf("SDL could not initialise either video or audio %s",
           SDL_GetError());
    return 1;
  }

  if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0) {
    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    return 1;
  }

  if(!IMG_Init(IMG_INIT_PNG)) {
    printf("SDL could not initialise PNG %s",
           SDL_GetError());
    return 1;
  }

  if(TTF_Init() == -1) {
    printf("SDL could not initialise TTF %s",
           TTF_GetError());
    return 1;
  }

  font = TTF_OpenFont("res/m5x7.ttf", 16);

  if(font == NULL) {
    printf("SDL could not open font %s",
           TTF_GetError());
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

SDL_Texture* text_to_texture(char *string, SDL_Color color) {

  SDL_Surface *surface = NULL;
  SDL_Texture *texture = NULL;

  surface = TTF_RenderText_Solid(font, string, color);

  if(surface == NULL) {
    printf("unable to render text to font %s",
           TTF_GetError());

    return NULL;
  }

  texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  if(texture == NULL) {
    printf("unable to create texture from rendererd text %s",
           SDL_GetError());

    return NULL;
  }

  return texture;
}

void render_enemies(GameState *state) {
  int i=0;
  Enemy *tmp;

  for(i=0; i<nenemies; i++) {
    tmp = &(state->enemies[i]);

    if(enemy_in_range(tmp, state, SCAN_RANGE/2)) {
      float ex = tmp->x - (state->playerX - SCAN_RANGE/2);
      float ey = tmp->y - (state->playerY - SCAN_RANGE/2);

      float screenWidth =SPRITE_W_GAME * (DISPLAY_SCREEN_WIDTH);
      float screenHeight=SPRITE_H_GAME *(DISPLAY_SCREEN_HEIGHT);
      float scanRange = SCAN_RANGE;

      int screenPosX = (screenWidth / scanRange) * ex;
      int screenPosY = (screenHeight / scanRange) * ey;

      SDL_Rect dstRect = (SDL_Rect){
                                    x_log_to_real(DISPLAY_SCREEN_X + screenPosX - SPRITE_W_GAME/2),
                                    y_log_to_real(DISPLAY_SCREEN_Y + screenPosY - SPRITE_H_GAME/2),
                                    x_log_to_real(SPRITE_W_GAME),
                                    y_log_to_real(SPRITE_H_GAME)
      };

      SDL_RenderCopy(renderer,
                     spriteSheet,
                     &ENEMY_SRC,
                     &dstRect);
    }
  }
}

void render_mines(GameState *state) {
  int i;
  Mine *tmp;

  for(i=0; i<nmines; i++) {
    tmp = &(state->mines[i]);

    if(mine_in_range(tmp, state, SCAN_RANGE/2)) {
      float ex = tmp->x - (state->playerX - SCAN_RANGE/2);
      float ey = tmp->y - (state->playerY - SCAN_RANGE/2);
      
      float screenWidth =SPRITE_W_GAME * (DISPLAY_SCREEN_WIDTH);
      float screenHeight=SPRITE_H_GAME *(DISPLAY_SCREEN_HEIGHT);
      float scanRange = SCAN_RANGE;
      
      int screenPosX = (screenWidth / scanRange) * ex;
      int screenPosY = (screenHeight / scanRange) * ey;
      
      SDL_Rect dstRect = (SDL_Rect){
                                    x_log_to_real(DISPLAY_SCREEN_X + screenPosX - SPRITE_W_GAME/2),
                                    y_log_to_real(DISPLAY_SCREEN_Y + screenPosY - SPRITE_H_GAME/2),
                                    x_log_to_real(SPRITE_W_GAME),
                                    y_log_to_real(SPRITE_H_GAME)
      };
      
      if(tmp->remaining_resource > 0) {
        SDL_RenderCopy(renderer,
                       spriteSheet,
                       &MINE_SRC,
                       &dstRect);
      } else {
        SDL_RenderCopy(renderer,
                     spriteSheet,
                     &MINE_SRC_EMPTY,
                     &dstRect);
      }
    }

    //just to break the curlies }}}}}
    return;
  }
}

