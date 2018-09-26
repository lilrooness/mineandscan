#include "game.h"

int main(int argc, char **argv) {

  if(render_init() > 0) {
    return 1;
  }


  game_init();

  SDL_Rect rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
  SDL_RenderFillRect(renderer, &rect);
  render_ui(renderer, state);
  SDL_RenderPresent(renderer);

  SDL_Delay(2000);

  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}

