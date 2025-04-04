#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "logics.h"
#include "mouseInputs.h"

using namespace std;

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();
    Chess game;
    game.init();
	MouseInputs mouseInputs;
    graphics.render(game);
    SDL_Event event;
    bool quit = false;

    while (!quit) {
        SDL_PollEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
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
            break;
        }
       
    }
    graphics.quit();
    return 0;
}