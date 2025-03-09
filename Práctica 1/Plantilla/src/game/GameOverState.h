#pragma once

#include "GameState.h"
#include <string>

class GameOverState : public GameState {
	std::string _message;
public:
	GameOverState(Game* game);
	~GameOverState() {}

	void enter() override;
	void leave() override {}
	void update() override;
};