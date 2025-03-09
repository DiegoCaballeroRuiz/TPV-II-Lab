#include "PausedState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/VirtualTimer.h"
#include "Game.h"

PausedState::PausedState(Game* game) : GameState(game) 
{
	_inputHandler = InputHandler::Instance();
}

PausedState::~PausedState() {

}

void 
PausedState::enter() {
	sdlutils().virtualTimer().pause();
}

void 
PausedState::leave() {
	sdlutils().virtualTimer().resume();
}

void 
PausedState::update() {
	SDL_Rect dest = { sdlutils().width() / 2, sdlutils().height() / 2, 100, 20 };

	sdlutils().clearRenderer();
	sdlutils().msgs().at("paused").render(dest);
	sdlutils().presentRenderer();

	if (_inputHandler->keyDownEvent()) {
		_game->setState(Game::RUNNING);
	}
}