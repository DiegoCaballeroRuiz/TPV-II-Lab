#include "FighterCtrl.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"

void FighterCtrl::initComponent() {
	_transform = _ent->getMngr()->getComponent<Transform>(_ent);
}

void FighterCtrl::update() {
	auto& inputHandler = *InputHandler::Instance();

	if (inputHandler.isKeyDown(SDLK_RIGHT)) 
		_transform->setRot(_transform->getRot() + _rotationDegrees);
	else if(inputHandler.isKeyDown(SDLK_LEFT))
		_transform->setRot(_transform->getRot() - _rotationDegrees);
	
	if (inputHandler.isKeyDown(SDLK_UP)) {
		Vector2D velocity = _transform->getVel() + Vector2D(0, -1).rotate(_transform->getRot()) * _thrust;

		if (velocity.magnitude() > _speedLimit)velocity = velocity.normalize() * _speedLimit;

		_transform->getVel().set(velocity);
	}
}