#pragma once

#include "PhysicsComponent.h"
class ShowAtOppositeSide : public PhysicsComponent {
public:
	ShowAtOppositeSide() : PhysicsComponent() {}
	void update(Container* o) override;
};