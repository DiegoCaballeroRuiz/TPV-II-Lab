#pragma once

#include "GameState.h"

class InputHandler;
class NewGameState : public GameState {
	Game* _game;
	InputHandler* _inputHandler;
public:
	NewGameState(Game* game);
	~NewGameState();
	void enter() override;
	void leave() override;
	void update() override;
};