#include "GhostSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/TextureSrc.h"

GhostSystem::GhostSystem() : _spawnDelay(5000.0f), _ghostGroup(ecs::grp::GHOSTS), _ghostSpeed(1.1f), _canSpawn(true),
_spawnPoints({
	Vector2D(0, 0),
	Vector2D(sdlutils().width(), 0),
	Vector2D(0, sdlutils().height()),
	Vector2D(sdlutils().width(), sdlutils().height())
	})
{
	_defaultSrcRect = build_sdlrect(128 * 5, 128 * 5, 128, 128);
	_blueSrcRect = build_sdlrect(128 * 6, 128 * 3, 128, 128);
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
	if (_canSpawn && ghosts.size() < 10 && sdlutils().virtualTimer().currTime() >= _lastGhostSpawnTime + _spawnDelay) {
		ecs::entity_t ghost = new ecs::Entity(_ghostGroup);

		float scale = 25.0f;
		Vector2D pos = _spawnPoints[sdlutils().rand().nextInt(0, 5)];
		Vector2D velocity = (pos - pacManTransform->_pos);
		_manager->addComponent<Transform>(ghost, pos, velocity, scale, scale, 0);

		_lastGhostSpawnTime = sdlutils().virtualTimer().currTime();
	}

	for (auto ghost : ghosts) {
		auto transform = _manager->getComponent<Transform>(ghost);

		//Intentar cambiar direccion
		int chance = sdlutils().rand().nextInt(0, 1001);
		if (chance <= 5) transform->_vel = (transform->_pos - pacManTransform->_pos);
		
		//Comprobar bordes
		if (transform->_pos.getX() < 0 && transform->_vel.getX() < 0
			|| transform->_pos.getX() > sdlutils().width() && transform->_vel.getX() > 0) 
		{
			transform->_vel.setX(-transform->_vel.getX());
		}

		if (transform->_pos.getY() < 0 && transform->_vel.getY() < 0
			|| transform->_pos.getY() > sdlutils().height() && transform->_vel.getY() > 0)
		{
			transform->_vel.setY(-transform->_vel.getY());
		}

		//Mover
		transform->_pos = transform->_pos + transform->_vel;
	}
}

void 
GhostSystem::recieve(const Message& msg) {
	if (msg.id == msgId::_m_ROUND_START) {
		
		_lastGhostSpawnTime = sdlutils().virtualTimer().currTime();
	}

	else if (msg.id == msgId::_m_ROUND_OVER) {
		auto ghosts = _manager->getEntities(_ghostGroup);
		for (auto ghost : ghosts) delete ghost;
		ghosts.clear();
	}

	else if (msg.id == msgId::_m_IMMUNITY_START) {
		auto ghosts = _manager->getEntities(_ghostGroup);
		for (auto ghost : ghosts) {
			auto texSrc = _manager->getComponent<TextureSrc>(ghost);
			texSrc->_src = _blueSrcRect;
		}
		_canSpawn = false;
	}

	else if (msg.id == msgId::_m_IMMUNITY_END) {
		auto ghosts = _manager->getEntities(_ghostGroup);
		for (auto ghost : ghosts) {
			auto texSrc = _manager->getComponent<TextureSrc>(ghost);
			texSrc->_src = _defaultSrcRect;
		}
		_canSpawn = true;
	}
}