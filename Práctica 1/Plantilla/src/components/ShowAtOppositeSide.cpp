#include"ShowAtOppositeSide.h"
#include"../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

void ShowAtOppositeSide::initComponent() {
	_transform = _ent->getMngr()->getComponent<Transform>(_ent);
}

void ShowAtOppositeSide::update() {
	if (_transform->getPos().getX() >= sdlutils().width() + _transform->getWidth()) _transform->getPos().setX(0);
	else if (_transform->getPos().getX() <= -_transform->getWidth()) _transform->getPos().setX(sdlutils().width());

	if (_transform->getPos().getY() >= sdlutils().height() + _transform->getHeight()) _transform->getPos().setY(0);
	else if (_transform->getPos().getY() <= -_transform->getHeight()) _transform->getPos().setY(sdlutils().height());
}