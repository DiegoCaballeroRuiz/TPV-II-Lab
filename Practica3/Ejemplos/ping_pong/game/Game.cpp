// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/BallSystem.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/NetworkSystem.h"
#include "../systems/PaddlesSystem.h"
#include "../systems/RenderSystem.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

using ecs::Manager;

Game::Game() :
		_mngr(nullptr), //
		_ballSys(nullptr), //
		_paddlesSys(nullptr), //
		_gameCtrlSys(nullptr), //
		_collisionsSys(nullptr), //
		_renderSys(nullptr), //
		_netSys(nullptr) {
}

Game::~Game() {
	delete _mngr;

	// release InputHandler if the instance was created correctly.
	if (InputHandler::HasInstance())
		InputHandler::Release();

	// release SLDUtil if the instance was created correctly.
	if (SDLUtils::HasInstance())
		SDLUtils::Release();
}

bool Game::init() {

	// initialize the SDL singleton
	if (!SDLUtils::Init("Ping Pong", 800, 600,
			"resources/config/pingpong.resources.json")) {

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

	sdlutils().hideCursor();

	// Create the manager
	_mngr = new Manager();

	_netSys = _mngr->addSystem<NetworkSystem>();

	if (!_netSys->connect()) {
		return false;
	}

	_ballSys = _mngr->addSystem<BallSystem>();
	_paddlesSys = _mngr->addSystem<PaddlesSystem>();
	_gameCtrlSys = _mngr->addSystem<GameCtrlSystem>();
	_collisionsSys = _mngr->addSystem<CollisionsSystem>();
	_renderSys = _mngr->addSystem<RenderSystem>();

	return true;

}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().regCurrTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			_netSys->disconnect();
			exit = true;
			continue;
		}

		_mngr->refresh();

		_ballSys->update();
		_paddlesSys->update();
		_collisionsSys->update();
		_gameCtrlSys->update();
		_netSys->update();
		sdlutils().clearRenderer();
		_renderSys->update();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}
