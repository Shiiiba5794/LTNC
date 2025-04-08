#ifndef MOVERULES_H
#define MOVERULES_H

#include <cmath>
#include <vector>
#include <cctype>
#include "defs.h"

using namespace std;

struct Chess;

struct MoveRules {
	

	static bool isKingMove(int x1, int y1, int x2, int y2);

	static bool isQueenMove(int x1, int y1, int x2, int y2);

	static bool isBishopMove(int x1, int y1, int x2, int y2);

	static bool isKnightMove(int x1, int y1, int x2, int y2);

	static bool isRookMove(int x1, int y1, int x2, int y2);

	static bool isPawnMove(bool isWhite, const vector<int>& moveRecords, const char  board[BOARD_SIZE][BOARD_SIZE]);

	static bool isEnPassantPossible(bool isWhite, const vector<int>& moveRecords, const char board[BOARD_SIZE][BOARD_SIZE]);

	static bool canCastleQueenSide(bool isWhite,const vector<int>& moveRecords, const char board[BOARD_SIZE][BOARD_SIZE],Chess*game);

	static bool canCastleKingSide(bool isWhite,const vector<int>& moveRecords, const char board[BOARD_SIZE][BOARD_SIZE],Chess*game);
};

#endif 
