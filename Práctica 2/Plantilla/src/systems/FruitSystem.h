#pragma once 

#include "../ecs/System.h"
#include "../utils/Vector2D.h"
#include <SDL.h>
#include <vector>

class FruitSystem : public ecs::System {
	ecs::grpId_t _fruitGroup;
	std::vector<Vector2D> _grid;
	
	const int N_ROWS = 6, N_COLUMNS = 8;

	void initGrid();
	void createFruits();

	SDL_Rect _cherrySrcRect, _pearSrcRect;
public:
	FruitSystem();
	virtual ~FruitSystem();

	void initSystem() override;
	void update() override;
	void recieve(const Message& msg) override;
};