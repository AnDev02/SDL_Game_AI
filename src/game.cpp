#include "../include/game.h"

game::game()
{
    gameBoard = vector<vector<ball>>(ROWS, vector<ball>(COLS, {INF, INF, INF, INF}));
    path.clear();
    shortestPath.clear();
    grid = vector<vector<ball>>(ROWS, vector<ball>(COLS, {INF, INF, INF, INF}));
    visited = vector<vector<bool>>(ROWS, vector<bool>(COLS, false));
    ballSelected = false;
    ballX = -1;
    ballY = -1;
    targetX = -1;
    targetY = -1;
    ballMoving = false;
    turn = 0;
    moveSoundThreadReady = false;
    quitMoveSound = false;
    isGameOver = false;
}

mutex game::myMutex;
condition_variable game::cv;
bool game::moveSoundThreadReady;
bool game::quitMoveSound = false;
int jumpStartTime = 0;
int initialY = 0;
int tempBallX;
int tempBallY;

game::~game() {}

void game::dijkstra(int startX, int startY, int endX, int endY)
{
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    // Đặt lại các biến
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            visited[i][j] = false;
            if (gameBoard[i][j].cost != 1000)
            {
                gameBoard[i][j].cost = INF;
            }
        }
    }
    path.clear();
    shortestPath.clear();
    priority_queue<ball, vector<ball>, greater<ball>> pq;
    pq.push(ball(startX, startY, 1000, INF));
    int x = 0, y = 0, cost = 0, newX = 0, newY = 0;
    bool pathFound = false;
    while (!pq.empty())
    {
        ball current = pq.top();
        pq.pop();
        x = current.x;
        y = current.y;
        cost = current.cost;
        if (visited[x][y])
            continue;
        visited[x][y] = true;

        for (int i = 0; i < 4; i++)
        {
            newX = x - dx[i];
            newY = y - dy[i];
            if ((newX < ROWS && newX >= 0) && (newY < COLS && newY >= 0) && gameBoard[newX][newY].cost != 1000)
            {
                if (newX == endX && newY == endY)
                    pathFound = true;
                int newDist = cost + 1;
                if (newDist < gameBoard[newX][newY].cost)
                {
                    path.push_back(make_tuple(newX, newY, newDist));
                    pq.push(ball(newX, newY, newDist, 1));
                }
            }
        }
    }
    if (pathFound == false)
        return;

    // retrace path
    int currentX = endX;
    int currentY = endY;
    while (currentX != startX || currentY != startY)
    {
        shortestPath.push_back(make_tuple(currentX, currentY, 1000));
        int parentX, parentY;
        for (const auto &node : path)
        {
            if ((abs(currentX - get<0>(node)) == 1 && currentY == get<1>(node)) || (abs(currentY - get<1>(node)) == 1 && currentX == get<0>(node)))
            {
                parentX = get<0>(node);
                parentY = get<1>(node);
                break;
            }
        }
        if (currentX == startX || currentY == startY)
            break;
        currentX = parentX;
        currentY = parentY;
    }
    reverse(shortestPath.begin(), shortestPath.end());
}

void game::audioCallbackMove(void *userData, Uint8 *stream, int len)
{
    if (audioLenMove == 0)
    {
        return;
    }
    len = (len > audioLenMove) ? audioLenMove : len;
    SDL_memcpy(stream, audioBufferMove, len);
    audioBufferMove += len;
    audioLenMove -= len;
}

void game::audioCallbackMatch(void *userData, Uint8 *stream, int len)
{
    if (audioLenMatch == 0)
    {
        return;
    }

    len = (len > audioLenMatch) ? audioLenMatch : len;
    SDL_memcpy(stream, audioBufferMatch, len);

    audioBufferMatch += len;
    audioLenMatch -= len;
}

void game::initializeGameBoard()
{
    float randomProbability = 0;
    int randColor = 0;
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int x = 0; x < ROWS; x++)
    {
        for (int y = 0; y < COLS; y++)
        {
            randomProbability = static_cast<float>(rand()) / RAND_MAX;
            if (randomProbability <= BALL_PROBABILITY)
            {
                randColor = rand() % 4;
                gameBoard[x][y].x = x * SQUARE_WIDTH;
                gameBoard[x][y].y = GAMEBOARD_START_Y + y * SQUARE_HEIGHT;
                gameBoard[x][y].cost = 1000;
                gameBoard[x][y].value = randColor;
            }
        }
    }
}

