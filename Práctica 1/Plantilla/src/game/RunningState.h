#pragma once

#include "GameState.h"

namespace ecs {
	class Manager;
	class Entity;
}
class RunningState : public GameState {
	ecs::Manager* _manager;
	float _lastTimeAstroidAdded;
	void checkCollisions();
public:
	RunningState(Game* game, ecs::Manager* manager);
	~RunningState() {}

	void enter() override {}
	void leave() override {}
	void update() override;
};