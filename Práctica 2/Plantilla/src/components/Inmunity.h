#pragma once 

#include "../ecs/Component.h"

struct Immunity : public ecs::Component {
	Immunity() : _inmune(false), _immunityEnd(0U) {}
	Immunity(bool inmune, std::uint32_t timeToStop) : _inmune(inmune), _immunityEnd(timeToStop) {}

	~Immunity() {}

	bool _inmune;
	std::uint32_t _immunityEnd;
};