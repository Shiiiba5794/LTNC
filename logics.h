#ifndef _LOGIC__H
#define _LOGIC__H

#include <vector>
#include <cmath>
using namespace std;

#define BOARD_SIZE 8
#define EMPTY_CELL ' '

struct Chess {
	char piece_positions[BOARD_SIZE][BOARD_SIZE];
	vector<int> moves; // moves[0] = x1, moves[1] = y1, moves[2] = x2, moves[3] = y2

	Chess() { 
		init();
	}

	void init();

	bool is_valid_move(int x1, int y1, int x2, int y2);

	bool is_path_clear(int x1, int y1, int x2, int y2);

	void move_piece(int x1, int y1, int x2, int y2);

	void delete_useless_moves();

	void check_move();
};

#endif
