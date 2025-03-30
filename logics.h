#ifndef _LOGIC__H
#define _LOGIC__H
using namespace std;
#define BOARD_SIZE 8
#define EMPTY_CELL false
#define USED_CELL true

struct Chess {
	bool used_cell[BOARD_SIZE][BOARD_SIZE];
	char piece_positions[BOARD_SIZE][BOARD_SIZE];

	vector<int> moves;
	//moves[0] = x1, moves[1] = y1, moves[2] = x2, moves[3] = y2
	void init() {
		for (int i = 0; i < BOARD_SIZE; i++)
			for (int j = 0; j < BOARD_SIZE; j++) {
				{
					if (i == 0 || i == 1 || i == 6 || i == 7) used_cell[i][j] = USED_CELL;
					else {
						used_cell[i][j] = EMPTY_CELL;
						piece_positions[i][j] = ' ';
					}
				}
				{	//black pieces
					if (i == 1) piece_positions[i][j] = 'P';
					if (i == 0) {
						if (j == 0 || j == 7) piece_positions[i][j] = 'R';
						if (j == 1 || j == 6) piece_positions[i][j] = 'N';
						if (j == 2 || j == 5) piece_positions[i][j] = 'B';
						if (j == 3) piece_positions[i][j] = 'Q';
						if (j == 4) piece_positions[i][j] = 'K';
					}
					//white piecs
					if (i == 6) piece_positions[i][j] = 'p';
					if (i == 7) {
						if (j == 0 || j == 7) piece_positions[i][j] = 'r';
						if (j == 1 || j == 6) piece_positions[i][j] = 'n';
						if (j == 2 || j == 5) piece_positions[i][j] = 'b';
						if (j == 3) piece_positions[i][j] = 'q';
						if (j == 4) piece_positions[i][j] = 'k';
					}
				}
			}
	}
	void king_move(int current_row, int current_column,int previous_row,int previous_column) {
		if (current_row >= 0 && current_row < BOARD_SIZE &&
			current_column >= 0 && current_column < BOARD_SIZE) {
			if ((current_row == previous_row + 1 || current_row == previous_row - 1) &&
				(current_column == previous_column + 1 || current_column == previous_column - 1)){
				used_cell[current_row][current_column] = true;
				used_cell[previous_row][previous_column] = false;
				piece_positions[current_row][current_column] = piece_positions[previous_row][previous_column];
				piece_positions[previous_row][previous_column] = ' ';
				moves.clear();
			}
			else moves.clear();
		}
	}
	void queen_move(int current_row, int current_column, int previous_row, int previous_column) {
		if (current_row >= 0 && current_row < BOARD_SIZE &&
			current_column >= 0 && current_column < BOARD_SIZE) {
			if (current_row == previous_row ||
				current_column == previous_column ||
				current_column + current_row == previous_column + previous_row ||
				current_column - current_row == previous_column - previous_row) {
				used_cell[current_row][current_column] = true;
				used_cell[previous_row][previous_column] = false;
				piece_positions[current_row][current_column] = piece_positions[previous_row][previous_column];
				piece_positions[previous_row][previous_column] = ' ';
				moves.clear();
			}
			else moves.clear();
		}
	}
	void bishop_move(int current_row, int current_column, int previous_row, int previous_column) {
		if (current_row >= 0 && current_row < BOARD_SIZE &&
			current_column >= 0 && current_column < BOARD_SIZE) {
			if (current_column + current_row == previous_column + previous_row ||
				current_column - current_row == previous_column - previous_row) {
				used_cell[current_row][current_column] = true;
				used_cell[previous_row][previous_column] = false;
				piece_positions[current_row][current_column] = piece_positions[previous_row][previous_column];
				piece_positions[previous_row][previous_column] = ' ';
				moves.clear();
			}
			else moves.clear();
		}
	}
	void knight_move(int current_row, int current_column, int previous_row, int previous_column) {
		if (current_row >= 0 && current_row < BOARD_SIZE &&
			current_column >= 0 && current_column < BOARD_SIZE) {
			if ((current_row == previous_row + 2 || current_row == previous_row - 2) &&
				(current_column == previous_column + 1 || current_column == previous_column - 1) ||
				(current_row == previous_row + 1 || current_row == previous_row - 1) &&
				(current_column == previous_column + 2 || current_column == previous_column - 2)) {
				used_cell[current_row][current_column] = true;
				used_cell[previous_row][previous_column] = false;
				piece_positions[current_row][current_column] = piece_positions[previous_row][previous_column];
				piece_positions[previous_row][previous_column] = ' ';
				moves.clear();
			}
			else moves.clear();
		}
	}
	void rook_move(int current_row, int current_column, int previous_row, int previous_column) {
		if (current_row >= 0 && current_row < BOARD_SIZE &&
			current_column >= 0 && current_column < BOARD_SIZE) {
			if (current_row == previous_row || current_column == previous_column) {
				used_cell[current_row][current_column] = true;
				used_cell[previous_row][previous_column] = false;
				piece_positions[current_row][current_column] = piece_positions[previous_row][previous_column];
				piece_positions[previous_row][previous_column] = ' ';
				moves.clear();
			}
			else moves.clear();
		}
	}
	void pawn_move(int current_row, int current_column, int previous_row, int previous_column) {
		if (current_row >= 0 && current_row < BOARD_SIZE &&
			current_column >= 0 && current_column < BOARD_SIZE) {
			if (current_row == previous_row + 1 && current_column == previous_column) {
				used_cell[current_row][current_column] = true;
				used_cell[previous_row][previous_column] = false;
				piece_positions[current_row][current_column] = piece_positions[previous_row][previous_column];
				piece_positions[previous_row][previous_column] = ' ';
				moves.clear();
			}
			else moves.clear();
		}
	}
	void check_move() {
		if (moves.size() == 4) {
			if (moves[0] == moves[2] && moves[1] == moves[3]) moves.clear();
			else if (piece_positions[moves[1]][moves[0]] == 'K' || piece_positions[moves[1]][moves[0]] == 'k')
				king_move(moves[3], moves[2], moves[1], moves[0]);
			else if (piece_positions[moves[1]][moves[0]] == 'Q' || piece_positions[moves[1]][moves[0]] == 'q') 
				queen_move(moves[3], moves[2], moves[1], moves[0]);
			else if (piece_positions[moves[1]][moves[0]] == 'B' || piece_positions[moves[1]][moves[0]] == 'b')
				bishop_move(moves[3], moves[2], moves[1], moves[0]);
			else if (piece_positions[moves[1]][moves[0]] == 'N' || piece_positions[moves[1]][moves[0]] == 'n')
				knight_move(moves[3], moves[2], moves[1], moves[0]);
			else if (piece_positions[moves[1]][moves[0]] == 'R' || piece_positions[moves[1]][moves[0]] == 'r')
				rook_move(moves[3], moves[2], moves[1], moves[0]);
			else if (piece_positions[moves[1]][moves[0]] == 'P' || piece_positions[moves[1]][moves[0]] == 'p')
				pawn_move(moves[3], moves[2], moves[1], moves[0]);
		}
	}
};
#endif