// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"


#include "../components/StopOnBorders.h"

#include "../components/Transform.h"


#include "FighterUtils.h"
#include "AsteroidsUtils.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

#include "NewGameState.h"
#include "NewRoundState.h"
#include "RunningState.h"
#include "PausedState.h"
#include "GameOverState.h"
using ecs::Manager;

Game::Game() :
		_mngr(nullptr), _asteroidUtils(nullptr), _fighterUtils(nullptr)
		
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

bool Game::init() {

	//initialize the SDL singleton
	if (!SDLUtils::Init("PacMan, Stars, ...", 800, 600,
		"../resources/config/resources.json")) {
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

	return true;
}

void Game::initGame() {

	//Start virtual timer
	sdlutils().virtualTimer().resetTime();

	// Create the manager
	_mngr = new Manager();

	//Inicializar los estados de juego
	_newgame_state = new NewGameState(this);
	_newround_state = new NewRoundState(this);
	_runing_state = new RunningState(this, _mngr);
	_paused_state = new PausedState(this);
	_gameover_state = new GameOverState(this);

	_state = _newgame_state;
	//Crear la nave
	_fighterUtils = new FighterUtils(_mngr);

	_fighterUtils->create_fighter();

	//Crear un asteroide 
	_asteroidUtils = new AsteroidsUtils(_mngr);

	//_asteroidUtils->create_asteroids(3);
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	// reset the time before starting - so we calculate correct
	// delta-time in the first iteration
	//
	sdlutils().virtualTimer().resetTime();

	while (!exit) {
		// store the current time -- all game objects should use this time when
		// then need to the current time. They also have accessed to the time elapsed
		// between the last two calls to regCurrTime().
		Uint32 startTime = sdlutils().regCurrTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
		}

		_state->update();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);

		sdlutils().virtualTimer().regCurrTime();
	}
}

void Game::checkCollisions() {
//
//	// the PacMan's Transform
//	//
//	auto pacman = _mngr->getHandler(ecs::hdlr::PACMAN);
//	auto pTR = _mngr->getComponent<Transform>(pacman);
//
//	// the GameCtrl component
//	auto ginfo = _mngr->getHandler(ecs::hdlr::GAMEINFO);
//	auto gctrl = _mngr->getComponent<GameCtrl>(ginfo);
//
//	// For safety, we traverse with a normal loop until the current size. In this
//	// particular case we could use a for-each loop since the list stars is not
//	// modified.
//	//
//	auto &stars = _mngr->getEntities(ecs::grp::STARS);
//	auto n = stars.size();
//	for (auto i = 0u; i < n; i++) {
//		auto e = stars[i];
//		if (_mngr->isAlive(e)) { // if the star is active (it might have died in this frame)
//
//			// the Star's Transform
//			//
//			auto eTR = _mngr->getComponent<Transform>(e);
//
//			// check if PacMan collides with the Star (i.e., eat it)
//			if (Collisions::collides(pTR->getPos(), pTR->getWidth(),
//					pTR->getHeight(), //
//					eTR->getPos(), eTR->getWidth(), eTR->getHeight())) {
//				_mngr->setAlive(e, false);
//				gctrl->onStarEaten();
//
//				// play sound on channel 1 (if there is something playing there
//				// it will be cancelled
//				sdlutils().soundEffects().at("pacman_eat").play(0, 1);
//			}
//		}
//	}
}
