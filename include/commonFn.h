#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H
#define INF (int)1e9
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
// REPLAY_BTN_X, HEADER_HEIGHT / 2 - REPLAY_BTN_HEIGHT / 2, REPLAY_BTN_WIDTH, REPLAY_BTN_HEIGHT
static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;
static SDL_Texture *square;
static SDL_Texture *ballTexture[8];
static SDL_Texture *numberTexture[10];
static SDL_Event e;
static SDL_Texture *backgroundTexture;
static SDL_Texture *startBtnTexture;
static SDL_Texture *exitBtnTexture;
static SDL_Texture *headerBorderTexture;
static SDL_Texture *replayBtnTexture;
static SDL_Texture *gameOverMenuTexture;
static SDL_Rect startButtonRect;
static SDL_AudioSpec audioSpecMove;
static Uint32 audioLenMove;
static Uint8* audioBufferMove;
static SDL_AudioSpec audioSpecMatch;
static Uint32 audioLenMatch;
static Uint8* audioBufferMatch;
const int WINDOW_WIDTH = 576; // phải chia hết cho num size
const int WINDOW_HEIGHT = 576 + 128;
const int START_BUTTON_WIDTH = 120;
const int START_BUTTON_HEIGHT = 50;
const int START_BUTTON_X = (WINDOW_WIDTH / 2) - (START_BUTTON_WIDTH / 2);
const int START_BUTTON_Y = WINDOW_HEIGHT / 2;
const int HEADER_WIDTH = 576;
const int HEADER_HEIGHT = 128;
const int EXIT_BUTTON_Y = WINDOW_HEIGHT / 2 + START_BUTTON_HEIGHT + 15;
const int SQUARE_WIDTH = 64;
const int SQUARE_HEIGHT = 64;
const int ROWS = 9;
const int COLS = 9;
const int GAMEBOARD_START_Y = WINDOW_HEIGHT - (ROWS * SQUARE_HEIGHT);
const int REPLAY_BTN_WIDTH = 50;
const int REPLAY_BTN_HEIGHT = 50;
const int REPLAY_BTN_X = 20;
const int REPLAY_BTN_Y = HEADER_HEIGHT / 2 - REPLAY_BTN_HEIGHT / 2;
const int GAMEOVER_REPLAY_X = WINDOW_WIDTH / 2 - REPLAY_BTN_WIDTH / 2;
const int GAMEOVER_REPLAY_Y = WINDOW_HEIGHT / 2 + 50;
const float BALL_PROBABILITY = 0.2; // Xác suất một ô có quả bóng (20%)
const int SMALL_BALL = 2;

namespace commonFn
{
    SDL_Texture *LoadTexture(const char *fileName, SDL_Renderer *renderer);
    void close();
};

#endif