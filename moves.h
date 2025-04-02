#ifndef MOVES_H
#define MOVES_H

#include <cmath>
#include <cctype>

struct Moves {
	static bool isKingMove(int x1, int y1, int x2, int y2);

	static bool isQueenMove(int x1, int y1, int x2, int y2);

	static bool isBishopMove(int x1, int y1, int x2, int y2);

	static bool isKnightMove(int x1, int y1, int x2, int y2);

	static bool isRookMove(int x1, int y1, int x2, int y2);

	static bool isPawnMove(int x1, int y1, int x2, int y2, bool isWhite, char board[8][8]);
};

#endif 
