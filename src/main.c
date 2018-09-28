#include "game.h"

int main(int argc, char **argv) {

  if(render_init() > 0) {
    return 1;
  }

  game_init();

  game_loop(state);

  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}