void game::loadAudio(const char *filePath, SDL_AudioSpec &spec, Uint32 &len, Uint8 *&buffer)
{
    SDL_AudioSpec wavSpec;
    Uint8 *wavStart;
    Uint32 wavLength;

    // Đọc tệp âm thanh WAV
    if (SDL_LoadWAV(filePath, &wavSpec, &wavStart, &wavLength) == nullptr)
    {
        std::cerr << "Failed to load audio file: " << SDL_GetError() << std::endl;
        return;
    }

    // Đặt buffer là đầu của dữ liệu WAV
    buffer = wavStart;

    // Đặt len là độ dài của dữ liệu WAV
    len = wavLength;

    // Đặt thông số của spec
    spec.freq = wavSpec.freq;
    spec.format = wavSpec.format;
    spec.channels = wavSpec.channels;
    spec.samples = wavSpec.samples;
}

void game::playMoveSound()
{
    std::unique_lock<std::mutex> lock(myMutex);

    while (!quitMoveSound)
    {
        if (quitMoveSound)
        {
            break;
        }
        loadAudio("../assets/sounds/sd_0.wav", audioSpecMove, audioLenMove, audioBufferMove);
        SDL_PauseAudio(0); // Bắt đầu phát âm thanh di chuyển
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        SDL_PauseAudio(1);
        moveSoundThreadReady = false;
        cv.notify_one();
        cv.wait(lock, []
                { return moveSoundThreadReady || quitMoveSound; });
    }
}

void game::playMatchSound()
{
    loadAudio("../assets/sounds/whoosh.wav", audioSpecMatch, audioLenMatch, audioBufferMatch);
    SDL_PauseAudio(0); // Bắt đầu phát âm thanh ăn quả
}

void game::renderGame(SDL_Renderer *renderer)
{
    SDL_Rect headerBorderRect = {0, 0, HEADER_WIDTH, HEADER_HEIGHT};
    SDL_RenderCopy(renderer, headerBorderTexture, nullptr, &headerBorderRect);
    SDL_Rect replayBtnRect = {REPLAY_BTN_X, REPLAY_BTN_Y, REPLAY_BTN_WIDTH, REPLAY_BTN_HEIGHT};
    SDL_RenderCopy(renderer, replayBtnTexture, nullptr, &replayBtnRect);
    renderScore(renderer, score, 200, HEADER_HEIGHT / 2 - 35 / 2);
    for (int x = 0; x < ROWS; x++)
    {
        for (int y = 0; y < COLS; y++)
        {
            SDL_Rect squareRect = {x * SQUARE_WIDTH, GAMEBOARD_START_Y + y * SQUARE_HEIGHT, SQUARE_WIDTH, SQUARE_HEIGHT};
            SDL_RenderCopy(renderer, square, nullptr, &squareRect);
        }
    }
    for (int x = 0; x < ROWS; x++)
    {
        for (int y = 0; y < COLS; y++)
        {
            int ballIndex = gameBoard[x][y].value;
            if (gameBoard[x][y].cost == 1000 || ballIndex > 3 && ballIndex < 8)
            {
                SDL_Rect nodeRect = {gameBoard[x][y].x, gameBoard[x][y].y, SQUARE_WIDTH, SQUARE_HEIGHT};
                SDL_RenderCopy(renderer, ballTexture[ballIndex], nullptr, &nodeRect);
            }
        }
    }
}

void game::replay()
{
    gameBoard = vector<vector<ball>>(ROWS, vector<ball>(COLS, {INF, INF, INF, INF}));
    path.clear();
    shortestPath.clear();
    score = 0;
    isGameOver = false;
    initializeGameBoard();
    generateTinyBalls();
}

