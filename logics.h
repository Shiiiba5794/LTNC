#ifndef _LOGIC__H
#define _LOGIC__H
#define BOARD_SIZE 8
#define EMPTY_CELL ' '
#define USED_CELL 'u'
struct Chess {
	char used_cell[BOARD_SIZE][BOARD_SIZE];
	char next_move = USED_CELL;
	void init() {
		for (int i = 0; i < BOARD_SIZE; i++)
			for (int j = 0; j < BOARD_SIZE; j++)
				if (i == 0 || i == 1 || i == 6 || i == 7) used_cell[i][j] = USED_CELL;
				else { used_cell[i][j] = EMPTY_CELL; }
	}
	
	void king_move(int row, int column) {
		if (row >= 0 && row < BOARD_SIZE &&
			column >= 0 && column < BOARD_SIZE) {
			
				used_cell[row][column] = next_move;
			
		}
	}

};
#endif