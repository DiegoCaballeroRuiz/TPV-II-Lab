#include "FruitSystem.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/macros.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/Miraculous.h"

FruitSystem::FruitSystem() 
	: System(), _grid(), _fruitGroup(ecs::grp::FRUITS)
{
	initGrid();
}

FruitSystem::~FruitSystem() {

}

void 
FruitSystem::initGrid() {
	for (int i = 0; i < N_ROWS; ++i) 
		for (int j = 0; j < N_COLUMNS; ++j) 
			_grid.push_back(Vector2D((sdlutils().width() / N_COLUMNS) * j, 
									 (sdlutils().height() / N_ROWS) * i));
}

void
FruitSystem::initSystem() {
	int nFruits = N_ROWS * N_COLUMNS;

	auto fruits = _manager->getEntities(_fruitGroup);

	//Crear las frutas
	for (int i = 0; i < nFruits; ++i) {
		ecs::entity_t fruit = new ecs::Entity(_fruitGroup);

		//Transform
		auto transform = _manager->addComponent<Transform>(fruit);
		float scale = 25.0f;
		float x = _grid[i].getX() - scale;
		float y = _grid[i].getY() - scale;

		transform->init(Vector2D(x, y), Vector2D(), scale, scale, 0.0f);

		//Image
		_manager->addComponent<Image>(fruit, sdlutils().images().at("spritesheet"));

		//Miraculous
		if (sdlutils().rand().nextInt(1, 101) <= 10) {
			auto miraculous = _manager->addComponent<Miraculous>(fruit);
			miraculous->_state = Miraculous::NORMAL;
			miraculous->N = sdlutils().rand().nextInt(10, 21);
		}
	}
}

void 
FruitSystem::update() {

}

void 
FruitSystem::recieve(const Message& msg) {

}