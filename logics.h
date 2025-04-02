#ifndef _LOGIC__H
#define _LOGIC__H

#include <vector>
#include <cmath>
#include "defs.h"
using namespace std;
#define BOARD_SIZE 8
#define EMPTY_CELL ' '


struct Chess {
	char piecePositions[BOARD_SIZE][BOARD_SIZE];
	
	vector<int> moveRecords; // moveRecords[0] = x1, moveRecords[1] = y1, moveRecords[2] = x2, moveRecords[3] = y2
	pair<int, int>blackKingPosition;
	pair<int, int>whiteKingPosition;

	Chess() { 
		init();
	}

	void init();

	bool isValidMove(int x1, int y1, int x2, int y2);

	bool isPathClear(int x1, int y1, int x2, int y2);

	void movePiece(int x1, int y1, int x2, int y2);

	bool isPawnPromoted(int x1, int y1, int x2, int y2) const;

	void control();

	bool checkmateBlack() const;
	
	bool checkmateWhite() const;
};

#endif
