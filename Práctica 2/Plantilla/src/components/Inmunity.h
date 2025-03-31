#pragma once 

#include "../ecs/Component.h"

struct Inmunity : public ecs::Component {
	Inmunity() : _inmune(false) {}
	Inmunity(bool inmune) : _inmune(inmune) {}

	~Inmunity() {}

	bool _inmune;
};