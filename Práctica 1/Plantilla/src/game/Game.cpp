// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/GameCtrl.h"
#include "../components/Image.h"
#include "../components/ImageWithFrames.h"
#include "../components/DeAcceleration.h"
#include "../components/StopOnBorders.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../components/FighterCtrl.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Gun.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

using ecs::Manager;

Game::Game() :
		_mngr(nullptr) {
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

	//initialize the SDL singleton
	if (!SDLUtils::Init("PacMan, Stars, ...", 800, 600,
		"../resources/config/resources.json")) {
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

	//Crear la nave
	auto nave = _mngr->addEntity();
	_mngr->setHandler(ecs::hdlr::SHIP, nave);

	sdlutils().virtualTimer().resetTime();

	auto transform = _mngr->addComponent<Transform>(nave);
	float scale = 50.0f;
	float x = (sdlutils().width() - scale) / 2.0f;
	float y = (sdlutils().height() - scale) / 2.0f;
	transform->init(Vector2D(x, y), { 0, 0 }, scale, scale, 0.0f);

	_mngr->addComponent<DeAcceleration>(nave);

	_mngr->addComponent<Image>(nave, &sdlutils().images().at("asteroid"));

	scale = 50.0f;
	x = (sdlutils().width() - scale) * 0.01f;
	y = (sdlutils().height() - scale) * 0.01f;
	SDL_Rect heartPos = {x, y, scale, scale};
	_mngr->addComponent<Health>(nave, heartPos, 10.0f, &sdlutils().images().at("heart"));

	_mngr->addComponent<FighterCtrl>(nave);

	_mngr->addComponent<Gun>(nave, &sdlutils().images().at("bullet"));

	_mngr->addComponent<ShowAtOppositeSide>(nave);
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
			continue;
		}

		_mngr->update();
		_mngr->refresh();

		checkCollisions();

		sdlutils().clearRenderer();
		_mngr->render();
		sdlutils().presentRenderer();

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
