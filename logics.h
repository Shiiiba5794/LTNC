#ifndef _LOGIC__H
#define _LOGIC__H

#include <vector>
#include "mouseInputs.h"

using namespace std;


struct Chess {
	const char initialBoard[BOARD_SIZE][BOARD_SIZE] = {
		{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
		{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
		{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
	};
	char piecePositions[BOARD_SIZE][BOARD_SIZE];
	vector<int> moveRecords; 
	MouseInputs mouseInputs;
	pair<int, int>blackKingPosition;
	pair<int, int>whiteKingPosition;
	bool isPawnPromotedFlag = false;
	bool isWhiteTurn = true;
	bool checkmateBlack = false;
	bool checkmateWhite = false;
	bool whiteWin = false;
	bool blackWin = false;
	int numberOfPiecesBeforeMove = 0;
	int numberOfPiecesAfterMove = 0;
	//castling
	bool hasWhiteKingMoved = false;
	bool hasWhiteQueenSideRookMoved = false;
	bool hasWhiteKingSideRookMoved = false;
	bool hasBlackKingMoved = false;
	bool hasBlackQueenSideRookMoved = false;
	bool hasBlackKingSideRookMoved = false;


	Chess() { 
		init();
		moveRecords=vector<int>(4, -1);
	}

	void init();

	bool isPathClear(int x1, int y1, int x2, int y2) const;
	
	bool isPawnPromoted(int x1, int y1, int x2, int y2) const;

	void promotePawn();

	void moveStandardPiece(int x1, int y1, int x2, int y2);

	bool isValidStandardMove(int x1, int y1, int x2, int y2) const;

	bool isWhiteKingDead() const;

	bool isBlackKingDead() const;

	void control();

	bool isSquareAttackedByWhite(int x,int y) const;
	
	bool isSquareAttackedByBlack(int x,int y) const;

	void deleteUselessMoveRules(int x1,int y1,int x2,int y2);

	void performEnPassant();

	void castleQueenSide(int x1,int y1,int x2,int y2);

	void castleKingSide(int x1, int y1, int x2, int y2);

	void reset();

	int countRemaningPieces();
};

#endif
