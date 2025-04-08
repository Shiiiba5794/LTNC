#include <SDL.h>
#include <SDL_mixer.h>
#include "audios.h"
#include "moveRules.h"
#include<iostream>

void Audios::initSDL_Mixer() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
			"SDL_mixer could not initialize! SDL_mixer Error: %s", Mix_GetError());
	}
}
Mix_Music* Audios::loadMusic(const char* path)
{
	Mix_Music* gMusic = Mix_LoadMUS(path);
	if (gMusic == nullptr) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
			"Could not load music! SDL_mixer Error: %s", Mix_GetError());
	}
	return gMusic;
}
void Audios::init() {
	initSDL_Mixer();
	backgroundMusic = loadMusic("audio//background.mp3");
	moveSound = loadSound("audio//move.mp3");
	captureSound = loadSound("audio//capture.mp3");
	checkmateSound = loadSound("audio//checkmate.mp3");
	endgameSound = loadSound("audio//endgame.mp3");
}
void Audios::quit() {
	Mix_FreeMusic(backgroundMusic);
	backgroundMusic = nullptr;
	Mix_FreeChunk(moveSound);
	moveSound = nullptr;
	Mix_FreeChunk(captureSound);
	captureSound = nullptr;
	Mix_FreeChunk(checkmateSound);
	checkmateSound = nullptr;
	Mix_FreeChunk(endgameSound);
	endgameSound = nullptr;
	Mix_CloseAudio();
	Mix_Quit();
}
void Audios::play(Mix_Music* gMusic)
{
	if (gMusic == nullptr) return;
	if (Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(gMusic, -1);
	}
	else if (Mix_PausedMusic() == 1) {
		Mix_ResumeMusic();
	}
}

Mix_Chunk* Audios::loadSound(const char* path) {
	Mix_Chunk* gChunk = Mix_LoadWAV(path);
	if (gChunk == nullptr) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
			"Could not load sound! SDL_mixer Error: %s", Mix_GetError());
	}
	return gChunk;
}
void Audios::play(Mix_Chunk* gChunk) {
	if (gChunk != nullptr) {
		Mix_PlayChannel(-1, gChunk, 0);
	}
}
void Audios::freeMusic(Mix_Music* music) {
	Mix_FreeMusic(music);
}
void Audios::freeSound(Mix_Chunk* sound) {
	Mix_FreeChunk(sound);
}
void Audios::playSound(Chess& game) {
	if (game.moveRecords.size() % 4 == 0) {
		if (game.numberOfPiecesAfterMove < game.numberOfPiecesBeforeMove) {
			play(captureSound);
		}
		else if (game.numberOfPiecesAfterMove == game.numberOfPiecesBeforeMove) {
			play(moveSound);
		}
		if (game.checkmateBlack || game.checkmateWhite) {
			play(checkmateSound);
		}if (game.whiteWin || game.blackWin) {
			play(endgameSound);
		}
	}
}