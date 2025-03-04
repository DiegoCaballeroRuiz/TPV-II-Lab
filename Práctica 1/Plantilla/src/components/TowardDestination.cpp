#include "TowardDestination.h"

#include "Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/RandomNumberGenerator.h"

TowardDestination::TowardDestination() : Component() 
{
	getRandomDestination();
}

void
TowardDestination::initComponent() {
	_transform = _ent->getMngr()->getComponent<Transform>(_ent);
}

void 
TowardDestination::update() {
	Vector2D distance = _destination - _transform->getPos();
	_transform->getVel().rotate(_transform->getVel().angle(distance));
	if (distance.magnitude() <= 10.0f) getRandomDestination();
}

void 
TowardDestination::getRandomDestination() {
	int x = sdlutils().rand().nextInt(0, sdlutils().width());
	int y = sdlutils().rand().nextInt(0, sdlutils().height());
	_destination = Vector2D(x, y);
}



