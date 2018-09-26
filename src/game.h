#ifndef GAME_H


#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


static const int SPRITE_W = 64;
static const int SPRITE_H = 64;

static const int UI_MN_LT_OFF_X = 0;
static const int UI_MN_LT_OFF_Y = 0;
 
static const int UI_MN_LT_ON_X = 128;
static const int UI_MN_LT_ON_Y = 0;
 
static const int UI_SC_LT_OFF_X = 64;
static const int UI_SC_LT_OFF_Y = 0;
 
static const int UI_SC_LT_ON_X = 192;
static const int UI_SC_LT_ON_Y = 0;
 
static const int UI_RED_LED_OFF_X = 128;
static const int UI_RED_LED_OFF_Y = 64;
 
static const int UI_RED_LED_ON_X = 256;
static const int UI_RED_LED_ON_Y = 64;
 
static const int UI_GREEN_LED_OFF_X = 192;
static const int UI_GREEN_LED_OFF_Y = 64;
 
static const int UI_GREEN_LED_ON_X = 320;
static const int UI_GREEN_LED_ON_Y = 64;
 
static const int UI_BTN_UP_X = 0;
static const int UI_BTN_UP_Y = 64;
 
static const int UI_BTN_DOWN_X = 64;
static const int UI_BTN_DOWN_Y = 64;
 
 
static const int WINDOW_WIDTH = 640;
static const int WINDOW_HEIGHT = 480;
 //KEEP THIS ASPECT RATIO!!!!
static const int LOG_W = 100;
static const int LOG_H = 75;
static const float WIDTH_FAC = 6.4f;
static const float HEIGHT_FAC = 10.4f;

typedef struct {
  float x;
  float y;
  bool down;
} Button;

typedef struct {
  float x;
  float y;
  bool on;
  bool color; // 1=green | 0=red
} Led;

typedef struct {
  float x;
  float y;
  bool on;
} MineLight;

typedef struct {
  float x;
  float y;
  bool on;
} ScanLight;

enum ComponentType {UI_RED_LED,
                    UI_GREEN_LED,
                    UI_MN_LT,
                    UI_SC_LT,
                    UI_BTN};

typedef enum ComponentType ComponentType;

typedef struct {
  Button scanButton;
  Button mineButton;

  MineLight mineLight;
  ScanLight scanLight;

  int playerX;
  int playerY;
} GameState;


GameState *state;

void game_init();

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *spriteSheet;

void render_ui(SDL_Renderer *renderer, GameState *state);
int x_log_to_real(float x);
int y_log_to_real(float y);
SDL_Texture* load_texture(SDL_Renderer *renderer,
                          char *filename);
int render_init();

#define GAME_H
#endif
