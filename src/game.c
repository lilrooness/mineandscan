#include "game.h"

void game_init() {
  mousex = 0; mousey = 0;
  up_key=false; down_key=false; left_key=false; right_key=false;

  state = malloc(sizeof(GameState));

  state->quit = false;
  
  state->scanButton = (Button) {10, 10, false};
  state->mineButton = (Button) {10, 74, false};

  state->scanLight = (ScanLight) {74, 10, false};
  state->mineLight = (MineLight) {74, 74, false};

  state->playerX = 0;
  state->playerY = 0;

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
  process_events(state);
  
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
    xdirection += -1;
  }

  int xspeed = xdirection * speed;
  int yspeed = ydirection * speed;

  state->playerX += xspeed;
  state->playerY += yspeed;
}

void check_button_presses(GameState *state) {
  //check each button

  //Scan button
  int scanButtonX = state->scanButton.x
    + (SPRITE_W/2 - UI_BTN_W/2);

  int scanButtonY = state->scanButton.y
    + (SPRITE_H/2 - UI_BTN_H/2);

  if(mouse_inside_bbox(scanButtonX,
                       scanButtonY,
                       UI_BTN_W,
                       UI_BTN_H)) {
    state->scanButton.down = !state->scanButton.down;
    state->scanLight.on = state->scanButton.down;
  }

  //Mine button
  int mineButtonX = state->mineButton.x
    + (SPRITE_W/2 - UI_BTN_W/2);

  int mineButtonY = state->mineButton.y
    + (SPRITE_H/2 - UI_BTN_H/2);

  if(mouse_inside_bbox(mineButtonX,
                       mineButtonY,
                       UI_BTN_W,
                       UI_BTN_H)) {
    state->mineButton.down = !state->mineButton.down;
    state->mineLight.on = state->mineButton.down;
  }
}

bool mouse_inside_bbox(int x, int y, int width, int height) {
  return (mousex > x
          && mousex < x + width
          && mousey > y
          && mousey < y + height);
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

void process_events(GameState *state) {
    while(!state->quit) {
    handle_input(state);

    SDL_Rect rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderFillRect(renderer, &rect);

    render_ui(renderer, state);
    SDL_RenderPresent(renderer);
  }
}
