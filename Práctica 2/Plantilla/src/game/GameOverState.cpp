#include "GameOverState.h"

#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "messages_defs.h"

GameOverState::GameOverState(Game* game) : GameState(game) {
	_inputHandler = InputHandler::Instance();
}

void 
GameOverState::enter() {
	auto manager = _game->getManager();
	_message = (manager->getEntities(ecs::grp::FRUITS).size() == 0)
		? "gameoverW"
		: "gameoverL";
}

void GameOverState::update() {
	SDL_Rect dest = { sdlutils().width() / 2 - 250, sdlutils().height() / 2 - 50, 500, 100 };

	sdlutils().clearRenderer();
	sdlutils().msgs().at(_message).render(dest);
	sdlutils().presentRenderer();

	if (_inputHandler->isKeyDown(SDLK_SPACE)) {
		auto manager = _game->getManager();
		Message m;
		m.id = msgId::_m_NEW_GAME;
		manager->send(m);
	}
}