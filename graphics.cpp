#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "logics.h"
#include "defs.h"

void Graphics::logErrorAndExit(const char* msg, const char* error)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
		"%s: %s", msg, error);
	SDL_Quit();
}
void Graphics::initSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		logErrorAndExit("SDL_Init", SDL_GetError());
	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (window == nullptr)
		logErrorAndExit("CreateWindow", SDL_GetError());
	if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
		logErrorAndExit("SDL_image error:", IMG_GetError());
	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
	if (renderer == nullptr)
		logErrorAndExit("CreateRenderer", SDL_GetError());
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}
void Graphics::prepareScene(SDL_Texture* background)
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, NULL, NULL);
}
void Graphics::presentScene()
{
	SDL_RenderPresent(renderer);
}
SDL_Texture* Graphics::loadTexture(const char* filename)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
		"Loading %s", filename);
	SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
	if (texture == NULL)
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
			SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());
	return texture;
}
void Graphics::renderTexture(SDL_Texture* texture, int x, int y)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(renderer, texture, NULL, &dest);
}
void Graphics::renderTexture(SDL_Texture* texture, int x, int y, int width, int height)
{
	SDL_Rect dest = { x, y, width, height };
	SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Graphics::quit()
{
	//black
	SDL_DestroyTexture(bR);
	bR = nullptr;
	SDL_DestroyTexture(bP);
	bP = nullptr;
	SDL_DestroyTexture(bQ);
	bQ = nullptr;
	SDL_DestroyTexture(bK);
	bK = nullptr;
	SDL_DestroyTexture(bB);
	bB = nullptr;
	SDL_DestroyTexture(bN);
	bN = nullptr;
	//white
	SDL_DestroyTexture(wR);
	wR = nullptr;
	SDL_DestroyTexture(wP);
	wP = nullptr;
	SDL_DestroyTexture(wQ);
	wQ = nullptr;
	SDL_DestroyTexture(wK);
	wK = nullptr;
	SDL_DestroyTexture(wB);
	wB = nullptr;
	SDL_DestroyTexture(wN);
	wN = nullptr;

	SDL_DestroyTexture(background);
	background = nullptr;
	SDL_DestroyTexture(board);
	board = nullptr;
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void Graphics::init() {
	initSDL();
	//black
	bR = loadTexture("img//bR.png");
	bQ = loadTexture("img//bQ.png");
	bK = loadTexture("img//bK.png");
	bP = loadTexture("img//bP.png");
	bB = loadTexture("img//bB.png");
	bN = loadTexture("img//bN.png");
	//white
	wR = loadTexture("img//wR.png");
	wQ = loadTexture("img//wQ.png");
	wK = loadTexture("img//wK.png");
	wP = loadTexture("img//wP.png");
	wB = loadTexture("img//wB.png");
	wN = loadTexture("img//wN.png");

	background = loadTexture("img//background.jpg");
	board = loadTexture("img//board.jpg");
}
void Graphics::render(const Chess& game) {
	prepareScene(background);
	{	//blur board
		SDL_SetTextureBlendMode(board, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(board, 210);
	}
	renderTexture(board, 350, 115, 400, 400);
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++) {
			int x = BOARD_X + j * CELL_SIZE;
			int y = BOARD_Y + i * CELL_SIZE;
			switch (game.piece_positions[i][j]) {
			case 'P': renderTexture(bP, x, y); break;
			case 'R': renderTexture(bR, x, y); break;
			case 'N': renderTexture(bN, x, y); break;
			case 'B': renderTexture(bB, x, y); break;
			case 'Q': renderTexture(bQ, x, y); break;
			case 'K': renderTexture(bK, x, y); break;
			case 'p': renderTexture(wP, x, y); break;
			case 'r': renderTexture(wR, x, y); break;
			case 'n': renderTexture(wN, x, y); break;
			case 'b': renderTexture(wB, x, y); break;
			case 'q': renderTexture(wQ, x, y); break;
			case 'k': renderTexture(wK, x, y); break;
			}
			presentScene();
		}
	
}