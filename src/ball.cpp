#include "../include/ball.h"

ball::~ball()
{
}

void ball::moveBall()
{
	// int x_move, y_move, weight_move;
	// int count = 0;
	// if (ballMoving)
	// {
	// 	for (const tuple<int, int, int> &step : shortestPath)
	// 	{
	// 		tie(x_move, y_move, weight_move) = step;
	// 		if (weight_move != 0 && x_move >= 0 && x_move < ROWS && y_move >= 0 && y_move < COLS)
	// 		{
	// 			gameBoard[ballX][ballY].x = x_move * SQUARE_WIDTH;
	// 			gameBoard[ballX][ballY].y = y_move * SQUARE_HEIGHT;
	// 			renderGame();
	// 			SDL_RenderPresent(renderer);
	// 		}
	// 	}
	// 	ballMoving = false;
	// 	if (shortestPath.size() != 0)
	// 	{
	// 		ball temp = gameBoard[targetX][targetY];
	// 		gameBoard[targetX][targetY] = gameBoard[ballX][ballY];
	// 		gameBoard[ballX][ballY] = {INF, INF, INF, INF};
	// 		vector<tuple<int, int>> checkRemove = removeBalls();
	// 		if (!checkRemove.empty())
	// 		{
	// 			for (const auto &cell : checkRemove)
	// 			{
	// 				gameBoard[get<0>(cell)][get<1>(cell)].x = INF;
	// 				gameBoard[get<0>(cell)][get<1>(cell)].y = INF;
	// 				gameBoard[get<0>(cell)][get<1>(cell)].cost = INF;
	// 				gameBoard[get<0>(cell)][get<1>(cell)].value = INF;
	// 			}
	// 		}
	// 	}
	// }
}