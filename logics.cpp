#include <vector>
#include <iostream>
#include <cmath>
#include <cctype>
#include "logics.h"
#include "moveRules.h"

using namespace std;
void Chess::init() {
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

	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			piecePositions[i][j] = initialBoard[i][j];
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
		else if (!isValidStandardMove(x1, y1, x2, y2)&&!MoveRules::isEnPassantPossible(isWhiteTurn,moveRecords,piecePositions)) {
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

bool Chess::isValidStandardMove(int x1, int y1, int x2, int y2) const {
	char piece = piecePositions[y1][x1];
	bool isValid = false;
	switch (piece) {
	case 'K':case'k':
		isValid = MoveRules::isKingMove(x1, y1, x2, y2) &&
			((isupper(piece) && !isWhiteTurn) || (islower(piece) && isWhiteTurn));
		break;
	case 'Q': case 'q':
		isValid = MoveRules::isQueenMove(x1, y1, x2, y2) && isPathClear(x1, y1, x2, y2) &&
			((isupper(piece) && !isWhiteTurn) || (islower(piece) && isWhiteTurn));
		break;
	case 'B': case 'b':
		isValid = MoveRules::isBishopMove(x1, y1, x2, y2) && isPathClear(x1, y1, x2, y2) &&
			((isupper(piece) && !isWhiteTurn) || (islower(piece) && isWhiteTurn));
		break;
	case 'N': case 'n':
		isValid = MoveRules::isKnightMove(x1, y1, x2, y2) &&
			((isupper(piece) && !isWhiteTurn) || (islower(piece) && isWhiteTurn));
		break;
	case 'R': case 'r':
		isValid = MoveRules::isRookMove(x1, y1, x2, y2) && isPathClear(x1, y1, x2, y2) &&
			((isupper(piece) && !isWhiteTurn) || (islower(piece) && isWhiteTurn));
		break;
	case 'P':
		isValid = MoveRules::isPawnMove(false, moveRecords, piecePositions) && !isWhiteTurn;
		break;
	case 'p':
		isValid = MoveRules::isPawnMove(true, moveRecords, piecePositions) && isWhiteTurn;
		break;
	}
	return isValid;
}

bool Chess::isWhiteKingDead() const {
	if (piecePositions[whiteKingPosition.second][whiteKingPosition.first] !='k') {
		return true;
	}
	return false;
}

bool Chess::isBlackKingDead() const {
	if (piecePositions[blackKingPosition.second][blackKingPosition.first]!='K') {
		return true;
	}
	return false;
}

void Chess::moveStandardPiece(int x1, int y1, int x2, int y2) {
	char piece = piecePositions[y1][x1];
	bool isValid = false;

	switch (piece) {
	case 'K':
		isValid = MoveRules::isKingMove(x1, y1, x2, y2) && !isWhiteTurn;
		if (isValid) {
			blackKingPosition.first = x2;
			blackKingPosition.second = y2;
			hasBlackKingMoved = true;
		}
		break;
	case'k':
		isValid = MoveRules::isKingMove(x1, y1, x2, y2) && isWhiteTurn;
		if (isValid) {
			whiteKingPosition.first = x2;
			whiteKingPosition.second = y2;
			hasWhiteKingMoved = true;
		}
		break;
	case 'Q': case 'q':
		isValid = MoveRules::isQueenMove(x1, y1, x2, y2) && isPathClear(x1, y1, x2, y2) &&
			((isupper(piece) && !isWhiteTurn) || (islower(piece) && isWhiteTurn));
		break;
	case 'B': case 'b':
		isValid = MoveRules::isBishopMove(x1, y1, x2, y2) && isPathClear(x1, y1, x2, y2) &&
			((isupper(piece) && !isWhiteTurn) || (islower(piece) && isWhiteTurn));
		break;
	case 'N': case 'n':
		isValid = MoveRules::isKnightMove(x1, y1, x2, y2) &&
			((isupper(piece) && !isWhiteTurn) || (islower(piece) && isWhiteTurn));
		break;
	case 'R': 
		isValid = MoveRules::isRookMove(x1, y1, x2, y2) && isPathClear(x1, y1, x2, y2) && !isWhiteTurn;
		if (isValid) {
			if (x1 == 0 && y1 == 0) hasBlackQueenSideRookMoved = true;
			else if (x1 == 7 && y1 == 0) hasBlackKingSideRookMoved = true;
		}
		break;
	case 'r':
		isValid = MoveRules::isRookMove(x1, y1, x2, y2) && isPathClear(x1, y1, x2, y2) && isWhiteTurn;
		if (isValid) {
			if (x1 == 0 && y1 == 7) hasWhiteQueenSideRookMoved = true;
			else if (x1 == 7 && y1 == 7) hasWhiteKingSideRookMoved = true;
		}
		break;
	case 'P':
		isValid = MoveRules::isPawnMove(false, moveRecords, piecePositions) && !isWhiteTurn;
		break;
	case 'p':
		isValid = MoveRules::isPawnMove(true, moveRecords, piecePositions) && isWhiteTurn;
		break;
	}

	if (isValid) {
		isPawnPromotedFlag = isPawnPromoted(x1, y1, x2, y2);
		piecePositions[y2][x2] = piece;
		piecePositions[y1][x1] = EMPTY_CELL;
		if (isSquareAttackedByWhite(blackKingPosition.first, blackKingPosition.second)) {
			checkmateBlack = true;
		}
		else checkmateBlack = false;
		if (isSquareAttackedByBlack(whiteKingPosition.first, whiteKingPosition.second)) {
			checkmateWhite = true;
		}
		else checkmateWhite = false;
		
		isWhiteTurn = !isWhiteTurn;
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
		else if(!isWhiteTurn){
			piecePositions[y1][x1] = EMPTY_CELL;
			piecePositions[y2][x2] = 'P';
			piecePositions[y2 - 1][x2] = EMPTY_CELL;
		}
		isWhiteTurn = !isWhiteTurn;
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
			moveStandardPiece(moveRecords[moveRecords.size() - 4],
				moveRecords[moveRecords.size() - 3],
				moveRecords[moveRecords.size() - 2],
				moveRecords[moveRecords.size() - 1]);
		}
		if (isWhiteKingDead()) blackWin = true;
		else if (isBlackKingDead()) whiteWin = true;
		
	}
}
bool Chess::isSquareAttackedByWhite(int x,int y)const {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (islower(piecePositions[i][j])) {
				if(isValidStandardMove(j, i, x,y)) return true;
			}

		}
	}
	return false;
}

