#include<cmath>
#include"moveRules.h"
#include"defs.h"
#include"logics.h"

bool MoveRules::isKingMove(int x1, int y1, int x2, int y2) {
	return abs(x2 - x1) <= 1 && abs(y2 - y1) <= 1;
}

bool MoveRules::isQueenMove(int x1, int y1, int x2, int y2) {
	return (x1 == x2 || y1 == y2 || abs(x2 - x1) == abs(y2 - y1));
}

bool MoveRules::isBishopMove(int x1, int y1, int x2, int y2) {
	return abs(x2 - x1) == abs(y2 - y1);
}

bool MoveRules::isKnightMove(int x1, int y1, int x2, int y2) {
	return (abs(x2 - x1) == 2 && abs(y2 - y1) == 1) || (abs(x2 - x1) == 1 && abs(y2 - y1) == 2);
}

bool MoveRules::isRookMove(int x1, int y1, int x2, int y2) {
	return x1 == x2 || y1 == y2;
}

bool MoveRules::isPawnMove(bool isWhite, const vector<int>& moveRecords, const char board[BOARD_SIZE][BOARD_SIZE]) {
	int x1 = moveRecords[moveRecords.size() - 4];
	int y1 = moveRecords[moveRecords.size() - 3];
	int x2 = moveRecords[moveRecords.size() - 2];
	int y2 = moveRecords[moveRecords.size() - 1];
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

bool MoveRules::isEnPassantPossible(bool isWhite, const vector<int>& moveRecords, const char board[BOARD_SIZE][BOARD_SIZE]) {
	if (moveRecords.size() >= 12 && moveRecords.size() % 4 == 0) {
		int x1 = moveRecords[moveRecords.size() - 4];
		int y1 = moveRecords[moveRecords.size() - 3];
		int x2 = moveRecords[moveRecords.size() - 2];
		int y2 = moveRecords[moveRecords.size() - 1];
		int direction = isWhite ? -1 : 1;
		int previousMoveX1 = moveRecords[moveRecords.size() - 8];
		int previousMoveY1 = moveRecords[moveRecords.size() - 7];
		int previousMoveX2 = moveRecords[moveRecords.size() - 6];
		int previousMoveY2 = moveRecords[moveRecords.size() - 5];
		if (previousMoveY2 == previousMoveY1 - 2 * direction) {
			if (board[previousMoveY2][previousMoveX2] == 'P') {
				if (board[y1][x1] == 'p')
					if (abs(x1 - previousMoveX1) == 1 && y1 == previousMoveY2)
						return true;
			}
			else if (board[previousMoveY2][previousMoveX2] == 'p') {
				if (board[y1][x1] == 'P')
					if (abs(x1 - previousMoveX1) == 1 && y1 == previousMoveY2)
						return true;
			}
		}
	}
	return false;
}

bool MoveRules::canCastleQueenSide(bool isWhite, const vector<int>& moveRecords, const char board[BOARD_SIZE][BOARD_SIZE], Chess* game) {
	int x1 = moveRecords[moveRecords.size() - 4];
	int y1 = moveRecords[moveRecords.size() - 3];
	int x2 = moveRecords[moveRecords.size() - 2];
	int y2 = moveRecords[moveRecords.size() - 1];

	if (isWhite && x1 == 4 && y1 == 7 && x2 == 2 && y2 == 7) {
		if (board[7][4] == 'k' && board[7][3] == EMPTY_CELL && board[7][2] == EMPTY_CELL && board[7][0] == 'r') {
			if (game->isSquareAttackedByBlack(7, 4) || game->isSquareAttackedByBlack(7, 3) || game->isSquareAttackedByBlack(7, 2)) {
				return false;
			}
			return true;
		}
		return false;
	}
	else if (!isWhite && x1 == 4 && y1 == 0 && x2 == 2 && y2 == 0) {
		if (board[0][4] == 'K' && board[0][3] == EMPTY_CELL && board[0][2] == EMPTY_CELL && board[0][0] == 'R') {
			if (game->isSquareAttackedByWhite(0, 4) || game->isSquareAttackedByWhite(0, 3) || game->isSquareAttackedByWhite(0, 2)) {
				return false;
			}
			return true;
		}
		return false;
	}
	return false;
}

bool MoveRules::canCastleKingSide(bool isWhite, const vector<int>& moveRecords, const char board[BOARD_SIZE][BOARD_SIZE], Chess* game) {
	int x1 = moveRecords[moveRecords.size() - 4];
	int y1 = moveRecords[moveRecords.size() - 3];
	int x2 = moveRecords[moveRecords.size() - 2];
	int y2 = moveRecords[moveRecords.size() - 1];
	if (isWhite && x1 == 4 && y1 == 7 && x2 == 6 && y2 == 7) {
		if (board[7][4] == 'k' && board[7][5] == EMPTY_CELL && board[7][6] == EMPTY_CELL && board[7][7] == 'r') {
			if (game->isSquareAttackedByBlack(7, 4) || game->isSquareAttackedByBlack(7, 5) || game->isSquareAttackedByBlack(7, 6)) {
				return false;
			}
			return true;
		}
		return false;
	}
	else if (!isWhite && x1 == 4 && y1 == 0 && x2 == 6 && y2 == 0) {
		if (board[0][4] == 'K' && board[0][5] == EMPTY_CELL && board[0][6] == EMPTY_CELL && board[0][7] == 'R') {
			if (game->isSquareAttackedByWhite(0, 4) || game->isSquareAttackedByWhite(0, 5) || game->isSquareAttackedByWhite(0, 6)) {
				return false;
			}
			return true;
		}
		return false;
	}
	return false;
}
