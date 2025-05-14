#pragma once 

#include "../ecs/Component.h"

struct Miraculous : public ecs::Component {
	enum State {
		NORMAL,
		MIRACULOUS
	};

	Miraculous(std::uint32_t n) : _state(NORMAL), N(n) {}
	Miraculous(State state, std::uint32_t n) : _state(state), N(n) {}
	~Miraculous() {}

	State _state;
	std::uint32_t N, M, T;
};