void game::startGame(SDL_Renderer *renderer, game *line98)
{
    std::vector<std::vector<ball>> compareGameBoard(ROWS, std::vector<ball>(COLS, {INF, INF, INF, INF}));
    initializeGameBoard();
    generateTinyBalls();
    bool quit = false;
    int turn = 0;

    thread moveSoundThread(playMoveSound);
    while (!quit)
    {
        turn++;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                quit = true;
            handleInputMouse(e, renderer);
        }
        switch (currentGameState)
        {
        case GAMESTATE_MENU:
            showGameMenu(renderer);
            break;
        case GAMESTATE_PLAYING:
            renderGame(renderer);
            break;
        }
        if (countEmptyNode() <= 3)
        {
            gameOver(renderer);
            isGameOver = true;
        }
        if (gameBoard != compareGameBoard)
        {
            SDL_RenderPresent(renderer);
        }
    }
    quitMoveSound = true;
    cv.notify_one();
    moveSoundThread.join();
}

void game::renderScore(SDL_Renderer *renderer, int score, int x, int y)
{
    int x_rect = x;
    string scoreString = std::to_string(score);
    for (char digit : scoreString)
    {
        int digitValue = digit - '0';
        SDL_Rect numRect = {x_rect, y, 35, 35};
        SDL_RenderCopy(renderer, numberTexture[digitValue], NULL, &numRect);
        x_rect += 35;
    }
}

void game::setUpTexture(SDL_Renderer *renderer)
{
    square = commonFn::LoadTexture("../assets/images/square.png", renderer);
    if (!square)
    {
        cerr << "Failed to load square texture." << endl;
        return;
    }

    backgroundTexture = commonFn::LoadTexture("../assets/images/backgroundLine98.png", renderer);
    if (!backgroundTexture)
    {
        cerr << "Failed to load background texture." << endl;
        return;
    }

    startBtnTexture = commonFn::LoadTexture("../assets/images/startButton.png", renderer);
    if (!startBtnTexture)
    {
        cerr << "Failed to load start button texture." << endl;
        return;
    }

    exitBtnTexture = commonFn::LoadTexture("../assets/images/exitButton.png", renderer);
    if (!exitBtnTexture)
    {
        cerr << "Failed to load start button texture." << endl;
        return;
    }

    headerBorderTexture = commonFn::LoadTexture("../assets/images/gameBoardHeader.png", renderer);
    if (!headerBorderTexture)
    {
        cerr << "Failed to load gameboard header texture." << endl;
        return;
    }

    replayBtnTexture = commonFn::LoadTexture("../assets/images/replayButton.png", renderer);
    if (!replayBtnTexture)
    {
        cerr << "Failed to load replay button texture." << endl;
        return;
    }

    gameOverMenuTexture = commonFn::LoadTexture("../assets/images/gameOverMenu.png", renderer);
    if (!gameOverMenuTexture)
    {
        cerr << "Failed to load game over menu texture." << endl;
        return;
    }

    const char *numberPaths[] = {
        "../assets/images/n0.png",
        "../assets/images/n1.png",
        "../assets/images/n2.png",
        "../assets/images/n3.png",
        "../assets/images/n4.png",
        "../assets/images/n5.png",
        "../assets/images/n6.png",
        "../assets/images/n7.png",
        "../assets/images/n8.png",
        "../assets/images/n9.png"};

    for (int i = 0; i < 10; i++)
    {
        numberTexture[i] = commonFn::LoadTexture(numberPaths[i], renderer);
        if (!numberTexture[i])
        {
            cerr << "Failed to load num texture " << i << "." << endl;
            return;
        }
    }
    const char *ballPaths[] = {
        "../assets/images/ball0.png",
        "../assets/images/ball1.png",
        "../assets/images/ball2.png",
        "../assets/images/ball3.png",
        "../assets/images/ball4.png",
        "../assets/images/ball5.png",
        "../assets/images/ball6.png",
        "../assets/images/ball7.png"};

    for (int i = 0; i < 8; ++i)
    {
        ballTexture[i] = commonFn::LoadTexture(ballPaths[i], renderer);
        if (!ballTexture[i])
        {
            cerr << "Failed to load ball texture " << i << "." << endl;
            return;
        }
    }

    // Khởi tạo SDL Audio Spec
    audioSpecMove.freq = 44100;
    audioSpecMove.format = AUDIO_S16SYS;
    audioSpecMove.channels = 1;
    audioSpecMove.samples = 2048;
    audioSpecMove.callback = audioCallbackMove;
    if (SDL_GetAudioStatus() == SDL_AUDIO_STOPPED)
    {
        if (SDL_OpenAudio(&audioSpecMove, nullptr) < 0)
        {
            std::cerr << "SDL could not open audio! SDL Error: " << SDL_GetError() << std::endl;
            return;
        }
    }
    audioSpecMatch.freq = 44100;
    audioSpecMatch.format = AUDIO_S16SYS;
    audioSpecMatch.channels = 1;
    audioSpecMatch.samples = 2048;
    audioSpecMatch.callback = audioCallbackMatch;
    if (SDL_GetAudioStatus() == SDL_AUDIO_STOPPED)
    {
        if (SDL_OpenAudio(&audioSpecMatch, nullptr) < 0)
        {
            std::cerr << "SDL could not open audio! SDL Error: " << SDL_GetError() << std::endl;
            return;
        }
    }
}

