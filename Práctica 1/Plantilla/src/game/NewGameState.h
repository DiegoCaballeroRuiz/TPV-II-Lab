#pragma once

#include "GameState.h"

class NewGameState : public GameState {
public:
	NewGameState(Game* game);
	~NewGameState();
	void enter() override {}
	void leave() override {}
	void update() override;
};