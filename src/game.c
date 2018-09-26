#include "game.h"

void game_init() {
  state = malloc(sizeof(GameState));
  
  state->scanButton = (Button) {10, 10, false};
  state->mineButton = (Button) {10, 30, false};

  state->scanLight = (ScanLight) {30, 10, false};
  state->mineLight = (MineLight) {30, 30, false};

  state->playerX = 0;
  state->playerY = 0;
}