void game::showGameMenu(SDL_Renderer *renderer)
{
    SDL_Rect gameMenuRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, &gameMenuRect);
    SDL_Rect startButtonRect = {START_BUTTON_X, START_BUTTON_Y, START_BUTTON_WIDTH, START_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, startBtnTexture, nullptr, &startButtonRect);
    SDL_Rect exitButtonRect = {START_BUTTON_X, EXIT_BUTTON_Y, START_BUTTON_WIDTH, START_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, exitBtnTexture, nullptr, &exitButtonRect);
}

int game::countEmptyNode()
{
    int result = 0;
    for (int x = 0; x < ROWS; x++)
        for (int y = 0; y < COLS; y++)
        {
            if (gameBoard[x][y].cost != 1000 && !(gameBoard[x][y].value >= 0 && gameBoard[x][y].value < 8))
                result++;
        }
    return result;
}

void game::generateTinyBalls()
{
    int count = SMALL_BALL;
    float randomProbability = 0;
    if (count > countEmptyNode())
        count = countEmptyNode();

    srand(static_cast<unsigned int>(time(nullptr)));
    while (count >= 0)
    {
        int randX = rand() % ROWS;
        int randY = rand() % COLS;
        if (!(gameBoard[randX][randY].value >= 0 && gameBoard[randX][randY].value < 8))
        {
            int randColor = rand() % 4 + 4;
            gameBoard[randX][randY].x = randX * SQUARE_WIDTH;
            gameBoard[randX][randY].y = GAMEBOARD_START_Y + randY * SQUARE_HEIGHT;
            gameBoard[randX][randY].cost = INF;
            gameBoard[randX][randY].value = randColor;
            count--;
            currentTinyBall.push_back(make_tuple(randX * SQUARE_WIDTH, GAMEBOARD_START_Y + randY * SQUARE_HEIGHT));
        }
    }
}

void game::resizeBalls()
{
    for (int x = 0; x < ROWS; x++)
    {
        for (int y = 0; y < COLS; y++)
        {
            auto prevTinyBall = find(currentTinyBall.begin(), currentTinyBall.end(), make_tuple(x * SQUARE_WIDTH, GAMEBOARD_START_Y + y * SQUARE_HEIGHT));
            if (gameBoard[x][y].value > 3 && gameBoard[x][y].value < 8 && prevTinyBall == currentTinyBall.end())
            {
                gameBoard[x][y].x = x * SQUARE_WIDTH;
                gameBoard[x][y].y = GAMEBOARD_START_Y + y * SQUARE_HEIGHT;
                gameBoard[x][y].cost = 1000;
                gameBoard[x][y].value = gameBoard[x][y].value - 4;

                vector<tuple<int, int>> checkRemove = removeBalls(x, y);
                if (!checkRemove.empty())
                {
                    {
                        lock_guard<mutex> lock(myMutex);
                        moveSoundThreadReady = true;
                        cv.notify_one();
                    }

                    for (const auto &cell : checkRemove)
                    {
                        gameBoard[get<0>(cell)][get<1>(cell)].x = INF;
                        gameBoard[get<0>(cell)][get<1>(cell)].y = INF;
                        gameBoard[get<0>(cell)][get<1>(cell)].cost = INF;
                        gameBoard[get<0>(cell)][get<1>(cell)].value = INF;
                    }

                    {
                        lock_guard<mutex> lock(myMutex);
                        cv.notify_one();
                    }
                }
            }
        }
    }
    currentTinyBall.clear();
}

