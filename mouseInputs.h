#ifndef _MOUSEINPUTS__H
#define _MOUSEINPUTS__H
#include <SDL.h>
#include "defs.h"

struct Chess;

struct MouseInputs {
	int x, y;
	int clickedCol, clickedRow;

	void updateMousePosition(SDL_Event& event);

	bool isInBoardClick(int x, int y) const;

	void removeExcessClicks(Chess& game);

};




#endif