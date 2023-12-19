#include "../include/commonFn.h"
#include "../include/ball.h"
#include "../include/game.h"
#define INF (int)1e9

// Khởi tạo cửa sổ SDLx
bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}

	window = SDL_CreateWindow("Line 98", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}
	return true;
}

int main(int argc, char *args[])
{
	if (!init())
	{
		return 1;
	}

	game line98;
	line98.setUpTexture(renderer);
	line98.initializeGameBoard();
	line98.startGame(renderer, &line98);
	commonFn::close();
	return 0;
}
