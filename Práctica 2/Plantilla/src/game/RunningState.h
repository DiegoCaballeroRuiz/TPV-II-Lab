#pragma once

#include "GameState.h"

namespace ecs {
	class Manager;
	class Entity;
}
class RunningState : public GameState {
	ecs::Manager* _manager;
	float _lastTimeAstroidAdded;
public:
	RunningState(Game* game);
	~RunningState() {}

	void enter() override {}
	void leave() override {}
	void update() override;
};