vector<tuple<int, int>> game::removeBalls(int targetX, int targetY)
{
    vector<tuple<int, int>> list_remove_ball;
    int valueToMatch = gameBoard[targetX][targetY].value;
    int count = 0;
    int currentX = -1;
    int currentY = -1;

    // check hàng dọc
    for (int x = targetX; x >= 0; x--)
    {
        if (x >= ROWS)
            break;
        else if (gameBoard[x][targetY].value != valueToMatch)
            break;
        currentX = x;
    }
    if (currentX != -1)
    {
        for (int x = currentX; x <= currentX + 4; x++)
        {
            if (x >= ROWS)
                break;
            if (gameBoard[x][targetY].value != valueToMatch)
                break;
            else
                list_remove_ball.push_back(make_tuple(x, targetY));
        }
    }

    if (list_remove_ball.size() != 5)
        list_remove_ball.clear();
    else
    {
        score += 50;
        return list_remove_ball;
    }

    // check hàng ngang
    for (int y = targetY; y >= 0; y--)
    {
        if (y >= ROWS)
            break;
        if (gameBoard[targetX][y].value != valueToMatch)
            break;
        currentY = y;
    }
    if (currentY != -1)
    {
        for (int y = currentY; y <= currentY + 4; y++)
        {
            if (gameBoard[targetX][y].value != valueToMatch)
                break;
            else
                list_remove_ball.push_back(make_tuple(targetX, y));
        }
    }
    if (list_remove_ball.size() != 5)
        list_remove_ball.clear();
    else
    {
        score += 50;
        return list_remove_ball;
    }

    // check chéo trái
    currentX = -1;
    int y = targetY;
    for (int x = targetX; x >= 0; x--)
    {
        if (gameBoard[x][y].value != valueToMatch)
            break;
        currentX = x;
        currentY = y;
        y--;
    }
    if (currentX != -1 && currentY != -1)
    {
        y = currentY;
        for (int x = currentX; x <= currentX + 4; x++)
        {
            if (x >= ROWS)
                break;
            if (y >= COLS)
                break;
            if (gameBoard[x][y].value != valueToMatch)
                break;
            else
                list_remove_ball.push_back(make_tuple(x, y));
            y++;
        }
    }
    if (list_remove_ball.size() != 5)
        list_remove_ball.clear();
    else
    {
        score += 50;
        return list_remove_ball;
    }

    // check chéo phải
    currentX = -1;
    currentY = -1;
    y = targetY;
    for (int x = targetX; x < ROWS; x++)
    {
        if (gameBoard[x][y].value != valueToMatch)
            break;
        currentX = x;
        currentY = y;
        y--;
    }

    if (currentX != -1 && currentY != -1)
    {
        y = currentY;
        for (int x = currentX; x >= currentX - 4; x--)
        {
            if (x < 0)
                break;
            if (x >= ROWS)
                break;
            if (y >= COLS)
                break;
            if (gameBoard[x][y].value != valueToMatch)
                break;
            else
                list_remove_ball.push_back(make_tuple(x, y));
            y++;
        }
    }
    if (list_remove_ball.size() != 5)
        list_remove_ball.clear();
    else
    {
        score += 50;
        return list_remove_ball;
    }
    return list_remove_ball;
}

