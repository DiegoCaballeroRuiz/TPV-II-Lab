#include "FruitSystem.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/macros.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/Miraculous.h"
#include "../components/TextureSrc.h"

FruitSystem::FruitSystem() 
	: System(), _grid(), _fruitGroup(ecs::grp::FRUITS)
{
	initGrid();
	_cherrySrcRect = build_sdlrect(128 * 4, 128, 128, 128);
	_pearSrcRect = build_sdlrect(128 * 7, 128, 128, 128);
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

}

void 
FruitSystem::createFruits() {
	int nFruits = N_ROWS * N_COLUMNS;

	auto fruits = _manager->getEntities(_fruitGroup);

	//Crear las frutas
	for (int i = 0; i < nFruits; ++i) {
		ecs::entity_t fruit = _manager->addEntity(_fruitGroup);

		//Transform
		auto transform = _manager->addComponent<Transform>(fruit);
		float scale = 25.0f;

		float x = _grid[i].getX() + scale/2;
		float y = _grid[i].getY() + scale/2;

		transform->init(Vector2D(x, y), Vector2D(), scale, scale, 0.0f);

		//Image
		_manager->addComponent<Image>(fruit, &sdlutils().images().at("spritesheet"));

		//TextureSrc
		_manager->addComponent<TextureSrc>(fruit, _cherrySrcRect);

		//Miraculous
		if (sdlutils().rand().nextInt(1, 101) <= 10)
			_manager->addComponent<Miraculous>(fruit, Miraculous::NORMAL, sdlutils().rand().nextInt(10, 21));
	}
}

void 
FruitSystem::update() {
	auto fruits = _manager->getEntities(_fruitGroup);

	std::cout << fruits.size() << "\n";

	if (fruits.size() == 0) {
		Message m; 
		m.id = msgId::_m_ROUND_OVER;
		_manager->send(m);
	}

	for (auto fruit : fruits) {
		if (_manager->hasComponent<Miraculous>(fruit)) {
			Miraculous* miraculous = _manager->getComponent<Miraculous>(fruit);

			if (miraculous->_state == Miraculous::MIRACULOUS 
				&& sdlutils().virtualTimer().currTime() - miraculous->T > miraculous->M * 1000) {
				
				miraculous->_state = Miraculous::NORMAL;
				miraculous->T = sdlutils().virtualTimer().currTime();

				auto src = _manager->getComponent<TextureSrc>(fruit);
				src->_src = _cherrySrcRect;
			}
			else if (miraculous->_state == Miraculous::NORMAL
				&& sdlutils().virtualTimer().currTime() - miraculous->T > miraculous->N * 1000) {

				miraculous->_state = Miraculous::MIRACULOUS;
				miraculous->T = sdlutils().virtualTimer().currTime();
				miraculous->M = sdlutils().rand().nextInt(1, 6);

				auto src = _manager->getComponent<TextureSrc>(fruit);
				src->_src = _pearSrcRect;
			}
		}
	}
}

void 
FruitSystem::recieve(const Message& msg) {
	if (msg.id == msgId::_m_NEW_GAME) {
		auto fruits = _manager->getEntities(_fruitGroup);

		for (auto fruit : fruits)
			_manager->setAlive(fruit, false);

		createFruits();
	}

	else if (msg.id == msgId::_m_ROUND_START) {
		auto fruits = _manager->getEntities(_fruitGroup);
		for (auto fruit : fruits) {
			if (_manager->hasComponent<Miraculous>(fruit)) {
				Miraculous* miraculous = _manager->getComponent<Miraculous>(fruit);
				miraculous->T = sdlutils().virtualTimer().currTime();
			}
		}
	}
}