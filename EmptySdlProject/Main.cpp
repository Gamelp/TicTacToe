#include <iostream>
#include <cstdlib>
#include <algorithm> 

#include <SDL.h>

#include "Constants.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

Game game;
int corner = 3;

bool running = false;

//Initializse SDL system
bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL_Init failed!");
		return false;
	}

	window = SDL_CreateWindow(
		WINDOW_TITLE,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		0
	);
	if (!window)
	{
		printf("SDL_CreateWindow failed!");
		return false;
	}

	renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED
	);
	if (!renderer)
	{
		printf("SDL_CreateRenderer failed!");
		return false;
	}

	return true;
}

//Initialize game
void setup()
{
	//Clear Board
	for (int x = 0; x < ROWS; x++)
	{
		for (int y = 0; y < COLS; y++)
		{
			game.Board[x][y] = 0;
		}
	}

	//Who will start the game
	int rnd = rand() % 10;
	if (rnd < 5)
	{
		game.CurrentPlayer = PLAYER_X;
	}
	else
	{
		game.CurrentPlayer = PLAYER_O;
	}

	//New game
	game.GameOver = false;
}

//Cleanup before exiting
void cleanup()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//Check for player input
void input(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				running = SDL_FALSE;
				break;

			case SDL_MOUSEBUTTONDOWN:
				SDL_MouseButtonEvent& b = event.button;
				if (b.button == SDL_BUTTON_LEFT)
				{
					int x, y;
					Uint32 buttons = SDL_GetMouseState(&x, &y);

					if (!game.GameOver)
					{
						int CELL_X = (int)(x / CELL_WIDTH);
						int CELL_Y = (int)(y / CELL_HEIGHT);

						if (game.Board[CELL_X][CELL_Y] == EMPTY)
						{
							if (game.CurrentPlayer == PLAYER_X)
							{
								game.Board[CELL_X][CELL_Y] = PLAYER_X;
								game.CurrentPlayer = PLAYER_O;
							}
						}
					}
					else
					{
						setup();
					}
				}
				break;
		}
	}
}

//Check if moves left
bool isMovesLeft()
{
	for (int x = 0; x < ROWS; x++)
		for (int y = 0; y < COLS; y++)
			if (game.Board[x][y] == EMPTY)
				return true;

	return false;
}

//Evaluate board for scores
int evaluateBoard()
{
	for (int x = 0; x < ROWS; x++)
	{
		if (game.Board[x][0] == game.Board[x][1] &&
			game.Board[x][1] == game.Board[x][2])
		{
			if (game.Board[x][0] == PLAYER_X)
				return 10;
			else if (game.Board[x][0] == PLAYER_O)
				return -10;
		}
	}

	for (int y = 0; y < COLS; y++)
	{
		if (game.Board[0][y] == game.Board[1][y] &&
			game.Board[1][y] == game.Board[2][y])
		{
			if (game.Board[0][y] == PLAYER_X)
				return 10;
			else if (game.Board[0][y] == PLAYER_O)
				return -10;
		}
	}

	if (game.Board[0][0] == game.Board[1][1] &&
		game.Board[1][1] == game.Board[2][2])
	{
		if (game.Board[0][0] == PLAYER_X)
			return 10;
		else if (game.Board[0][0] == PLAYER_O)
			return -10;
	}

	if (game.Board[0][2] == game.Board[1][1] &&
		game.Board[1][1] == game.Board[2][0])
	{
		if (game.Board[0][2] == PLAYER_X)
			return 10;
		else if (game.Board[0][2] == PLAYER_O)
			return -10;
	}

	return 0;
}

//int minimax(int depth, bool isMax)
//{
//	int score = evaluateBoard();
//
//	if (score == 10)
//		return 10;
//
//	if (score == -10)
//		return -10;
//
//	if (!isMovesLeft())
//		return 0;
//
//	if (isMax)
//	{
//		int best = -1000;
//
//		for (int x = 0; x < ROWS; x++)
//		{
//			for (int y = 0; y < COLS; y++)
//			{
//				if (game.Board[x][y] == EMPTY)
//				{
//					game.Board[x][y] = PLAYER_X;
//
//					int max = minimax(depth + 1, !isMax);
//					if (max > best)
//						best = max;
//
//					game.Board[x][y] = EMPTY;
//				}
//			}
//		}
//
//		return best;
//	}
//	else if (!isMax)
//	{
//		int best = 1000;
//
//		for (int x = 0; x < ROWS; x++)
//		{
//			for (int y = 0; y < COLS; y++)
//			{
//				if (game.Board[x][y] == EMPTY)
//				{
//					game.Board[x][y] = PLAYER_O;
//
//					int min = minimax(depth + 1, isMax);
//					if (min < best)
//						best = min;
//
//					game.Board[x][y] = EMPTY;
//				}
//			}
//		}
//
//		return best;
//	}
//}

