#include "RunningState.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "AsteroidsUtils.h"
#include "../ecs/Manager.h"
#include "Game.h"
#include "FighterUtils.h"
#include "../utils/Collisions.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../components/Gun.h"

RunningState::RunningState(Game* game, ecs::Manager* manager) : GameState(game), _manager(manager), _lastTimeAstroidAdded(0)
{
	_inputHandler = InputHandler::Instance();
}

void
RunningState::update() {
	if (_game->getAsteroidsUtils()->getNumberOfAsteroids() == 0) 
		_game->setState(Game::GAMEOVER);

	if (_inputHandler->isKeyDown(SDLK_p))
		_game->setState(Game::PAUSED);

	_manager->update();

	checkCollisions();

	sdlutils().clearRenderer();
	_manager->render();
	sdlutils().presentRenderer();

	_manager->refresh();

	if (sdlutils().currTime() - _lastTimeAstroidAdded > 5000) {
		_game->getAsteroidsUtils()->create_asteroids(1);
		_lastTimeAstroidAdded = sdlutils().virtualTimer().currTime();
	}
}


void
RunningState::checkCollisions() {
	auto fighter = _manager->getHandler(ecs::hdlr::SHIP);
	auto fighterTr = _manager->getComponent<Transform>(fighter);
	auto asteroids = _manager->getEntities(ecs::grp::ASTEROIDS);

	for (int i = 0; i < asteroids.size(); ++i) {
		auto aTr = _manager->getComponent<Transform>(asteroids.at(i));
		// Si hay colisión entre asteroide y caza
		if (Collisions::collidesWithRotation(
			fighterTr->getPos(), fighterTr->getWidth(), fighterTr->getHeight(), fighterTr->getRot(),
			aTr->getPos(), aTr->getWidth(), aTr->getHeight(), aTr->getRot()))
		{
			_game->getFightersUtils()->update_lives(-1);
			auto fighterHealth = _manager->getComponent<Health>(fighter);
			if (fighterHealth->getHealth() > 0)
				Game::Instance()->setState(Game::NEWROUND);
			else
				Game::Instance()->setState(Game::GAMEOVER);
			break;
		}
		auto it = _manager->getComponent<Gun>(fighter)->begin();
		auto it_end = _manager->getComponent<Gun>(fighter)->end();
		while (it != it_end) {
			// Si hay colisión entre asteroide y bala
			if (it->used && Collisions::collidesWithRotation(
				it->pos, it->width, it->height, it->rot,
				aTr->getPos(), aTr->getWidth(), aTr->getHeight(), aTr->getRot()))
			{
				_game->getAsteroidsUtils()->split_astroid(asteroids.at(i));
				it->used = false;
			}
			++it;
		}
	}
}

