#include"ShowAtOppositeSide.h"
#include"Container.h"
#include "../sdlutils/SDLUtils.h"

void ShowAtOppositeSide::update(Container* o) {
	if (o->getPos().getX() >= sdlutils().width() + o->getWidth()) o->getPos().setX(0);
	else if (o->getPos().getX() <= -o->getWidth()) o->getPos().setX(sdlutils().width());

	if (o->getPos().getY() >= sdlutils().height() + o->getHeight()) o->getPos().setY(0);
	else if (o->getPos().getY() <= -o->getHeight()) o->getPos().setY(sdlutils().height());
}