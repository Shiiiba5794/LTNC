#include <vector>
#include <iostream>
#include <cmath>
#include <cctype>
#include "logics.h"
#include "moveRules.h"

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


void Chess::deleteUselessMoveRules(int x1, int y1, int x2, int y2) {
	if (moveRecords.size() % 4 == 0 && moveRecords.size() >= 8) {

		if (x1 == x2 && y1 == y2 && mouseInputs.isInBoardClick(x1, y1)) {
			moveRecords.erase(moveRecords.end() - 4, moveRecords.end());
		}
		else if (piecePositions[y1][x1] == EMPTY_CELL) {
			moveRecords.erase(moveRecords.end() - 4, moveRecords.end() - 2);
		}
		else if (piecePositions[y2][x2] != EMPTY_CELL) {
			if (isupper(piecePositions[y1][x1]) && isupper(piecePositions[y2][x2])) {
				moveRecords.erase(moveRecords.end() - 4, moveRecords.end());
			}
			else if (islower(piecePositions[y1][x1]) && islower(piecePositions[y2][x2])) {
				moveRecords.erase(moveRecords.end() - 4, moveRecords.end());
			}
		}
		else if (!isValidMove(x1, y1, x2, y2)) {
			moveRecords.erase(moveRecords.end() - 4, moveRecords.end());
		}

	}
}



bool Chess::isPathClear(int x1, int y1, int x2, int y2) const {
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

bool Chess::isPawnPromoted(int x1, int y1, int x2, int y2) const {

	if ((piecePositions[y1][x1] == 'p' && y2 == 0) || (piecePositions[y1][x1] == 'P' && y2 == 7)) {
		return true;
	}
	return false;
}

bool Chess::isValidMove(int x1, int y1, int x2, int y2) const {
	char piece = piecePositions[y1][x1];
	if (MoveRules::isEnPassantPossible(isWhiteTurn, moveRecords, piecePositions)) {
		return true;
	}
	bool isValid = false;
	switch (piece) {
	case 'K':case'k':
		isValid = MoveRules::isKingMove(x1, y1, x2, y2) &&
			((isupper(piece) && isBlackTurn) || (islower(piece) && isWhiteTurn));
		break;
	case 'Q': case 'q':
		isValid = MoveRules::isQueenMove(x1, y1, x2, y2) && isPathClear(x1, y1, x2, y2) &&
			((isupper(piece) && isBlackTurn) || (islower(piece) && isWhiteTurn));
		break;
	case 'B': case 'b':
		isValid = MoveRules::isBishopMove(x1, y1, x2, y2) && isPathClear(x1, y1, x2, y2) &&
			((isupper(piece) && isBlackTurn) || (islower(piece) && isWhiteTurn));
		break;
	case 'N': case 'n':
		isValid = MoveRules::isKnightMove(x1, y1, x2, y2) &&
			((isupper(piece) && isBlackTurn) || (islower(piece) && isWhiteTurn));
		break;
	case 'R': case 'r':
		isValid = MoveRules::isRookMove(x1, y1, x2, y2) && isPathClear(x1, y1, x2, y2) &&
			((isupper(piece) && isBlackTurn) || (islower(piece) && isWhiteTurn));
		break;
	case 'P':
		isValid = MoveRules::isPawnMove(false, moveRecords, piecePositions) && isBlackTurn;
		break;
	case 'p':
		isValid = MoveRules::isPawnMove(true, moveRecords, piecePositions) && isWhiteTurn;
		break;
	}
	return isValid;
}


void Chess::moveStandardPiece(int x1, int y1, int x2, int y2) {
	char piece = piecePositions[y1][x1];
	bool isValid = false;

	switch (piece) {
	case 'K':
		isValid = MoveRules::isKingMove(x1, y1, x2, y2) && isBlackTurn;
		if (isValid) {
			blackKingPosition.first = x2;
			blackKingPosition.second = y2;
		}
		break;
	case'k':
		isValid = MoveRules::isKingMove(x1, y1, x2, y2) && isWhiteTurn;
		if (isValid) {
			whiteKingPosition.first = x2;
			whiteKingPosition.second = y2;
		}
		break;
	case 'Q': case 'q':
		isValid = MoveRules::isQueenMove(x1, y1, x2, y2) && isPathClear(x1, y1, x2, y2) &&
			((isupper(piece) && isBlackTurn) || (islower(piece) && isWhiteTurn));
		break;
	case 'B': case 'b':
		isValid = MoveRules::isBishopMove(x1, y1, x2, y2) && isPathClear(x1, y1, x2, y2) &&
			((isupper(piece) && isBlackTurn) || (islower(piece) && isWhiteTurn));
		break;
	case 'N': case 'n':
		isValid = MoveRules::isKnightMove(x1, y1, x2, y2) &&
			((isupper(piece) && isBlackTurn) || (islower(piece) && isWhiteTurn));
		break;
	case 'R': case 'r':
		isValid = MoveRules::isRookMove(x1, y1, x2, y2) && isPathClear(x1, y1, x2, y2) &&
			((isupper(piece) && isBlackTurn) || (islower(piece) && isWhiteTurn));
		break;
	case 'P':
		isValid = MoveRules::isPawnMove(false, moveRecords, piecePositions) && isBlackTurn;
		break;
	case 'p':
		isValid = MoveRules::isPawnMove(true, moveRecords, piecePositions) && isWhiteTurn;
		break;
	}

	if (isValid) {
		isPawnPromotedFlag = isPawnPromoted(x1, y1, x2, y2);
		piecePositions[y2][x2] = piece;
		piecePositions[y1][x1] = EMPTY_CELL;
		isWhiteTurn = !isWhiteTurn;
		isBlackTurn = !isBlackTurn;
	}
	else return;

}

void Chess::performEnPassant() {
	bool isValid = MoveRules::isEnPassantPossible(isWhiteTurn, moveRecords, piecePositions);
	if (isValid) {
		int x1 = moveRecords[moveRecords.size() - 4];
		int y1 = moveRecords[moveRecords.size() - 3];
		int x2 = moveRecords[moveRecords.size() - 2];
		int y2 = moveRecords[moveRecords.size() - 1];
		if (isWhiteTurn) {
			piecePositions[y1][x1] = EMPTY_CELL;
			piecePositions[y2][x2] = 'p';
			piecePositions[y2 + 1][x2] = EMPTY_CELL;
		}
		else if(isBlackTurn){
			piecePositions[y1][x1] = EMPTY_CELL;
			piecePositions[y2][x2] = 'P';
			piecePositions[y2 - 1][x2] = EMPTY_CELL;
		}
		isWhiteTurn = !isWhiteTurn;
		isBlackTurn = !isBlackTurn;
	}
}



void Chess::control() {
	if (moveRecords.size() % 4 == 0) {
		deleteUselessMoveRules(moveRecords[moveRecords.size() - 4],
			moveRecords[moveRecords.size() - 3],
			moveRecords[moveRecords.size() - 2],
			moveRecords[moveRecords.size() - 1]);
		if (MoveRules::isEnPassantPossible(isWhiteTurn, moveRecords, piecePositions)) {
			performEnPassant();
		}
		else {
			cout << "standard" << endl;
			moveStandardPiece(moveRecords[moveRecords.size() - 4],
				moveRecords[moveRecords.size() - 3],
				moveRecords[moveRecords.size() - 2],
				moveRecords[moveRecords.size() - 1]);
		}
		
	}
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
