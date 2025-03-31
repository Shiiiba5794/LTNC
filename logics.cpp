#include <iostream>
#include <vector>
#include <cmath>
#include "logics.h"

using namespace std;
void Chess::init() {
	const char initial_board[BOARD_SIZE][BOARD_SIZE] = {
		{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
		{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
		{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
	};

	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			piece_positions[i][j] = initial_board[i][j];
}

bool Chess::is_valid_move(int x1, int y1, int x2, int y2) {
	if (x2 < 0 || x2 >= BOARD_SIZE || y2 < 0 || y2 >= BOARD_SIZE) {
		moves.erase(moves.end() - 4, moves.end());
		return false;
	}
	if (x1 == x2 && y1 == y2) {
		moves.erase(moves.end() - 4, moves.end());
		return false;
	}
	return true;
}
//check if there are any pieces in the way
bool Chess::is_path_clear(int x1, int y1, int x2, int y2) {
	int dx = (x2 - x1) == 0 ? 0 : (x2 - x1) / abs(x2 - x1);
	int dy = (y2 - y1) == 0 ? 0 : (y2 - y1) / abs(y2 - y1);

	int cx = x1 + dx, cy = y1 + dy;
	while (cx != x2 || cy != y2) {
		if (piece_positions[cx][cy] != EMPTY_CELL)
			return false;
		cx += dx;
		cy += dy;
	}
	return true;
}

void Chess::move_piece(int x1, int y1, int x2, int y2) {
	if (!is_valid_move(x1, y1, x2, y2)) return;
	char piece = piece_positions[x1][y1];
	//king
	if (piece == 'K' || piece == 'k') {
		if (abs(x2 - x1) <= 1 && abs(y2 - y1) <= 1)
			piece_positions[x2][y2] = piece;
		else {
			moves.erase(moves.end() - 4, moves.end());
			return;
		}
	}//queen
	else if (piece == 'Q' || piece == 'q') {
		if ((x1 == x2 || y1 == y2 || abs(x2 - x1) == abs(y2 - y1)) && (is_path_clear(x1, y1, x2, y2)))
			piece_positions[x2][y2] = piece;
		else {
			return;
			moves.erase(moves.end() - 4, moves.end());
		}
	}//bishop
	else if (piece == 'B' || piece == 'b') {
		if (abs(x2 - x1) == abs(y2 - y1) && is_path_clear(x1, y1, x2, y2))
			piece_positions[x2][y2] = piece;
		else {
			return;
			moves.erase(moves.end() - 4, moves.end());
		}
	}//knight
	else if (piece == 'N' || piece == 'n') {
		if ((abs(x2 - x1) == 2 && abs(y2 - y1) == 1) || (abs(x2 - x1) == 1 && abs(y2 - y1) == 2))
			piece_positions[x2][y2] = piece;
		else {
			return;
			moves.erase(moves.end() - 4, moves.end());
		}
	}//rook
	else if (piece == 'R' || piece == 'r') {
		if ((x1 == x2 || y1 == y2) && is_path_clear(x1, y1, x2, y2))
			piece_positions[x2][y2] = piece;
		else {
			return;
			moves.erase(moves.end() - 4, moves.end());
		}
	}//pawn
	else if (piece == 'P' || piece == 'p') {
		if (piece == 'P') {
			if (x1 == 1 && y1 == y2 &&
				((x2 == 3 && piece_positions[3][y1] == EMPTY_CELL && piece_positions[2][y1] == EMPTY_CELL) ||
					(x2 == 2 && piece_positions[2][y1] == EMPTY_CELL)))
				piece_positions[x2][y2] = piece;
			else {
				return;
				moves.erase(moves.end() - 4, moves.end());
			}
		}
		else if (piece == 'p') {
			if (x1 == 6 && y1 == y2 &&
				((x2 == 4 && piece_positions[4][y1] == EMPTY_CELL && piece_positions[5][y1] == EMPTY_CELL) ||
					(x2 == 5 && piece_positions[5][y1] == EMPTY_CELL)))
				piece_positions[x2][y2] = piece;
			else {
				return;
				moves.erase(moves.end() - 4, moves.end());
			}
		}
	}

	piece_positions[x1][y1] = EMPTY_CELL;
}

void Chess::delete_useless_moves() {
	if (moves.size() >= 2) {
		int x = moves[moves.size() - 2];
		int y = moves[moves.size() - 1];
		if (moves.size() % 4 != 0 && x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
			if (piece_positions[x][y] == EMPTY_CELL) {
				moves.pop_back();
				moves.pop_back();
			}
		}
		if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
			moves.pop_back();
			moves.pop_back();
		}

	}
}


void Chess::check_move() {
	if (moves.size() % 4 == 0)
		move_piece(moves[moves.size() - 4], moves[moves.size() - 3], moves[moves.size() - 2], moves[moves.size() - 1]);
}