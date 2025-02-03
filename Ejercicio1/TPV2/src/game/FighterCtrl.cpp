#include "FighterCtrl.h"
#include "../sdlutils/InputHandler.h"
#include"Container.h"

void FighterCtrl::handleInput(Container* o) {
	auto& inputHandler = *InputHandler::Instance();

	if (inputHandler.isKeyDown(SDLK_RIGHT)) 
		o->setRotation(o->getRotation() + _rotationDegrees);
	else if(inputHandler.isKeyDown(SDLK_LEFT))
		o->setRotation(o->getRotation() - _rotationDegrees);
	
	if (inputHandler.isKeyDown(SDLK_UP)) {
		Vector2D velocity = o->getVel() + Vector2D(0, -1).rotate(o->getRotation()) * _thrust;

		if (velocity.magnitude() > _speedLimit)velocity = velocity.normalize() * _speedLimit;

		o->getVel().set(velocity);
	}
}