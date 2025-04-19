// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionsSystem.h"

#include "../components/Transform.h"
#include "../ecs/messages.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "GameCtrlSystem.h"
#include "NetworkSystem.h"
CollisionsSystem::CollisionsSystem() :
		_ballTr(nullptr), _active(false) {
}

CollisionsSystem::~CollisionsSystem() {
}

void CollisionsSystem::initSystem() {
	_ballTr = _mngr->getComponent<Transform>(
			_mngr->getHandler(ecs::hdlr::_hdlr_BALL));
	assert(_ballTr != nullptr);
}

void CollisionsSystem::update() {

	if (!_mngr->getSystem<NetworkSystem>()->isHost())
		return;

	if (!_active)
		return;

	bool ballCollidesWithPaddle = false;

	for (auto e : _mngr->getEntities(ecs::grp::_grp_PADDLES)) {
		auto paddleTr_ = _mngr->getComponent<Transform>(e);
		ballCollidesWithPaddle = Collisions::collides(paddleTr_->_pos,
				paddleTr_->_width, paddleTr_->_height, _ballTr->_pos,
				_ballTr->_width, _ballTr->_height);

		if (ballCollidesWithPaddle)
			break;
	}

	if (ballCollidesWithPaddle) {

		// change the direction of the ball, and increment the speed
		auto &vel = _ballTr->_vel; // the use of & is important, so the changes goes directly to the ball
		vel.setX(-vel.getX());
		vel = vel * 1.2f;

		_mngr->getSystem<NetworkSystem>()->sendBallVelocity(_ballTr);
		// play some sound
		sdlutils().soundEffects().at("paddle_hit").play();
	} else if (_ballTr->_pos.getX() < 0) {
		Message m;
		m.id = _m_BALL_EXIT;
		m.ball_exit.side = GameCtrlSystem::LEFT;
		_mngr->send(m);
	} else if (_ballTr->_pos.getX() + _ballTr->_width > sdlutils().width()) {
		Message m;
		m.id = _m_BALL_EXIT;
		m.ball_exit.side = GameCtrlSystem::RIGHT;
		_mngr->send(m);
	}
}

void CollisionsSystem::recieve(const Message &m) {
	switch (m.id) {
	case _m_ROUND_START:
		_active = true;
		break;
	case _m_NEW_GAME:
	case _m_ROUND_OVER:
		_active = false;
		break;
	default:
		break;
	}
}
