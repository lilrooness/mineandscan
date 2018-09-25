#ifdef GAME_H
#else

#include "ui.h"

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
} GameState;

int playerX = 0;
int playerY = 0;

GameState *state;

void game_init() {
  state = malloc(sizeof(GameState));
  
  state->scanButton = (Button) {10, 10, false};
  state->mineButton = (Button) {10, 30, false};

  state->scanLight = (ScanLight) {30, 10, false};
  state->mineLight = (MineLight) {30, 30, false};
}

#define GAME_H
#endif
