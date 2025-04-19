// This file is part of the course TPV2@UCM - Samir Genaim

#include "BallSystem.h"

#include "../components/Image.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "NetworkSystem.h"

BallSystem::BallSystem() :
		_ballTr(nullptr) {
}

BallSystem::~BallSystem() {
}

void BallSystem::initSystem() {
	// create the ball entity
	//
	auto ball = _mngr->addEntity();
	_mngr->setHandler(ecs::hdlr::_hdlr_BALL, ball);

	_ballTr = _mngr->addComponent<Transform>(ball);
	auto ballSize = 15.0f;
	auto ballX = (sdlutils().width() - ballSize) / 2.0f;
	auto ballY = (sdlutils().height() - ballSize) / 2.0f;
	_ballTr->init(Vector2D(ballX, ballY), Vector2D(), ballSize, ballSize, 0.0f);

	_mngr->addComponent<Image>(ball, &sdlutils().images().at("tennis_ball"));
}

void BallSystem::update() {

	_ballTr->move();

	// check upper/lower borders
	if (_ballTr->_pos.getY() < 0) {
		_ballTr->_pos.setY(0.0f);
		_ballTr->_vel.setY(-_ballTr->_vel.getY());
		// play some sound
		sdlutils().soundEffects().at("wall_hit").play();
	} else if (_ballTr->_pos.getY() + _ballTr->_width > sdlutils().height()) {
		_ballTr->_pos.setY(sdlutils().height() - _ballTr->_height);
		_ballTr->_vel.setY(-_ballTr->_vel.getY());
		sdlutils().soundEffects().at("wall_hit").play();
	}

//	_mngr->getSystem<NetworkSystem>()->sendBallPosition(ballTr_);
}

void BallSystem::resetBall() {
	_ballTr->_pos.set(sdlutils().width() / 2 - 5, sdlutils().height() / 2 - 5);
	_ballTr->_vel.set(0, 0);
	_mngr->getSystem<NetworkSystem>()->sendBallPosition(_ballTr);
	_mngr->getSystem<NetworkSystem>()->sendBallVelocity(_ballTr);
}

void BallSystem::changeBallPos(float x, float y) {
	_ballTr->_pos.set(x, y);
}

void BallSystem::changeBallVel(float x, float y) {
	std::cout << x << " " << y << std::endl;
	_ballTr->_vel.set(x, y);
}

void BallSystem::moveBall() {
	auto &r = sdlutils().rand();

	int dx = 1 - 2 * r.nextInt(0, 2); // 1 or -1
	int dy = 1 - 2 * r.nextInt(0, 2); // 1 or -1

	Vector2D v(dx * r.nextInt(2, 7), dy * r.nextInt(2, 7));
	_ballTr->_vel.set(v.normalize() * 2);
	_mngr->getSystem<NetworkSystem>()->sendBallVelocity(_ballTr);
}

void BallSystem::recieve(const Message &m) {
	if (!_mngr->getSystem<NetworkSystem>()->isHost())
		return;

	switch (m.id) {
	case _m_ROUND_START:
		moveBall();
		break;
	case _m_NEW_GAME:
	case _m_ROUND_OVER:
		resetBall();
		break;
	default:
		break;
	}
}
