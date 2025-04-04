#ifndef _LOGIC__H
#define _LOGIC__H

#include <vector>
#include "mouseInputs.h"

using namespace std;


struct Chess {
	char piecePositions[BOARD_SIZE][BOARD_SIZE];
	MouseInputs mouseInputs;
	
	vector<int> moveRecords; 
	pair<int, int>blackKingPosition;
	pair<int, int>whiteKingPosition;
	bool isPawnPromotedFlag = false;

	Chess() { 
		init();
		moveRecords=vector<int>(4, -1);
	}

	void init();

	bool isPathClear(int x1, int y1, int x2, int y2) const;
	
	bool isPawnPromoted(int x1, int y1, int x2, int y2) const;

	void movePiece(int x1, int y1, int x2, int y2);

	bool isValidMove(int x1, int y1, int x2, int y2) const;

	void control();

	bool checkmateBlack() const;
	
	bool checkmateWhite() const;

	void deleteUselessMoves(int x1,int y1,int x2,int y2);
};

#endif
