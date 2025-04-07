#ifndef _AUDIOS__H
#define _AUDIOS__H
#include <SDL.h>
#include <SDL_mixer.h>

struct Audios {
	Mix_Music* backgroundMusic = nullptr;

	void initSDL_Mixer();

	Mix_Music* loadMusic(const char* path);

	void init();

	void quit();

	void play(Mix_Music* gMusic);

	Mix_Chunk* loadSound(const char* path);

	void play(Mix_Chunk* gChunk);

	void freeMusic(Mix_Music* music);

	void freeSound(Mix_Chunk* sound);

};

#endif