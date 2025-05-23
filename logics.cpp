﻿#include <vector>
#include <iostream>
#include <cmath>
#include <cctype>
#include "logics.h"
#include "moveRules.h"

using namespace std;
void Chess::init() {
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
		else if (!isValidStandardMove(x1, y1, x2, y2) &&
			!MoveRules::isEnPassantPossible(isWhiteTurn, moveRecords, piecePositions) &&
			!MoveRules::canCastleKingSide(isWhiteTurn, moveRecords, piecePositions, this) &&
			!MoveRules::canCastleQueenSide(isWhiteTurn, moveRecords, piecePositions, this)) {
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

void Chess::promotePawn() {
	int pawnPositionX = moveRecords[moveRecords.size() - 2];
	int pawnPositionY = moveRecords[moveRecords.size() - 1];
	if (isWhiteTurn) piecePositions[pawnPositionY][pawnPositionX] = 'Q';
	else piecePositions[pawnPositionY][pawnPositionX] = 'q';
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
	if (piecePositions[whiteKingPosition.second][whiteKingPosition.first] != 'k') {
		return true;
	}
	return false;
}

bool Chess::isBlackKingDead() const {
	if (piecePositions[blackKingPosition.second][blackKingPosition.first] != 'K') {
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
		isWhiteTurn = !isWhiteTurn;
		if (isSquareAttackedByWhite(blackKingPosition.first, blackKingPosition.second)) {
			checkmateBlack = true;
		}
		else checkmateBlack = false;
		if (isSquareAttackedByBlack(whiteKingPosition.first, whiteKingPosition.second)) {
			checkmateWhite = true;
		}
		else checkmateWhite = false;

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
			isWhiteTurn = !isWhiteTurn;
		}
		else if (!isWhiteTurn) {
			piecePositions[y1][x1] = EMPTY_CELL;
			piecePositions[y2][x2] = 'P';
			piecePositions[y2 - 1][x2] = EMPTY_CELL;
			isWhiteTurn = !isWhiteTurn;
		}
	}
}



void Chess::control() {
	numberOfPiecesBeforeMove = countRemaningPieces();
	if (moveRecords.size() % 4 == 0) {
		deleteUselessMoveRules(moveRecords[moveRecords.size() - 4],
			moveRecords[moveRecords.size() - 3],
			moveRecords[moveRecords.size() - 2],
			moveRecords[moveRecords.size() - 1]);

		if (MoveRules::isEnPassantPossible(isWhiteTurn, moveRecords, piecePositions)) {
			performEnPassant();
			isWhiteTurn = !isWhiteTurn;
		}
		else if (MoveRules::canCastleQueenSide(isWhiteTurn, moveRecords, piecePositions, this)) {
			castleQueenSide(moveRecords[moveRecords.size() - 4],
				moveRecords[moveRecords.size() - 3],
				moveRecords[moveRecords.size() - 2],
				moveRecords[moveRecords.size() - 1]);
		}
		else if (MoveRules::canCastleKingSide(isWhiteTurn, moveRecords, piecePositions, this)) {
			castleKingSide(moveRecords[moveRecords.size() - 4],
				moveRecords[moveRecords.size() - 3],
				moveRecords[moveRecords.size() - 2],
				moveRecords[moveRecords.size() - 1]);

		}
		else if (isPawnPromotedFlag) {
			promotePawn();
			isPawnPromotedFlag = false;
		}
		else {
			moveStandardPiece(moveRecords[moveRecords.size() - 4],
				moveRecords[moveRecords.size() - 3],
				moveRecords[moveRecords.size() - 2],
				moveRecords[moveRecords.size() - 1]);

		}
		numberOfPiecesAfterMove = countRemaningPieces();
		if (isWhiteKingDead()) blackWin = true;
		else if (isBlackKingDead()) whiteWin = true;

	}
}
bool Chess::isSquareAttackedByWhite(int x, int y)const {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (islower(piecePositions[i][j])) {
				char piece = piecePositions[i][j];
				bool isValid = false;
				switch (piece) {
				case'k':
					isValid = MoveRules::isKingMove(j, i, x, y);
					break;
				case 'q':
					isValid = MoveRules::isQueenMove(j, i, x, y) && isPathClear(j, i, x, y);
					break;
				case 'b':
					isValid = MoveRules::isBishopMove(j, i, x, y) && isPathClear(j, i, x, y);
					break;
				case 'n':
					isValid = MoveRules::isKnightMove(j, i, x, y);
					break;
				case 'p':
					isValid = MoveRules::isPawnMove(true, moveRecords, piecePositions);
					break;
				}
				if (isValid) return true;
			}

		}
	}
	return false;
}

