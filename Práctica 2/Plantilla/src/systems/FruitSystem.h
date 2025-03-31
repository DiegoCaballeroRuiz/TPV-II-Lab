#pragma once 

#include "../ecs/System.h"
#include "../utils/Vector2D.h"
#include <vector>

class FruitSystem : public ecs::System {
	ecs::grpId_t _fruitGroup;
	std::vector<Vector2D> _grid;
public:
	FruitSystem();
	virtual ~FruitSystem();

	void initSystem() override;
	void update() override;
	void recieve(const Message& msg) override;
};