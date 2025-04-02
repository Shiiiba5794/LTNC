#include <iostream>
#include <vector>
#include <cmath>
#include <cctype>
#include "logics.h"
#include "moves.h"

using namespace std;
void Chess::init() {
	const char initial_board[BOARD_SIZE][BOARD_SIZE] = {
		{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
		{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
		{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
	};

	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			piecePositions[i][j] = initial_board[i][j];
	blackKingPosition.first = 4;
	blackKingPosition.second = 0;
	whiteKingPosition.first = 4;
	whiteKingPosition.second = 7;
}

bool Chess::isValidMove(int x1, int y1, int x2, int y2) {
	if (x2 < 0 || x2 >= BOARD_SIZE || y2 < 0 || y2 >= BOARD_SIZE) {
		moveRecords.erase(moveRecords.end() - 4, moveRecords.end());
		return false;
	}
	if (x1 == x2 && y1 == y2) {
		moveRecords.erase(moveRecords.end() - 4, moveRecords.end());
		return false;
	}
	return true;
}

bool Chess::isPathClear(int x1, int y1, int x2, int y2) {
	int dx = (x2 - x1) == 0 ? 0 : (x2 - x1) / abs(x2 - x1);
	int dy = (y2 - y1) == 0 ? 0 : (y2 - y1) / abs(y2 - y1);

	int cx = x1 + dx, cy = y1 + dy;
	while (cx != x2 || cy != y2) {
		if (piecePositions[cy][cx] != EMPTY_CELL)
			return false;
		cx += dx;
		cy += dy;
	}
	return true;
}

void Chess::movePiece(int x1, int y1, int x2, int y2) {
	if (!isValidMove(x1, y1, x2, y2)) return;
	char piece = piecePositions[y1][x1];
	bool isValid = false;

	switch (piece) {
	case 'K': 
		isValid = Moves::isKingMove(x1, y1, x2, y2);
		if (isValid) {
			blackKingPosition.first = x2;
			blackKingPosition.second = y2;
		}
		break;
	case'k':
		isValid = Moves::isKingMove(x1, y1, x2, y2);
		if (isValid) {
			whiteKingPosition.first = x2;
			whiteKingPosition.second = y2;
		}
		break;
	case 'Q': case 'q':
		isValid = Moves::isQueenMove(x1, y1, x2, y2)&&isPathClear(x1,y1,x2,y2);
		break;
	case 'B': case 'b':
		isValid = Moves::isBishopMove(x1, y1, x2, y2)&&isPathClear(x1, y1, x2, y2);
		break;
	case 'N': case 'n':
		isValid = Moves::isKnightMove(x1, y1, x2, y2);
		break;
	case 'R': case 'r':
		isValid = Moves::isRookMove(x1, y1, x2, y2)&&isPathClear(x1, y1, x2, y2);
		break;
	case 'P':
		isValid = Moves::isPawnMove(x1, y1, x2, y2, false,piecePositions);
		break;
	case 'p':
		isValid = Moves::isPawnMove(x1, y1, x2, y2, true,piecePositions);
		break;
	}

	if (isValid) {
		piecePositions[y2][x2] = piece;
		piecePositions[y1][x1] = EMPTY_CELL;
	}
	else return;
}


bool Chess::isPawnPromoted(int x1, int y1, int x2, int y2) const {
	
	if (( piecePositions[y1][x1]=='p' && y2 == 0) || (piecePositions[y1][x1]=='P' && y2 == 7)) {
		return true;
	}
	return false;
}

void Chess::control() {
	if (moveRecords.size() % 4 == 0)
		movePiece(moveRecords[moveRecords.size() - 4], moveRecords[moveRecords.size() - 3], moveRecords[moveRecords.size() - 2], moveRecords[moveRecords.size() - 1]);
}
bool Chess::checkmateBlack()const {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			
			
		}
	}
	return false;
}

bool Chess::checkmateWhite()const {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			
			
		}
	}
	return false;
}