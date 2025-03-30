#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "logics.h"

struct Graphics {
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Texture* bP, * bN, * bK, * bQ, * bB, * bR, * wP, * wN, * wK, * wQ, * wB, * wR, * background,*board;

	void logErrorAndExit(const char* msg, const char* error);

	void initSDL();

	void prepareScene(SDL_Texture* background);

	void presentScene();

	SDL_Texture* loadTexture(const char* filename);

	void renderTexture(SDL_Texture* texture, int x, int y);

	void renderTexture(SDL_Texture* texture, int x, int y, int width, int height);

	void start();

	void quit();

	void init();

	void render(const Chess& game);
};
#endif 