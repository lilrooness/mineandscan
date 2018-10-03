#include "game.h"

void game_init() {
  mousex = 0; mousey = 0;

  up_key=false; down_key=false;
  left_key=false; right_key=false;

  state = malloc(sizeof(GameState));

  state->quit = false;
  
  state->scanButton = (Button) {3, 8, false};
  state->mineButton = (Button) {3, 33, false};

  state->scanLight = (ScanLight) {17, 8, false};
  state->mineLight = (MineLight) {17, 33, false};

  state->playerX = 0;
  state->playerY = 0;

  state->screen_mode = -1;

  nenemies = 10;
  state->enemies = malloc(nenemies * sizeof(Enemy));

  int maxRand = 100;

  for(int i=0; i<nenemies; i++) {
    int x = (int)rand()%maxRand;
    int y = (int)rand()%maxRand;
    state->enemies[i] = (Enemy) {x, y, false};
  }
}

void handle_input(GameState *state) {
  SDL_Event e;
  while(SDL_PollEvent(&e) != 0) {
    if(e.type == SDL_QUIT) {
      state->quit = true;
    }else if(e.type == SDL_MOUSEMOTION) {
      SDL_GetMouseState(&mousex, &mousey);
    }else if(e.type == SDL_MOUSEBUTTONDOWN) {
      check_button_presses(state);
    }else if(e.type == SDL_KEYDOWN) {
      handle_key_event(e, true);
    }else if(e.type == SDL_KEYUP) {
      handle_key_event(e, false);
    }
  }
}

void game_loop(GameState *state) {

  while(!state->quit) {

    int frameStart = SDL_GetTicks();
    
    handle_input(state);
    
    SDL_Rect rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderFillRect(renderer, &rect);
    
    render_ui(renderer, state);


    int xdirection = 0;
    int ydirection = 0;
    
    if(up_key) {
      ydirection -= 1;
    }
    if(down_key) {
      ydirection += 1;
    }
    if(left_key) {
      xdirection -= 1;
    }
    if(right_key) {
      xdirection += 1;
    }
    
    int xspeed = xdirection * speed;
    int yspeed = ydirection * speed;
    
    state->playerX += xspeed;
    state->playerY += yspeed;
    
    SDL_RenderPresent(renderer);

    int frameEnd = SDL_GetTicks();
    int frameTime = frameEnd - frameStart;

    if(frameTime < (1000 / FRAMES_PER_SECOND)) {
      SDL_Delay((1000/FRAMES_PER_SECOND) - frameTime);
    }
  }
}

void check_button_presses(GameState *state) {
  //check each button

  //Scan button
  int scanButtonX = state->scanButton.x
    + (SPRITE_W_GAME/2 - UI_BTN_W/2);

  int scanButtonY = state->scanButton.y
    + (SPRITE_H_GAME/2 - UI_BTN_H/2);

  if(mouse_inside_bbox(scanButtonX,
                       scanButtonY,
                       UI_BTN_W,
                       UI_BTN_H)) {
    state->scanButton.down = !state->scanButton.down;
    state->scanLight.on = state->scanButton.down;

    if(state->scanLight.on) {
      state->screen_mode = 2;
      state->mineLight.on = false;
      state->mineButton.down = false;
    }
  }

  //Mine button
  int mineButtonX = state->mineButton.x
    + (SPRITE_W_GAME/2 - UI_BTN_W/2);

  int mineButtonY = state->mineButton.y
    + (SPRITE_H_GAME/2 - UI_BTN_H/2);

  if(mouse_inside_bbox(mineButtonX,
                       mineButtonY,
                       UI_BTN_W,
                       UI_BTN_H)) {
    state->mineButton.down = !state->mineButton.down;
    state->mineLight.on = state->mineButton.down;

    if(state->scanLight.on) {
      state->screen_mode = 1;
      state->scanLight.on = false;
      state->scanButton.down = false;
    }
  }
}

bool mouse_inside_bbox(int x, int y, int width, int height) {
  int mousexLog = x_real_to_log(mousex);
  int mouseyLog = y_real_to_log(mousey);

  return (mousexLog > x
          && mousexLog < x + width
          && mouseyLog > y
          && mouseyLog < y + height);
}

void handle_key_event(SDL_Event e, bool keyDown) {
  switch(e.key.keysym.sym) {
    case SDLK_UP:
      up_key = keyDown;
      break;
    case SDLK_DOWN:
      down_key = keyDown;
      break;
    case SDLK_LEFT:
      left_key = keyDown;
      break;
    case SDLK_RIGHT:
      right_key = keyDown;
      break;
    default:
      break;
  }
}

float distance(float ax, float ay, float bx, float by) {
  return sqrt(pow(bx - ax, 2) + pow(by - ay, 2));
}

bool enemy_in_range(Enemy *e, GameState * state) {
  int px = state->playerX;
  int py = state->playerY;

  int halfRange = SCAN_RANGE/2;
  if(e->x > px - halfRange
     && e->x < px + halfRange
     && e->y > py - halfRange
     && e->y < py + halfRange) {

    return true;
  }

  return false;
}
