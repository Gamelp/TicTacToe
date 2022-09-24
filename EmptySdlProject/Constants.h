#pragma once

#define WINDOW_TITLE "TicTacToe"
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#define GAME_FPS 60

const int ROWS = 3;
const int COLS = 3;
const int CELL_WIDTH = WINDOW_WIDTH / ROWS;
const int CELL_HEIGHT = WINDOW_HEIGHT / COLS;

const int EMPTY = 0;
const int PLAYER_X = 1;
const int PLAYER_O = 2;

struct Game
{
	int Board[ROWS][COLS] = {};
	int CurrentPlayer = PLAYER_X;
};