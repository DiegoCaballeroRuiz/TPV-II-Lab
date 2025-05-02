// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "LittleWolf.h"
#include "Networking.h"

Game::Game() :
		_little_wolf(new LittleWolf(this)),
		_networking(new Networking(this))//
{
}

Game::~Game() {

	// release InputHandler if the instance was created correctly.
	if (InputHandler::HasInstance())
		InputHandler::Release();

	// release SLDUtil if the instance was created correctly.
	if (SDLUtils::HasInstance())
		SDLUtils::Release();

	delete _little_wolf;
}

void Game::initGame() {
	_little_wolf->addPlayer(_networking->client_id());
}

void Game::init(const char *map, char* host, uint8_t port) {

	// load a map
	_little_wolf->load(map);

	// initialize the SDL singleton
	if (!SDLUtils::Init("[Little Wolf: " + std::string(map) + "]",
			_little_wolf->get_xres(),
			_little_wolf->get_yres(),
			"resources/config/littlewolf.resources.json")) {

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

	if (!_networking->init(host, port)) {
		SDLNetUtils::print_SDLNet_error();
		return;
	}


	_little_wolf->init(sdlutils().window(), sdlutils().renderer());
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.keyDownEvent()) {

			// ESC exists the game
			if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
				exit = true;
				continue;
			}

		}

		_little_wolf->update();

		// the clear is not necessary since the texture we copy to the window occupies the whole screen
		// sdlutils().clearRenderer();

		_little_wolf->render();

		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

