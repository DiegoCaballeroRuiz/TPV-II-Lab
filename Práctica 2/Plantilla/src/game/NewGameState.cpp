#include "NewGameState.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"
#include "messages_defs.h"
#include "Game.h"
#include "../sdlutils/Texture.h"

NewGameState::NewGameState(Game* game) : GameState(game)
{
	_inputHandler = InputHandler::Instance();
}

NewGameState::~NewGameState() {}

void 
NewGameState::update() {
	SDL_Rect dest = { sdlutils().width() / 2 - 250, sdlutils().height() / 2 - 25, 500, 50 };

	sdlutils().clearRenderer();
	sdlutils().msgs().at("PressAnyKey").render(dest);
	sdlutils().presentRenderer();

	if (_inputHandler->keyDownEvent()) {
		auto manager = _game->getManager();
		Message m;
		m.id = msgId::_m_NEW_ROUND;
		manager->send(m);
	}
}