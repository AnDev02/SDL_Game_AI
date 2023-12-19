#ifndef GAME_H
#define GAME_H
#pragma once
#include "./commonFn.h"
#include "./ball.h"

class game
{
private:
    int dx[4];
    int dy[4];
    vector<vector<ball>> gameBoard;
    vector<tuple<int, int, int>> path;
    vector<tuple<int, int, int>> shortestPath;
    vector<tuple<int, int>> currentTinyBall;
    vector<vector<ball>> grid;
    vector<vector<bool>> visited;
    bool ballSelected = false;
    // Tọa độ của quả bóng
    int ballX = -1;
    int ballY = -1;
    // Tọa độ của ô mục tiêu
    int targetX = -1;
    int targetY = -1;
    bool ballMoving = false;
    int turn = 0;
    int score = 0;
    static mutex myMutex;
    static condition_variable cv;
    static bool moveSoundThreadReady;
    static bool moveSoundThreadFinished;
    static bool quitMoveSound;
    bool isGameOver = false;
    enum GameState
    {
        GAMESTATE_MENU,
        GAMESTATE_PLAYING
    };

public:
    void updateBallPosition(int x, int y);
    static void audioCallbackMove(void *userData, Uint8 *stream, int len);
    static void audioCallbackMatch(void *userData, Uint8 *stream, int len);
    bool isReplay = false;
    GameState currentGameState = GameState::GAMESTATE_MENU;
    void dijkstra(int startX, int startY, int endX, int endY);
    void initializeGameBoard();
    void renderGame(SDL_Renderer *renderer);
    void startGame(SDL_Renderer *renderer, game *line98);
    int countEmptyNode();
    void generateTinyBalls();
    void resizeBalls();
    vector<tuple<int, int>> removeBalls(int targetX, int targetY);
    void handleInputMouse(SDL_Event e, SDL_Renderer *renderer);
    void handleMoveBall(SDL_Renderer *renderer);
    void setUpTexture(SDL_Renderer *renderer);
    void showGameMenu(SDL_Renderer *renderer);
    void renderScore(SDL_Renderer *renderer, int score, int x, int y);
    void gameOver(SDL_Renderer *renderer);
    void replay();
    static void loadAudio(const char *filePath, SDL_AudioSpec &spec, Uint32 &len, Uint8 *&buffer);
    static void playMoveSound();
    static void playMatchSound();
    game();
    ~game();
};

#endif