// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionsSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"
#include "StarsSystem.h"

CollisionsSystem::CollisionsSystem() {
	// TODO Auto-generated constructor stub

}

CollisionsSystem::~CollisionsSystem() {
	// TODO Auto-generated destructor stub
}

void CollisionsSystem::initSystem() {
}

void CollisionsSystem::update() {

	// the PacMan's Transform
	auto pm = _manager->getHandler(ecs::hdlr::PACMAN);
	auto pTR = _manager->getComponent<Transform>(pm);

	//Fruta
	auto &fruits = _manager->getEntities(ecs::grp::FRUITS);
	int n = fruits.size();

	for (int i = 0; i < n; i++) {
		auto e = fruits[i];
		if (_manager->isAlive(e)) { // if the star is active (it might have died in this frame)

			// the Star's Transform
			auto eTR = _manager->getComponent<Transform>(e);

			// check if PacMan collides with the Star (i.e., eat it)
			if (Collisions::collides(			//
					pTR->_pos, pTR->_width, pTR->_height, //
					eTR->_pos, eTR->_width, eTR->_height)) {

				Message m;
				m.id = msgId::_m_PACMAN_FOOD_COLLISION;
				m.fruit_eaten.e = e;
				_manager->send(m);
			}
		}
	}

	//Fantasmas
	auto& ghosts = _manager->getEntities(ecs::grp::GHOSTS);
	n = ghosts.size();

	for (int i = 0; i < n; i++) {
		auto ghost = ghosts[i];

		if (_manager->isAlive(ghost)) {
			auto transform = _manager->getComponent<Transform>(ghost);

			if (Collisions::collides(			//
				pTR->_pos, pTR->_width, pTR->_height, //
				transform->_pos, transform->_width, transform->_height)) {

				Message m;
				m.id = msgId::_m_PACMAN_GHOST_COLLISION;
				m.ghost_hit.e = ghost;
				_manager->send(m);
			}
		}
	}
}