int minimax(int depth, int alpha, int beta, bool isMax)
{
	int score = evaluateBoard();

	if (score == 10)
		return 10 - depth;

	if (score == -10)
		return -10 + depth;

	if (!isMovesLeft())
		return 0;

	if (isMax)
	{
		int best = -1000;

		for (int x = 0; x < ROWS; x++)
		{
			for (int y = 0; y < COLS; y++)
			{
				if (game.Board[x][y] == EMPTY)
				{
					game.Board[x][y] = PLAYER_X;

					int val = minimax(depth + 1, alpha, beta, false);

					game.Board[x][y] = EMPTY;

					best = std::max(best, val);
					alpha = std::max(alpha, best);

					if (beta <= alpha)
						break;
				}
			}
		}

		return best;
	}
	else
	{
		int best = 1000;

		for (int x = 0; x < ROWS; x++)
		{
			for (int y = 0; y < COLS; y++)
			{
				if (game.Board[x][y] == EMPTY)
				{
					game.Board[x][y] = PLAYER_O;

					int val = minimax(depth + 1, alpha, beta, true);

					game.Board[x][y] = EMPTY;

					best = std::min(best, val);
					beta = std::min(beta, best);

					if (beta <= alpha)
						break;
				}
			}
		}

		return best;
	}
}

BestMove findBestMove()
{
	int bestScore = -1000;

	BestMove bestMove;
	bestMove.Row = -1;
	bestMove.Col = -1;

	if (game.Board[1][1] == EMPTY)
	{
		bestMove.Row = 1;
		bestMove.Col = 1;
		return bestMove;
	}

	for (int x = 0; x < ROWS; x++)
	{
		for (int y = 0; y < COLS; y++)
		{
			if (game.Board[x][y] == EMPTY)
			{
				game.Board[x][y] = PLAYER_X;

				int score = minimax(0, INT_MIN, INT_MAX, false);

				game.Board[x][y] = EMPTY;

				if (score > bestScore)
				{
					bestScore = score;
					bestMove.Row = x;
					bestMove.Col = y;
				}
			}
		}
	}

	return bestMove;
}

//Update game
void update()
{
	if (game.CurrentPlayer == PLAYER_O)
	{
		BestMove move = findBestMove();
		if (move.Row != -1 && move.Col != -1)
		{
			game.Board[move.Row][move.Col] = PLAYER_O;
			game.CurrentPlayer = PLAYER_X;
		}
	}

	int score = evaluateBoard();
	if (!isMovesLeft() || score != 0)
	{
		game.GameOver = true;
	}
}

void drawCircle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(renderer, x + dx, y + dy);
			}
		}
	}
}

void renderBoard()
{
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);

	//Draw row lines
	for (int x = 0; x < ROWS; x++)
	{
		SDL_RenderDrawLine(
			renderer,
			0,
			x * (WINDOW_HEIGHT / COLS),
			WINDOW_WIDTH,
			x * (WINDOW_HEIGHT / COLS)
		);
	}

	//Draw column lines
	for (int y = 0; y < COLS; y++)
	{
		SDL_RenderDrawLine(
			renderer,
			y * (WINDOW_WIDTH / ROWS),
			0,
			y * (WINDOW_WIDTH / ROWS),
			WINDOW_HEIGHT
		);
	}
}

void renderPieces()
{
	for (int x = 0; x < ROWS; x++)
	{
		for (int y = 0; y < COLS; y++)
		{
			int CENTER_X = (x * CELL_WIDTH) + CELL_WIDTH / 2;
			int CENTER_Y = (y * CELL_HEIGHT) + CELL_HEIGHT / 2;

			if (game.Board[x][y] == PLAYER_X)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

				SDL_RenderDrawLine(
					renderer,
					CENTER_X - 50,
					CENTER_Y - 50,
					CENTER_X + 50,
					CENTER_Y + 50
				);

				SDL_RenderDrawLine(
					renderer,
					CENTER_X + 50,
					CENTER_Y - 50,
					CENTER_X - 50,
					CENTER_Y + 50
				);
			}
			else if (game.Board[x][y] == PLAYER_O)
			{
				SDL_Color color;
				color.r = 255;
				color.g = 0;
				color.b = 0;
				color.a = 255;

				drawCircle(renderer, CENTER_X, CENTER_Y, 50, color);

				color.r = 0;
				drawCircle(renderer, CENTER_X, CENTER_Y, 49, color);
			}
		}
	}
}

//Render game
void render()
{
	//Clear
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//Render game
	renderBoard();
	renderPieces();

	//Preset
	SDL_RenderPresent(renderer);
}

int main(int argc, char* args[])
{
	running = init();
	if (running)
	{
		setup();
	}

	while (running)
	{
		input();
		update();
		render();
	}

	cleanup();

	return 0;
}
