#include "mouseInputs.h"
#include "logics.h"

void MouseInputs::updateMousePosition(SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		x = event.button.x;
		y = event.button.y;
		clickedCol = (x - BOARD_X) / CELL_SIZE;
		clickedRow = (y - BOARD_Y) / CELL_SIZE;
	}
}

bool MouseInputs::isInBoardClick(int x, int y) const {
	return (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE);
}

void MouseInputs::removeExcessClicks(Chess& game) {
	if (game.moveRecords.size() % 4 == 2) {
		if (!isInBoardClick(clickedCol, clickedRow)) {
			game.moveRecords.erase(game.moveRecords.end() - 2, game.moveRecords.end());
		}
	}
}