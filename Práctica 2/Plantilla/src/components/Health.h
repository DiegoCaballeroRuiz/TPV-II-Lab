#pragma once

#include "../ecs/Component.h"

struct Health : public ecs::Component {
	int lives;
	int maxLives;

	Health() : maxLives(3), lives(3) {}

	Health(int maxLives) : maxLives(maxLives), lives(maxLives) {}
};