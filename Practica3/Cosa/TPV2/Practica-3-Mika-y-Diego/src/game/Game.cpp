// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "LittleWolf.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLNetUtils.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "Networking.h"

Game::Game() :
		_littleWolf(nullptr), //
		_networking(nullptr) {
}

Game::~Game() {
	delete _littleWolf;
	delete _networking;

	// release InputHandler if the instance was created correctly.
	if (InputHandler::HasInstance())
		InputHandler::Release();

	// release SLDUtil if the instance was created correctly.
	if (SDLUtils::HasInstance())
		SDLUtils::Release();

}

bool Game::initGame() {
	_littleWolf->addPlayer(_networking->client_id());
	return true;
}

bool Game::init(const char *map, char *host, Uint16 port) {

	_networking = new Networking();

	if (!_networking->init(host, port)) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}
	std::cout << "Connected as client " << (int) _networking->client_id() << std::endl;

	_littleWolf = new LittleWolf(this);
	_littleWolf->load(map);

	// initialize the SDL singleton
	if (!SDLUtils::Init("SDLNet Game", 800, 600,
			"resources/config/asteroids.multiplayer.resources.json")) {

		std::cerr << "Something went wrong while initializing SDLUtils"
				<< std::endl;
		return false;
	}

	// initialize the InputHandler singleton
	if (!InputHandler::Init()) {
		std::cerr << "Something went wrong while initializing SDLHandler"
				<< std::endl;
		return false;

	}

	_littleWolf->init(sdlutils().window(), sdlutils().renderer());

	sdlutils().virtualTimer().resetTime();

	return true;
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

		_littleWolf->update();
		_networking->update();

		sdlutils().clearRenderer();

		_littleWolf->render();

		sdlutils().presentRenderer();

		Uint32 frameTime = vt.currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

	_networking->disconnect();

}
