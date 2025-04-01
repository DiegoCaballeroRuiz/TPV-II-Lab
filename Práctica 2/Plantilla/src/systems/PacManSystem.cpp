// This file is part of the course TPV2@UCM - Samir Genaim

#include "PacManSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Health.h"
#include "../components/Miraculous.h"
#include "../components/Inmunity.h"

PacManSystem::PacManSystem() :
		_pacManTransform(nullptr) {
}

PacManSystem::~PacManSystem() {
}

void PacManSystem::initSystem() {
	// create the PacMan entity
	auto pacman = _manager->addEntity();
	_manager->setHandler(ecs::hdlr::PACMAN, pacman);

	_pacManTransform = _manager->addComponent<Transform>(pacman);
	float scale = 50.0f;
	float x = (sdlutils().width() - scale) / 2.0f;
	float y = (sdlutils().height() - scale) / 2.0f;
	_pacManTransform->init(Vector2D(x, y), Vector2D(), scale, scale, 0.0f);

	_manager->addComponent<Image>(pacman, &sdlutils().images().at("pacman"));
	_manager->addComponent<Health>(pacman);
	_manager->addComponent<Inmunity>(pacman);
}

void PacManSystem::update() {

	auto &ihldr = ih();

	if (ihldr.keyDownEvent()) {

		if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // rotate right
			_pacManTransform->_rot = _pacManTransform->_rot + 90.0f;
			_pacManTransform->_vel = _pacManTransform->_vel.rotate(+90.0f);
		} else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // rotate left
			_pacManTransform->_rot = _pacManTransform->_rot - 90.0f;
			_pacManTransform->_vel = _pacManTransform->_vel.rotate(-90.0f);
		} 
		else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) _pacManTransform->_vel = Vector2D(0, -3.0f).rotate(_pacManTransform->_rot);
		else if (ihldr.isKeyDown(SDL_SCANCODE_DOWN)) _pacManTransform->_vel = Vector2D(0, 0).rotate(_pacManTransform->_rot);
	}

	// move the pacman
	_pacManTransform->_pos = _pacManTransform->_pos + _pacManTransform->_vel;

	// check left/right borders
	if (_pacManTransform->_pos.getX() < 0) {
		_pacManTransform->_pos.setX(0.0f);
		_pacManTransform->_vel.set(0.0f, 0.0f);
	} else if (_pacManTransform->_pos.getX() + _pacManTransform->_width > sdlutils().width()) {
		_pacManTransform->_pos.setX(sdlutils().width() - _pacManTransform->_width);
		_pacManTransform->_vel.set(0.0f, 0.0f);
	}

	// check upper/lower borders
	if (_pacManTransform->_pos.getY() < 0) {
		_pacManTransform->_pos.setY(0.0f);
		_pacManTransform->_vel.set(0.0f, 0.0f);
	} else if (_pacManTransform->_pos.getY() + _pacManTransform->_height > sdlutils().height()) {
		_pacManTransform->_pos.setY(sdlutils().height() - _pacManTransform->_height);
		_pacManTransform->_vel.set(0.0f, 0.0f);
	}
}

void 
PacManSystem::recieve(const Message& msg) {
	if (msg.id == msgId::_m_ROUND_START) {
		float scale = 50.0f;
		float x = (sdlutils().width() - scale) / 2.0f;
		float y = (sdlutils().height() - scale) / 2.0f;

		_pacManTransform->_pos.set(x, y);
		_pacManTransform->_vel.set(0.0f, 0.0f);
		_pacManTransform->_rot = 0.0f;
	}

	else if (msg.id == msgId::_m_NEW_GAME) {
		_pacManHealth->lives = _pacManHealth->maxLives;
	}

	else if (msg.id == msgId::_m_PACMAN_FOOD_COLLISION) {
		auto fruit = msg.fruit_eaten.e;
		_manager->setAlive(fruit, false);

		if (_manager->hasComponent<Miraculous>(fruit)
			&& _manager->getComponent<Miraculous>(fruit)->_state) {
			Message m;
			m.id = msgId::_m_IMMUNITY_START;
			_manager->send(m);
		}
	}

	else if (msg.id == msgId::_m_PACMAN_GHOST_COLLISION) {
		auto pacman = _manager->getHandler(ecs::hdlr::PACMAN);
		auto ghost = msg.ghost_hit.e;

		if (_manager->getComponent<Inmunity>(pacman)->_inmune) _manager->setAlive(ghost, false);
		else {
			Message m;
			m.id = msgId::_m_ROUND_OVER;
			_manager->send(m);
		}
	}

	else if (msg.id == msgId::_m_ROUND_OVER) {
		auto health = _manager->getComponent<Health>(_manager->getHandler(ecs::hdlr::PACMAN));

		health->lives--;

		if (health->lives <= 0) {
			Message m;
			m.id = msgId::_m_GAME_OVER;
			_manager->send(m);
		}
	}

	else if (msg.id == msgId::_m_IMMUNITY_START) {
	}
}
