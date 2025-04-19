#include "NewRoundState.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"
#include "messages_defs.h"
#include "Game.h"

NewRoundState::NewRoundState(Game* game) : GameState(game) 
{
	_inputHandler = InputHandler::Instance();
}

NewRoundState::~NewRoundState() {

}

void 
NewRoundState::update() {
	SDL_Rect dest = { sdlutils().width() / 2 - 250, sdlutils().height() / 2 - 25, 500, 50 };

	sdlutils().clearRenderer();
	sdlutils().msgs().at("newround").render(dest);
	sdlutils().presentRenderer();

	if (_inputHandler->isKeyDown(SDLK_SPACE)) {
		auto manager = _game->getManager();
		Message m;
		m.id = msgId::_m_ROUND_START;
		manager->send(m);
	}
}