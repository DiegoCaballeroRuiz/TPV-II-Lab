#include "StateChangeSystem.h"
#include "../ecs/Manager.h"
#include "../components/Health.h"

void 
StateChangeSystem::recieve(const Message& m) {
	
	switch (m.id) {

	case msgId::_m_NEW_GAME:
		_game->setState(Game::NEWGAME);
		break;

	case msgId::_m_ROUND_START:
		_game->setState(Game::RUNNING);
		break;

	case msgId::_m_ROUND_OVER:
		Message m;

		if (_manager->getComponent<Health>(_manager->getHandler(ecs::hdlr::PACMAN))->lives <= 0
			|| _manager->getEntities(ecs::grp::FRUITS).size() == 0)
		{
			m.id = msgId::_m_GAME_OVER;
		}
		else m.id = msgId::_m_ROUND_START;

		_manager->send(m);
		break;

	case msgId::_m_GAME_OVER:
		_game->setState(Game::GAMEOVER);
		break;

	case msgId::_m_NEW_ROUND:
		_game->setState(Game::NEWROUND);
		break;
	}
}