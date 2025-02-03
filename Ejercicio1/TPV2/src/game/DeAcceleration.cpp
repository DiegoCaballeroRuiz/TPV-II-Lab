#include "DeAcceleration.h"

#include "Container.h"

void DeAcceleration::update(Container* o) {
	o->getVel().set(o->getVel() * 0.995f);
}