void game::gameOver(SDL_Renderer *renderer)
{
    SDL_Rect gameOverMenuRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderCopy(renderer, gameOverMenuTexture, NULL, &gameOverMenuRect);
    renderScore(renderer, score, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    SDL_Rect btnReplay = {GAMEOVER_REPLAY_X, GAMEOVER_REPLAY_Y, REPLAY_BTN_WIDTH, REPLAY_BTN_HEIGHT};
    SDL_RenderCopy(renderer, replayBtnTexture, NULL, &btnReplay);
}

void game::handleInputMouse(SDL_Event e, SDL_Renderer *renderer)
{
    if (!ballMoving)
    {
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            switch (currentGameState)
            {
            case GAMESTATE_MENU:
                if ((x >= START_BUTTON_X && x <= START_BUTTON_X + START_BUTTON_WIDTH) && (y >= START_BUTTON_Y && y <= START_BUTTON_Y + START_BUTTON_HEIGHT))
                    currentGameState = GameState::GAMESTATE_PLAYING;
                break;
            case GAMESTATE_PLAYING:
                if (isGameOver)
                {
                    int x_val = WINDOW_WIDTH / 2 - REPLAY_BTN_WIDTH / 2;
                    int y_val = WINDOW_HEIGHT / 2 + 200;
                    if (x >= GAMEOVER_REPLAY_X && x <= GAMEOVER_REPLAY_X + REPLAY_BTN_WIDTH && y >= GAMEOVER_REPLAY_Y && y <= GAMEOVER_REPLAY_Y + REPLAY_BTN_WIDTH)
                    {
                        isReplay = true;
                        replay();
                    }
                }
                if (x >= REPLAY_BTN_X && x <= REPLAY_BTN_X + REPLAY_BTN_WIDTH && y >= REPLAY_BTN_Y && y <= REPLAY_BTN_X + REPLAY_BTN_WIDTH)
                {
                    isReplay = true;
                    replay();
                }
                if (!ballSelected)
                {
                    ballX = x / SQUARE_WIDTH;
                    ballY = y / SQUARE_HEIGHT - 2;
                    if (gameBoard[ballX][ballY].cost == 1000)
                    {
                        ballSelected = true;
                        gameBoard[ballX][ballY].isSelected = true;
                        updateBallPosition(ballX, ballY);
                    }
                    ballMoving = false;
                }
                else
                {
                    targetX = x / SQUARE_WIDTH;
                    targetY = y / SQUARE_HEIGHT - 2;
                    ballSelected = false;
                    gameBoard[ballX][ballY].isSelected = false;
                    updateBallPosition(ballX, ballY);
                    if (gameBoard[targetX][targetY].cost != 1000)
                    {
                        ballMoving = true;
                        shortestPath.clear();
                        dijkstra(ballX, ballY, targetX, targetY);
                        handleMoveBall(renderer);
                        if (shortestPath.size() != 0)
                        {
                            generateTinyBalls();
                            resizeBalls();
                        }
                    }
                }
                break;
            }
        }
    }
}

void game::updateBallPosition(int x, int y)
{
    int temp = tempBallY;
    if (gameBoard[x][y].isSelected)
    {
        gameBoard[x][y].y -= 10;
    }
    else
    {
        gameBoard[x][y].y += 10;
    }
}

void game::handleMoveBall(SDL_Renderer *renderer)
{
    int x_move, y_move, weight_move;
    int count = 0;
    if (ballMoving)
    {
        for (const tuple<int, int, int> &step : shortestPath)
        {
            tie(x_move, y_move, weight_move) = step;
            if (weight_move != 0 && x_move >= 0 && x_move < ROWS && y_move >= 0 && y_move < COLS)
            {
                gameBoard[ballX][ballY].x = x_move * SQUARE_WIDTH;
                gameBoard[ballX][ballY].y = GAMEBOARD_START_Y + y_move * SQUARE_HEIGHT;
                renderGame(renderer);
                SDL_RenderPresent(renderer);
                SDL_Delay(100);
            }
        }
        ballMoving = false;
        if (shortestPath.size() != 0)
        {
            ball temp = gameBoard[targetX][targetY];
            gameBoard[targetX][targetY] = gameBoard[ballX][ballY];
            gameBoard[ballX][ballY] = {INF, INF, INF, INF};
            vector<tuple<int, int>> checkRemove = removeBalls(targetX, targetY);
            if (!checkRemove.empty())
            {
                {
                    lock_guard<mutex> lock(myMutex);
                    moveSoundThreadReady = true;
                    cv.notify_one();
                }

                for (const auto &cell : checkRemove)
                {
                    gameBoard[get<0>(cell)][get<1>(cell)].x = INF;
                    gameBoard[get<0>(cell)][get<1>(cell)].y = INF;
                    gameBoard[get<0>(cell)][get<1>(cell)].cost = INF;
                    gameBoard[get<0>(cell)][get<1>(cell)].value = INF;
                }

                {
                    lock_guard<mutex> lock(myMutex);
                    cv.notify_one();
                }
            }
        }
    }
}