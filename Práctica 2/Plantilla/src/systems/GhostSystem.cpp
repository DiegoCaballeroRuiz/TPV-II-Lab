#include "GhostSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"

GhostSystem::GhostSystem() : _spawnDelay(5000.0f), _ghostGroup(ecs::grp::GHOSTS), _ghostSpeed(1.1f),
_spawnPoints({
	Vector2D(0, 0),
	Vector2D(sdlutils().width(), 0),
	Vector2D(0, sdlutils().height()),
	Vector2D(sdlutils().width(), sdlutils().height())
	})
{
}

GhostSystem::~GhostSystem() {}

void 
GhostSystem::initSystem() {
	_lastGhostSpawnTime = sdlutils().virtualTimer().currTime();
}

void 
GhostSystem::update() {

	auto ghosts = _manager->getEntities(_ghostGroup);
	auto pacManTransform = _manager->getComponent<Transform>(_manager->getHandler(ecs::hdlr::PACMAN));
	//Intentar spawnear fantasma
	if (ghosts.size() < 10 && sdlutils().virtualTimer().currTime() >= _lastGhostSpawnTime + _spawnDelay) {
		ecs::entity_t ghost = new ecs::Entity(_ghostGroup);

		float scale = 25.0f;
		Vector2D pos = _spawnPoints[sdlutils().rand().nextInt(0, 5)];
		Vector2D velocity = (pos - pacManTransform->_pos);
		_manager->addComponent<Transform>(ghost, pos, velocity, scale, scale, 0);

		_lastGhostSpawnTime = sdlutils().virtualTimer().currTime();
	}

	for (auto ghost : ghosts) {
		//Intentar cambiar direccion

		//Mover

	}

}

void 
GhostSystem::recieve(const Message& msg) {

}