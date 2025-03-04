#include "Follow.h"

#include "Transform.h"
#include "../ecs/Manager.h"

Follow::Follow(Transform* target) : Component(), _target(target), _mTransform(nullptr)
{

}

void
Follow::initComponent() {
	_mTransform = _ent->getMngr()->getComponent<Transform>(_ent);
	_mTransform->getVel() = { 1.0f, 0.0f };
}

void 
Follow::update() {
	_mTransform->getVel().rotate(_mTransform->getVel().angle(_target->getPos() - _mTransform->getPos()) > 0
		? 1.0f
		: -1.0f);
}