#include "game.h"

void game_init() {
  mousex = 0; mousey = 0;
  state = malloc(sizeof(GameState));

  state->quit = false;
  
  state->scanButton = (Button) {10, 10, false};
  state->mineButton = (Button) {10, 30, false};

  state->scanLight = (ScanLight) {30, 10, false};
  state->mineLight = (MineLight) {30, 30, false};

  state->playerX = 0;
  state->playerY = 0;
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
    }
  }
}

void game_loop(GameState *state) {
  while(!state->quit) {
    handle_input(state);

    SDL_Rect rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderFillRect(renderer, &rect);

    render_ui(renderer, state);
    SDL_RenderPresent(renderer);
  }
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
  }
}

bool mouse_inside_bbox(int x, int y, int width, int height) {
  return (mousex > x
          && mousex < x + width
          && mousey > y
          && mousey < y + height);
}
