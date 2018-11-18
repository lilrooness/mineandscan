#ifndef GAME_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#elif __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#elif __WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#endif



//static const int WINDOW_WIDTH = 640;
//static const int WINDOW_HEIGHT = 480;

#define FRAMES_PER_SECOND 60

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

//KEEP THIS ASPECT RATIO!!!!
#define GAME_WIDTH 100
#define GAME_HEIGHT 75

#define SCAN_RANGE 100

//BOUNDING BOXES LOGICAL
#define UI_BTN_W 10
#define UI_BTN_H 4

#define SPRITE_W_GAME 20
#define SPRITE_H_GAME 20

//SPRITESHEET COORDS
#define SPRITE_W 64
#define SPRITE_H 64

#define UI_MN_LT_OFF_X 0
#define UI_MN_LT_OFF_Y 0

#define UI_MN_LT_ON_X 128
#define UI_MN_LT_ON_Y 0

#define UI_SC_LT_OFF_X 64
#define UI_SC_LT_OFF_Y 0

#define UI_SC_LT_ON_X 192
#define UI_SC_LT_ON_Y 0

#define UI_RED_LED_OFF_X 128
#define UI_RED_LED_OFF_Y 64

#define UI_RED_LED_ON_X 256
#define UI_RED_LED_ON_Y 64

#define UI_GREEN_LED_OFF_X 192
#define UI_GREEN_LED_OFF_Y 64

#define UI_GREEN_LED_ON_X 320
#define UI_GREEN_LED_ON_Y 64

#define UI_BTN_UP_X 0
#define UI_BTN_UP_Y 64

#define UI_BTN_DOWN_X 64
#define UI_BTN_DOWN_Y 64

#define UI_CIRCLE_GREEN_X 256
#define UI_CIRCLE_GREEN_Y 0

#define UI_CIRCLE_FILL_GREEN_X 320
#define UI_CIRCLE_FILL_GREEN_Y 0

#define UI_CIRCLE_RED_X 384
#define UI_CIRCLE_RED_Y 0

#define UI_CIRCLE_FILL_RED_X 448
#define UI_CIRCLE_FILL_RED_Y 0

#define UI_EDGE_TL_X 256
#define UI_EDGE_TL_Y 128

#define UI_EDGE_TR_X 320
#define UI_EDGE_TR_Y 128

#define UI_EDGE_BL_X 384
#define UI_EDGE_BL_Y 128

#define UI_EDGE_BR_X 448
#define UI_EDGE_BR_Y 128

#define UI_EDGE_L_X 64
#define UI_EDGE_L_Y 128

#define UI_EDGE_R_X 0
#define UI_EDGE_R_Y 128

#define UI_EDGE_B_X 128
#define UI_EDGE_B_Y 128

#define UI_EDGE_T_X 192
#define UI_EDGE_T_Y 128

#define UI_CENTER_X 512
#define UI_CENTER_Y 128

#define UI_RETICLE_X 512
#define UI_RETICLE_Y 0

static const SDL_Rect MINE_SRC = {
                                  UI_CIRCLE_FILL_GREEN_X,
                                  UI_CIRCLE_FILL_GREEN_Y,
                                  SPRITE_W, SPRITE_H
};

static const SDL_Rect MINE_SRC_EMPTY = {
                                        UI_CIRCLE_GREEN_X,
                                        UI_CIRCLE_GREEN_Y,
                                        SPRITE_W, SPRITE_H
};

static const SDL_Rect ENEMY_SRC = {
  UI_CIRCLE_RED_X,
  UI_CIRCLE_RED_Y,
  SPRITE_W, SPRITE_H
};

static const SDL_Rect ENEMY_ALERT_SRC = {
  UI_CIRCLE_FILL_RED_X,
  UI_CIRCLE_FILL_RED_Y,
  SPRITE_W, SPRITE_H
};

static const SDL_Rect BUTTON_SRC_RECT_UP = {
  UI_BTN_UP_X, UI_BTN_UP_Y,
  SPRITE_W, SPRITE_H};

static const SDL_Rect BUTTON_SRC_RECT_DOWN = {
  UI_BTN_DOWN_X, UI_BTN_DOWN_Y,
  SPRITE_W, SPRITE_H};

