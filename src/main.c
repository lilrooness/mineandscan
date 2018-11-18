#include "game.h"

int main(int argc, char **argv) {

  if(render_init() > 0) {
    return 1;
  }

  ambiance = Mix_LoadMUS("res/fridge-ambiance.wav");
  radar_ping = Mix_LoadWAV("res/radar_ping.wav");
  radar_ping_channel = -1;

  if(ambiance == NULL) {
    printf("could not load fridge-ambiance.wav SDL_mixer Error: %s\n", Mix_GetError());
    return 1;
  }

  if(radar_ping == NULL) {
    printf("could not load radar_ping.wav SDL_mixer Error: %s\n", Mix_GetError());
    return 1;
  }

  game_init();

  Mix_PlayMusic(ambiance, -1);
  
  game_loop(state);

  SDL_DestroyWindow(window);

  Mix_FreeMusic(ambiance);
  Mix_FreeChunk(radar_ping);

  IMG_Quit();
  Mix_Quit();
  SDL_Quit();
  return 0;
}

