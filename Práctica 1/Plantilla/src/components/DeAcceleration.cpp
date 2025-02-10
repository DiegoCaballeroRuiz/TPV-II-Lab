#include "DeAcceleration.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"

void DeAcceleration::initComponent() {
	_transform = _ent->getMngr()->getComponent<Transform>(_ent);
}

void DeAcceleration::update() {
	_transform->getVel().set(_transform->getVel() * 0.995f);
	if (_transform->getVel().magnitude() < 0.05f) _transform->getVel().set({0.0f, 0.0f});
}