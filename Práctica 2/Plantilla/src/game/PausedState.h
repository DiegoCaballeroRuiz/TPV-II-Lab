#pragma once 

#include "GameState.h"

class PausedState : public GameState {
public:
	PausedState(Game* game);
	~PausedState();
	void enter() override;
	void leave() override;
	void update() override;
};