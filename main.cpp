#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "defs.h"
#include "graphics.h"
#include "logics.h"
#include "mouseInputs.h"
#include "audios.h"

using namespace std;

int main(int argc, char* argv[])
{
	Graphics graphics;
	graphics.init();
	Audios audios;
	audios.init();
	audios.play(audios.backgroundMusic);
	Chess game;
	game.init();
	MouseInputs mouseInputs;
	graphics.startGame();
	SDL_Event event;
	bool quit = false;
	while (!quit) {
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (!graphics.isStarting) {
				mouseInputs.updateMousePosition(event);
				game.moveRecords.push_back(mouseInputs.clickedCol);
				game.moveRecords.push_back(mouseInputs.clickedRow);
				mouseInputs.removeExcessClicks(game);
				cout << game.moveRecords.size() << endl;
				for (int x : game.moveRecords)
					cout << x << " ";
				cout << endl;
				game.control();
				graphics.render(game);
				audios.playSound(game);
				if (game.whiteWin || game.blackWin) {
					game.reset();
				}
				break;
			}
			else {
				graphics.isStarting = false;
				graphics.render(game);
				break;
			}

		}

	}
	graphics.quit();
	audios.quit();
	return 0;
}