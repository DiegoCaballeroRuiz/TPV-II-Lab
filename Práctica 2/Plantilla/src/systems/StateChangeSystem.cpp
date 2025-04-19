#include "StateChangeSystem.h"
#include "../ecs/Manager.h"
#include "../components/Health.h"

void 
StateChangeSystem::recieve(const Message& m) {
	
	if (m.id == msgId::_m_NEW_GAME) {
		_game->setState(Game::NEWGAME);
	}

	else if (m.id == msgId::_m_ROUND_START) {
		_game->setState(Game::RUNNING);
	}

	else if (m.id == msgId::_m_ROUND_OVER) {
		auto pacman = _manager->getHandler(ecs::hdlr::PACMAN);
		auto fruits = _manager->getEntities(ecs::grp::FRUITS);

		Message m;
		if (_manager->getComponent<Health>(pacman)->lives <= 0 || fruits.size() == 0) m.id = msgId::_m_GAME_OVER;
		else m.id = msgId::_m_ROUND_START;

		_manager->send(m);
	}

	else if (m.id == msgId::_m_GAME_OVER) {
		_game->setState(Game::GAMEOVER);
	}

	else if (m.id == msgId::_m_NEW_ROUND) {
		_game->setState(Game::NEWROUND);
	}
}