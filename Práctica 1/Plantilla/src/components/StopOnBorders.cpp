// This file is part of the course TPV2@UCM - Samir Genaim

#include "StopOnBorders.h"

#include <cassert>

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

StopOnBorders::StopOnBorders() :
		_tr() {
}

StopOnBorders::~StopOnBorders() {
}

void StopOnBorders::initComponent() {
	auto *mngr = _ent->getMngr();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
}

void StopOnBorders::update() {
	auto &pos = _tr->getPos();
	auto &vel = _tr->getVel();

	// check left/right borders
	if (pos.getX() < 0) {
		pos.setX(0.0f);
		vel.set(0.0f, 0.0f);
	} else if (pos.getX() + _tr->getWidth() > sdlutils().width()) {
		pos.setX(sdlutils().width() - _tr->getWidth());
		vel.set(0.0f, 0.0f);
	}

	// check upper/lower borders
	if (pos.getY() < 0) {
		pos.setY(0.0f);
		vel.set(0.0f, 0.0f);
	} else if (pos.getY() + _tr->getHeight() > sdlutils().height()) {
		pos.setY(sdlutils().height() - _tr->getHeight());
		vel.set(0.0f, 0.0f);
	}
}