bool Chess::isSquareAttackedByBlack(int x,int y)const {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (isupper(piecePositions[i][j])) {
				if (isValidStandardMove(j, i, x, y))return true;
			}

		}
	}
	return false;
}

void Chess::castleQueenSide(int x1, int y1, int x2, int y2) {
	if (isWhiteTurn) {
		if (!hasWhiteKingMoved && !hasWhiteQueenSideRookMoved) {
			if (x1 == 4 && y1 == 7 && x2 == 2 && y2 == 7) {
				piecePositions[y1][x1] = EMPTY_CELL;
				piecePositions[y1][x2] = 'k';
				piecePositions[y1][x2 + 1] = 'r';
				piecePositions[y1][x2 - 1] = EMPTY_CELL;
				hasWhiteKingMoved = true;
				hasWhiteQueenSideRookMoved = true;
			}
		}
	}
	else {
		if (!hasBlackKingMoved && !hasBlackQueenSideRookMoved) {
			if (x1 == 4 && y1 == 0 && x2 == 2 && y2 == 0) {
				piecePositions[y1][x1] = EMPTY_CELL;
				piecePositions[y1][x2] = 'K';
				piecePositions[y1][x2 + 1] = 'R';
				piecePositions[y1][x2 - 1] = EMPTY_CELL;
				hasBlackKingMoved = true;
				hasBlackQueenSideRookMoved = true;
			}
		}
	}
}

void Chess::castleKingSide(int x1, int y1, int x2, int y2) {
	if (isWhiteTurn) {
		if (!hasWhiteKingMoved && !hasWhiteKingSideRookMoved) {
			if (x1 == 4 && y1 == 7 && x2 == 6 && y2 == 7) {
				piecePositions[y1][x1] = EMPTY_CELL;
				piecePositions[y1][x2] = 'k';
				piecePositions[y1][x2 - 1] = 'r';
				piecePositions[y1][x2 + 1] = EMPTY_CELL;
				hasWhiteKingMoved = true;
				hasWhiteKingSideRookMoved = true;
			}
		}
	}
	else {
		if (!hasBlackKingMoved && !hasBlackKingSideRookMoved) {
			if (x1 == 4 && y1 == 0 && x2 == 6 && y2 == 0) {
				piecePositions[y1][x1] = EMPTY_CELL;
				piecePositions[y1][x2] = 'K';
				piecePositions[y1][x2 - 1] = 'R';
				piecePositions[y1][x2 + 1] = EMPTY_CELL;
				hasBlackKingMoved = true;
				hasBlackKingSideRookMoved = true;
			}
		}
	}
}