#ifdef UI_H
#else

#include <stdbool.h>

#include "sprites.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
//KEEP THIS ASPECT RATIO!!!!
const int LOG_W = 100;
const int LOG_H = 75;
const float WIDTH_FAC = 6.4f;
const float HEIGHT_FAC = 10.4f;

typedef struct {
  float x;
  float y;
  bool down;
} Button;

typedef struct {
  float x;
  float y;
  bool on;
  bool color; // 1=green | 0=red
} Led;

typedef struct {
  float x;
  float y;
  bool on;
} MineLight;

typedef struct {
  float x;
  float y;
  bool on;
} ScanLight;

#define UI_H
#endif