bool Chess::isSquareAttackedByBlack(int x, int y)const {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (isupper(piecePositions[i][j])) {
				char piece = piecePositions[i][j];
				bool isValid = false;
				switch (piece) {
				case 'K':
					isValid = MoveRules::isKingMove(j, i, x, y);
					break;
				case 'Q':
					isValid = MoveRules::isQueenMove(j, i, x, y) && isPathClear(j, i, x, y);
					break;
				case 'B':
					isValid = MoveRules::isBishopMove(j, i, x, y) && isPathClear(j, i, x, y);
					break;
				case 'N':
					isValid = MoveRules::isKnightMove(j, i, x, y);
					break;
				case 'P':
					isValid = MoveRules::isPawnMove(false, moveRecords, piecePositions);
					break;
				}
				if (isValid) return true;
			}
		}
	}
	return false;
}

void Chess::castleQueenSide(int x1, int y1, int x2, int y2) {
	if (isWhiteTurn) {
		if (!hasWhiteKingMoved && !hasWhiteQueenSideRookMoved) {
			if (x1 == 4 && y1 == 7 && x2 == 2 && y2 == 7) {
				piecePositions[7][4] = EMPTY_CELL;
				piecePositions[7][2] = 'k';
				piecePositions[7][3] = 'r';
				piecePositions[7][0] = EMPTY_CELL;
				whiteKingPosition.first = 2;
				whiteKingPosition.second = 7;
				hasWhiteKingMoved = true;
				hasWhiteQueenSideRookMoved = true;
				isWhiteTurn = !isWhiteTurn;
			}
		}
	}
	else {
		if (!hasBlackKingMoved && !hasBlackQueenSideRookMoved) {
			if (x1 == 4 && y1 == 0 && x2 == 2 && y2 == 0) {
				piecePositions[0][4] = EMPTY_CELL;
				piecePositions[0][2] = 'K';
				piecePositions[0][3] = 'R';
				piecePositions[0][0] = EMPTY_CELL;
				blackKingPosition.first = 2;
				blackKingPosition.second = 0;
				hasBlackKingMoved = true;
				hasBlackQueenSideRookMoved = true;
				isWhiteTurn = !isWhiteTurn;

			}
		}
	}
}

void Chess::castleKingSide(int x1, int y1, int x2, int y2) {
	if (isWhiteTurn) {
		if (!hasWhiteKingMoved && !hasWhiteKingSideRookMoved) {
			if (x1 == 4 && y1 == 7 && x2 == 6 && y2 == 7) {
				piecePositions[7][4] = EMPTY_CELL;
				piecePositions[7][6] = 'k';
				piecePositions[7][5] = 'r';
				piecePositions[7][7] = EMPTY_CELL;
				whiteKingPosition.first = 6;
				whiteKingPosition.second = 7;
				hasWhiteKingMoved = true;
				hasWhiteKingSideRookMoved = true;
				isWhiteTurn = !isWhiteTurn;
			}
		}
	}
	else {
		if (!hasBlackKingMoved && !hasBlackKingSideRookMoved) {
			if (x1 == 4 && y1 == 0 && x2 == 6 && y2 == 0) {
				piecePositions[0][4] = EMPTY_CELL;
				piecePositions[0][6] = 'K';
				piecePositions[0][5] = 'R';
				piecePositions[0][7] = EMPTY_CELL;
				blackKingPosition.first = 6;
				blackKingPosition.second = 0;
				hasBlackKingMoved = true;
				hasBlackKingSideRookMoved = true;
				isWhiteTurn = !isWhiteTurn;
			}
		}
	}
}

void Chess::reset() {
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			piecePositions[i][j] = initialBoard[i][j];
	moveRecords.clear();
	moveRecords.resize(4, -1);
	blackKingPosition.first = 4;
	blackKingPosition.second = 0;
	whiteKingPosition.first = 4;
	whiteKingPosition.second = 7;
	isPawnPromotedFlag = false;
	isWhiteTurn = true;
	checkmateBlack = false;
	checkmateWhite = false;
	whiteWin = false;
	blackWin = false;
	hasWhiteKingMoved = false;
	hasWhiteQueenSideRookMoved = false;
	hasWhiteKingSideRookMoved = false;
	hasBlackKingMoved = false;
	hasBlackQueenSideRookMoved = false;
	hasBlackKingSideRookMoved = false;
}

int Chess::countRemaningPieces() {
	int pieces = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (piecePositions[i][j] != EMPTY_CELL) pieces++;
		}
	}return pieces;
}