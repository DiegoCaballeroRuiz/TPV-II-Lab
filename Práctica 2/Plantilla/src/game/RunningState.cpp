#include "RunningState.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"
#include "Game.h"
#include "../utils/Collisions.h"
#include "../components/Transform.h"
#include "../components/Health.h"

RunningState::RunningState(Game* game) : GameState(game), _lastTimeAstroidAdded(0)
{
	_inputHandler = InputHandler::Instance();
}

void
RunningState::update() {
	auto manager = _game->getManager();
	auto fruits = manager->getEntities(ecs::grp::FRUITS);

	if (fruits.size() == 0) {
		Message m;
		m.id = msgId::_m_GAME_OVER;
		manager->send(m);
	}

	if (_inputHandler->isKeyDown(SDLK_p))
		_game->setState(Game::PAUSED);

	//Objetos de juego
	_game->getPacManSys()->update();
	_game->getFruitSys()->update();
	_game->getGhostSys()->update();

	//Colisiones
	_game->getCollisionSys()->update();
}

