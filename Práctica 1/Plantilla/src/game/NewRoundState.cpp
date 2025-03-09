#include "NewRoundState.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "FighterUtils.h"
#include "AsteroidsUtils.h"
#include "Game.h"

NewRoundState::NewRoundState(Game* game) : GameState(game) 
{
	_inputHandler = InputHandler::Instance();
}

NewRoundState::~NewRoundState() {

}

void 
NewRoundState::update() {
	SDL_Rect dest = { sdlutils().width() / 2 - 250, sdlutils().height() / 2, 500, 50 };

	sdlutils().clearRenderer();
	sdlutils().msgs().at("newround").render(dest);
	sdlutils().presentRenderer();

	if (_inputHandler->isKeyDown(SDLK_SPACE)) {
		_game->getFightersUtils()->reset_fighter();

		_game->getAsteroidsUtils()->remove_all_asteroids();
		_game->getAsteroidsUtils()->create_asteroids(10);

		_game->setState(Game::RUNNING);
	}
}