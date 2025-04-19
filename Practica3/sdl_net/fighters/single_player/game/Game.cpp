// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"

#include "Bullets.h"
#include "Fighter.h"

Game::Game() :
		_bm(nullptr), //
		_fighters(nullptr) //
{
}

Game::~Game() {
	delete _fighters;
	delete _bm;

// release InputHandler if the instance was created correctly.
	if (InputHandler::HasInstance())
		InputHandler::Release();

// release SLDUtil if the instance was created correctly.
	if (SDLUtils::HasInstance())
		SDLUtils::Release();
}

void Game::init() {

// initialize the SDL singleton
	if (!SDLUtils::Init("SDLNet Game", 900, 480,
			"resources/config/asteroids.resources.json")) {

		std::cerr << "Something went wrong while initializing SDLUtils"
				<< std::endl;
		return;
	}

// initialize the InputHandler singleton
	if (!InputHandler::Init()) {
		std::cerr << "Something went wrong while initializing SDLHandler"
				<< std::endl;
		return;

	}

	_bm = new Bullets();
	_fighters = new Fighter(*_bm);

}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	auto &vt = sdlutils().virtualTimer();

	while (!exit) {
		Uint32 startTime = vt.regCurrTime();

		// refresh the input handler
		ihdlr.refresh();
		if (ihdlr.keyDownEvent()) {

			// ESC exists the game
			if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
				exit = true;
				continue;
			}

		}

		_fighters->update();
		_bm->update();

		sdlutils().clearRenderer();

		_fighters->render();
		_bm->render();

		sdlutils().presentRenderer();

		Uint32 frameTime = vt.currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}

