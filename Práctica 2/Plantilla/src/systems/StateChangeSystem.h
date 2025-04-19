#pragma once

#include "../ecs/System.h"
#include "../game/Game.h"

class StateChangeSystem : public ecs::System {

	Game* _game;

public:
	
	StateChangeSystem(Game* game) : System(), _game(game) {}
	~StateChangeSystem() {}

	void recieve(const Message&) override;
};