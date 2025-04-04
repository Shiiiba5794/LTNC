#include<cmath>
#include"moves.h"
#include"defs.h"

bool Moves::isKingMove(int x1, int y1, int x2, int y2) {
	return abs(x2 - x1) <= 1 && abs(y2 - y1) <= 1;
}

bool Moves::isQueenMove(int x1, int y1, int x2, int y2) {
	return (x1 == x2 || y1 == y2 || abs(x2 - x1) == abs(y2 - y1));
}

bool Moves::isBishopMove(int x1, int y1, int x2, int y2) {
	return abs(x2 - x1) == abs(y2 - y1);
}

bool Moves::isKnightMove(int x1, int y1, int x2, int y2) {
	return (abs(x2 - x1) == 2 && abs(y2 - y1) == 1) || (abs(x2 - x1) == 1 && abs(y2 - y1) == 2);
}

bool Moves::isRookMove(int x1, int y1, int x2, int y2) {
	return x1 == x2 || y1 == y2;
}




bool Moves::isPawnMove(int x1, int y1, int x2, int y2, bool isWhite, const char  board[8][8]) {
	int direction = isWhite ? -1 : 1;
	if (x1 == x2) {
		if (y2 == y1 + direction && board[y2][x2] == EMPTY_CELL)
			return true;
		if ((y1 == 6 && isWhite) || (y1 == 1 && !isWhite)) {
			if (y2 == y1 + 2 * direction && board[y1 + direction][x2] == EMPTY_CELL && board[y2][x2] == EMPTY_CELL)
				return true;
		}
	}
	if (abs(x2 - x1) == 1 && y2 == y1 + direction) {
		if (board[y2][x2] != EMPTY_CELL && ((isWhite && isupper(board[y2][x2])) || (!isWhite && islower(board[y2][x2]))))
			return true;
	}

	return false;
}