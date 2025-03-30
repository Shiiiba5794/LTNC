#ifndef _LOGIC__H
#define _LOGIC__H
#define BOARD_SIZE 8
#define EMPTY_CELL false
#define USED_CELL true

struct Chess {
	bool used_cell[BOARD_SIZE][BOARD_SIZE];
	char piece_positions[BOARD_SIZE][BOARD_SIZE];

	struct current_position {
		int current_row;
		int current_column;
	};

	void init() {
		for (int i = 0; i < BOARD_SIZE; i++)
			for (int j = 0; j < BOARD_SIZE; j++) {
				{
					if (i == 0 || i == 1 || i == 6 || i == 7) used_cell[i][j] = USED_CELL;
					else {
						used_cell[i][j] = EMPTY_CELL;
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
					if (i == 1) piece_positions[i][j] = 'p';
					if (i == 0) {
						if (j == 0 || j == 7) piece_positions[i][j] = 'r';
						if (j == 1 || j == 6) piece_positions[i][j] = 'n';
						if (j == 2 || j == 5) piece_positions[i][j] = 'b';
						if (j == 3) piece_positions[i][j] = 'q';
						if (j == 4) piece_positions[i][j] = 'k';
					}
				}
			}
	}
	void king_move(int row, int column) {
		if (row >= 0 && row < BOARD_SIZE &&
			column >= 0 && column < BOARD_SIZE) {

			used_cell[row][column] = true;

		}
	}

};
#endif