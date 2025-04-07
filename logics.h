#ifndef _LOGIC__H
#define _LOGIC__H

#include <vector>
#include "mouseInputs.h"

using namespace std;


struct Chess {
	char piecePositions[BOARD_SIZE][BOARD_SIZE];
	vector<int> moveRecords; 
	MouseInputs mouseInputs;
	pair<int, int>blackKingPosition;
	pair<int, int>whiteKingPosition;
	bool isPawnPromotedFlag = false;
	bool isWhiteTurn = true;
	bool isBlackTurn = false;
	bool isBlackKingInCheck = false;



	Chess() { 
		init();
		moveRecords=vector<int>(4, -1);
	}

	void init();

	bool isPathClear(int x1, int y1, int x2, int y2) const;
	
	bool isPawnPromoted(int x1, int y1, int x2, int y2) const;

	void moveStandardPiece(int x1, int y1, int x2, int y2);

	bool isValidMove(int x1, int y1, int x2, int y2) const;

	void control();

	bool checkmateBlack() const;
	
	bool checkmateWhite() const;

	void deleteUselessMoveRules(int x1,int y1,int x2,int y2);

	void performEnPassant();
};

#endif
