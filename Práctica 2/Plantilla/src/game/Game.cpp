// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/PacManSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/StarsSystem.h"
#include "../systems/FruitSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/StateChangeSystem.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"
#include "NewGameState.h"
#include "NewRoundState.h"
#include "PausedState.h"
#include "RunningState.h"
#include "GameOverState.h"
#include "GameState.h"

using ecs::Manager;

Game::Game() :
	_mngr(), //
	_pacmanSys(), //
	_fruitSys(), //
	_renderSys(), //
	_collisionSys()
{
	
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

void Game::init() {

	// initialize the SDL singleton
	if (!SDLUtils::Init("PacMan, Stars, ...", 800, 600,
			"resources/config/resources.json")) {

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

	// Create the manager
	_mngr = new Manager();

	// add the systems
	_pacmanSys = _mngr->addSystem<PacManSystem>();
	_renderSys = _mngr->addSystem<RenderSystem>();
	_collisionSys = _mngr->addSystem<CollisionsSystem>();
	_fruitSys = _mngr->addSystem<FruitSystem>();
	_ghostSys = _mngr->addSystem<GhostSystem>();
	_stateSys = _mngr->addSystem<StateChangeSystem>(this);

	_pacmanSys->initSystem();
	_ghostSys->initSystem();
	_fruitSys->initSystem();
	_collisionSys->initSystem();
	_renderSys->initSystem();
	_stateSys->initSystem();

	//add the states
	_newgame_state = new NewGameState(this);
	_newround_state = new NewRoundState(this);
	_paused_state = new PausedState(this);
	_gameover_state = new GameOverState(this);
	_runing_state = new RunningState(this);

	Message m;
	m.id = msgId::_m_NEW_GAME;
	_mngr->send(m);
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();
	sdlutils().virtualTimer().resetTime();
	sdlutils().virtualTimer().resume();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		_state->update();

		_mngr->refresh();

		sdlutils().clearRenderer();
		_renderSys->update();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);

		sdlutils().virtualTimer().regCurrTime();
	}

}