static const SDL_Rect MINE_LIGHT_SRC_RECT_OFF = {
  UI_MN_LT_OFF_X, UI_MN_LT_OFF_Y,
  SPRITE_W, SPRITE_H};

static const SDL_Rect MINE_LIGHT_SRC_RECT_ON = {
  UI_MN_LT_ON_X, UI_MN_LT_ON_Y,
  SPRITE_W, SPRITE_H};

static const SDL_Rect SCAN_LIGHT_SRC_RECT_OFF = {
  UI_SC_LT_OFF_X, UI_SC_LT_OFF_Y,
  SPRITE_W, SPRITE_H};

static const SDL_Rect SCAN_LIGHT_SRC_RECT_ON = {
  UI_SC_LT_ON_X, UI_SC_LT_ON_Y,
  SPRITE_W, SPRITE_H};

static const SDL_Rect RETICLE_SRC_RECT = {
 UI_RETICLE_X, UI_RETICLE_Y,
 SPRITE_W, SPRITE_H};

#define SCREEN_TILES_LENGTH 9
#define DISPLAY_SCREEN_X 20
#define DISPLAY_SCREEN_Y 10
#define DISPLAY_SCREEN_WIDTH 3
#define DISPLAY_SCREEN_HEIGHT 3
static const int SCREEN_TILES[] = {1,2,3,
                                   4,5,6,
                                   7,8,9};

static const int speed = 1;
static const int ATTRACTION_RANGE = SCAN_RANGE/3;
static const int KILL_RANGE = 2;

typedef struct {
  int x;
  int y;
  bool down;
} Button;

typedef struct {
  int x;
  int y;
  bool on;
  bool color; // 1=green | 0=red
} Led;

typedef struct {
  int x;
  int y;
  bool on;
} MineLight;

typedef struct {
  int x;
  int y;
  bool on;
} ScanLight;

typedef struct {
  int x;
  int y;
  bool alerted;
} Enemy;

typedef struct {
  int x;
  int y;
  int remaining_resource;
} Mine;

enum ComponentType {UI_RED_LED,
                    UI_GREEN_LED,
                    UI_MN_LT,
                    UI_SC_LT,
                    UI_BTN};

typedef enum ComponentType ComponentType;

enum GameMode {
MENU, PLAY, GAME_OVER
};

typedef enum GameMode GameMode;

typedef struct {
  
  int frames_since_radar_ping;
  bool quit;

  Button scanButton;
  Button mineButton;

  MineLight mineLight;
  ScanLight scanLight;

  int playerX;
  int playerY;

  Enemy *enemies;
  Mine *mines;
  
  int screen_mode; //mine=1 scan=2 none=-1

  GameMode mode;

  char dbg_string[300];
} GameState;

//GLOBALS

int nenemies;
int nmines;

int mousex;
int mousey;

GameState *state;

void game_init();

bool up_key;
bool down_key;
bool left_key;
bool right_key;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *spriteSheet;

TTF_Font *font;

Mix_Chunk *radar_ping;
Mix_Music *ambiance;
int radar_ping_channel;

//FUNCTIONS
void render_ui(SDL_Renderer *renderer, GameState *state);
int x_log_to_real(int x);
int y_log_to_real(int y);
int x_real_to_log(int x);
int y_real_to_log(int y);
SDL_Texture* load_texture(SDL_Renderer *renderer,
                          char *filename);
SDL_Texture* text_to_texture(char *text, SDL_Color color);
int render_init();
void render_enemies(GameState *state);
void render_mines(GameState *state);
void render_gameover_screen(SDL_Renderer *renderer, GameState *state);

void handle_input(GameState *state);
void game_loop(GameState *state);
void check_button_presses(GameState *state);
bool mouse_inside_bbox(int x, int y, int width, int height);
void handle_key_event(SDL_Event e, bool keyDown);
float distance(float ax, float ay, float bx, float by);
bool enemy_in_range(Enemy *enemy, GameState *state, int range);
bool mine_in_range(Mine *mine, GameState *state, int range);
SDL_Point get_approx_vector_to_player(Enemy *enemy, GameState *state);
void update_enemy(Enemy *enemy, GameState *state);
void do_play_tick(GameState *state);
void do_gameover_tick(GameState *state);
void restart_game(GameState *state);
float get_closest_enemy_distance(GameState *state);

#define GAME_H
#endif
