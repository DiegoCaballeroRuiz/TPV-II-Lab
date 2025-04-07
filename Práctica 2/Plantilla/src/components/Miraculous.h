#pragma once 

#include "../ecs/Component.h"

struct Miraculous : public ecs::Component {
	enum State {
		NORMAL,
		MIRACULOUS
	};

	Miraculous(int n) : _state(NORMAL), N(n) {}
	Miraculous(State state, int n) : _state(state), N(n) {}
	~Miraculous() {}

	State _state;
	int N, M, T;
};