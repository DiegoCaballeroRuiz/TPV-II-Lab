#include "FighterUtils.h"

#include "../ecs/ecs.h"
#include "../components/Health.h"
#include "../components/FighterCtrl.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Gun.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/DeAcceleration.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"

#include<SDL.h>

FighterUtils::FighterUtils(ecs::Manager* manager) : FighterFacade(), _mngr(manager)
{
}

FighterUtils::~FighterUtils() {

}

void 
FighterUtils::create_fighter() {
	auto nave = _mngr->addEntity();
	_mngr->setHandler(ecs::hdlr::SHIP, nave);


	auto transform = _mngr->addComponent<Transform>(nave);
	float scale = 50.0f;
	float centerX = (sdlutils().width() - scale) / 2.0f;
	float centerY = (sdlutils().height() - scale) / 2.0f;
	transform->init(Vector2D(centerX, centerY), { 0, 0 }, scale, scale, 0.0f);

	_mngr->addComponent<DeAcceleration>(nave);

	_mngr->addComponent<Image>(nave, &sdlutils().images().at("ship"));

	scale = 50.0f;
	float heartX = (sdlutils().width() - scale) * 0.01f;
	float heartY = (sdlutils().height() - scale) * 0.01f;
	SDL_Rect heartPos = { heartX, heartY, scale, scale };
	_mngr->addComponent<Health>(nave, heartPos, 10.0f, &sdlutils().images().at("heart"));
	_mngr->addComponent<FighterCtrl>(nave);
	_mngr->addComponent<Gun>(nave, &sdlutils().images().at("bullet"));
	_mngr->addComponent<ShowAtOppositeSide>(nave);
}

void 
FighterUtils::reset_fighter() {
	auto transform = _mngr->getComponent<Transform>(_mngr->getHandler(ecs::hdlr::SHIP));

	float centerX = (sdlutils().width() - transform->getWidth()) / 2.0f;
	float centerY = (sdlutils().height() - transform->getHeight()) / 2.0f;
	transform->getPos() = { centerX, centerY };

	_mngr->getComponent<Gun>(_mngr->getHandler(ecs::hdlr::SHIP))->reset();
}

void 
FighterUtils::reset_lives() {
	_mngr->getComponent<Health>(_mngr->getHandler(ecs::hdlr::SHIP))->resetLifes();
}

int 
FighterUtils::update_lives(int n) {
	_mngr->getComponent<Health>(_mngr->getHandler(ecs::hdlr::SHIP))->addLife(n);

}