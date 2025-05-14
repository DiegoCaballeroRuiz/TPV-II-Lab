#include "ImmunitySystem.h"
#include "../ecs/Manager.h"
#include "../components/Miraculous.h"
#include "../components/Inmunity.h"
#include "../sdlutils/SDLUtils.h"

ImmunitySystem::ImmunitySystem() : _immunityComponents() {

}

ImmunitySystem::~ImmunitySystem() {

}

void 
ImmunitySystem::initSystem() {

}

void 
ImmunitySystem::update() {
	for (Immunity* immunity : _immunityComponents) {
		if (!immunity->_inmune) continue;

		if (sdlutils().virtualTimer().currTime() >= immunity->_immunityEnd) {
			Message m;
			m.id = msgId::_m_IMMUNITY_END;
			m.inmunity_end.immunity = immunity;
			_manager->send(m);
		}
	}
}

void 
ImmunitySystem::recieve(const Message& m) {
	switch (m.id) {
	case _m_PACMAN_FOOD_COLLISION:
		if (_manager->hasComponent<Miraculous>(m.fruit_eaten.e)
			&& _manager->getComponent<Miraculous>(m.fruit_eaten.e)->_state) {
			Message m;
			m.id = msgId::_m_IMMUNITY_START;
			m.inmunity_start.immunity = _pacManImmunity;
			_manager->send(m);
		}
		break;

	case _m_IMMUNITY_START:
		m.inmunity_start.immunity->_inmune = true;
		m.inmunity_start.immunity->_immunityEnd = sdlutils().virtualTimer().currTime() + _immunityTime;
		break;

	case _m_IMMUNITY_END:
		m.inmunity_end.immunity->_inmune = false;
		break;

	case _m_REGISTER_IMMUNE:
		if (m.register_immune.isPacMan) _pacManImmunity = m.register_immune.immunity;
		_immunityComponents.push_back(m.register_immune.immunity);
		break;
	}
}