#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "logics.h"

using namespace std;

void processClickAt(int x, int y, Chess& game) {
    int clickedCol = (x - BOARD_X) / CELL_SIZE;
    int clickedRow = (y - BOARD_Y) / CELL_SIZE;
	game.moves.push_back(clickedCol);
	game.moves.push_back(clickedRow);

}

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();
    Chess game;
    game.init();
    graphics.render(game);
    int x, y;
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        SDL_PollEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x, &y);
            processClickAt(x, y, game);
            processClickAt(x, y, game);
            graphics.render(game);
            break;
        }
        SDL_Delay(0);
    }
    graphics.quit();
    return 0;
}