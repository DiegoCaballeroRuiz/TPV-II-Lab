#pragma once

#include "PhysicsComponent.h"

class DeAcceleration : public PhysicsComponent {
public:
	DeAcceleration() : PhysicsComponent() {}
	void update(Container* o) override;
};