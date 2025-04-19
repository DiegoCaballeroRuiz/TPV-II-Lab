#pragma once 

#include "GameState.h"

class NewRoundState : public GameState {
public: 
	NewRoundState(Game* game);
	~NewRoundState();
	void enter() override {}
	void leave() override {}
	void update() override;
};