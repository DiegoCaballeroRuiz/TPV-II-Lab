#include "FighterCtrl.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SoundEffect.h"

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"

FighterCtrl::FighterCtrl() : Component(), _rotationDegrees(5.0f), _thrust(0.2), _speedLimit(3.0f), _transform(nullptr)
{
	//_thrustSound = new SoundEffect("thrust.wav");
}

FighterCtrl::~FighterCtrl() {
	if (_transform != nullptr) {
		_transform = nullptr;
	}

	//delete _thrustSound;
	//_thrustSound = nullptr;
}

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
		//_thrustSound->play();
		Vector2D velocity = _transform->getVel() + Vector2D(0, -1).rotate(_transform->getRot()) * _thrust;

		if (velocity.magnitude() > _speedLimit)velocity = velocity.normalize() * _speedLimit;

		_transform->getVel().set(velocity);
	}
}