#include "NewGameState.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"
#include "FighterUtils.h"
#include "../sdlutils/Texture.h"

NewGameState::NewGameState(Game* game) : GameState(game) 
{
	_inputHandler = InputHandler::Instance();
}

void 
NewGameState::update() {
	SDL_Rect dest = { sdlutils().width() / 2, sdlutils().height() / 2, 100, 20 };
	sdlutils().msgs().at("PressAnyKey").render(dest);

	if (_inputHandler->keyDownEvent()) {
		_game->getFightersUtils()->reset_lives();
		_game->setState(Game::NEWROUND);
	}
}