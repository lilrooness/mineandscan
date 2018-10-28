#include "game.h"

void game_init() {
  mousex = 0; mousey = 0;

  state = malloc(sizeof(GameState));
  nenemies = 10;
  nmines = 30;
  state->enemies = malloc(nenemies * sizeof(Enemy));
  state->mines = malloc(nmines * sizeof(Mine));
  restart_game(state);
}

void restart_game(GameState *state) {

  up_key=false; down_key=false;
  left_key=false; right_key=false;

  state->mode = PLAY;

  state->quit = false;

  state->scanButton = (Button) {3, 8, false};
  state->mineButton = (Button) {3, 33, true};

  state->scanLight = (ScanLight) {17, 8, false};
  state->mineLight = (MineLight) {17, 33, true};

  state->playerX = 100;
  state->playerY = 0;

  state->screen_mode = 1;

  int maxRand = 100;

  for(int i=0; i<nenemies; i++) {
    int x = (int)rand()%maxRand;
    int y = (int)rand()%maxRand;
    state->enemies[i].x = x;
    state->enemies[i].y = y;
    state->enemies[i].alerted = false;
  }

  for(int i=0; i<nmines; i++) {
    int x = (int)rand()%maxRand;
    int y = (int)rand()%maxRand;
    state->mines[i].x = x;
    state->mines[i].y = y;
    state->mines[i].remaining_resource = 50;
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

    if(state->mode == PLAY) {
        do_play_tick(state);
    } else if (state->mode == GAME_OVER) {
        do_gameover_tick(state);
    }


    SDL_Rect rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderFillRect(renderer, &rect);

    if(state->mode == PLAY) {
        render_ui(renderer, state);
    } else if(state->mode == GAME_OVER) {
        render_gameover_screen(renderer, state);
    }


    SDL_RenderPresent(renderer);

    int frameEnd = SDL_GetTicks();
    int frameTime = frameEnd - frameStart;

    if(frameTime < (1000 / FRAMES_PER_SECOND)) {
      SDL_Delay((1000/FRAMES_PER_SECOND) - frameTime);
    }
  }
}

void do_gameover_tick(GameState *state) {
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0) {
        if(e.type == SDL_KEYDOWN) {
            if(e.key.keysym.sym == SDLK_r) {
                restart_game(state);
            }
        } else if(e.type == SDL_QUIT) {
            state->quit = true;
        }
    }
}

void do_play_tick(GameState *state) {
    for(int i=0; i<nenemies; i++) {
        update_enemy(state->enemies + (i*sizeof(Enemy)), state);
    }

    handle_input(state);


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
    } else {
      state -> screen_mode = -1;
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

    if(state->mineLight.on) {
      state->screen_mode = 1;
      state->scanLight.on = false;
      state->scanButton.down = false;
    } else {
      state->screen_mode = -1;
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

bool enemy_in_range(Enemy *e, GameState * state, int range) {
  int px = state->playerX;
  int py = state->playerY;

  if(e->x > px - range
     && e->x < px + range
     && e->y > py - range
     && e->y < py + range) {

    return true;
  }

  return false;
}

bool mine_in_range(Mine *m, GameState * state, int range) {
  int px = state->playerX;
  int py = state->playerY;

  if(m->x > px - range
     && m->x < px + range
     && m->y > py - range
     && m->y < py + range) {

    return true;
  }

  return false;
}

SDL_Point get_approx_vector_to_player(Enemy *enemy, GameState *state) {
    SDL_Point vector = {state->playerX - enemy->x, state->playerY - enemy->y};
    if(vector.x > 0) {
        vector.x = 1;
    } else if(vector.x < 0) {
        vector.x = -1;
    } else {
        vector.x = 0;
    }

    if(vector.y > 0) {
        vector.y = 1;
    } else if(vector.y < 0) {
        vector.y = -1;
    } else {
        vector.y = 0;
    }

    return vector;
}

void update_enemy(Enemy *enemy, GameState *state) {
    float dist = distance(state->playerX, state->playerY, enemy->x, enemy->y);

    if(dist <= KILL_RANGE) {
        // YOU DIED
        state->mode = GAME_OVER;
        return;
    }

    if(dist <= ATTRACTION_RANGE) {
        SDL_Point vector = get_approx_vector_to_player(enemy, state);
        enemy->x += vector.x;
        enemy->y += vector.y;
    }
}
