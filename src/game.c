#include "game.h"

void game_init() {
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
