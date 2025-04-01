// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/Miraculous.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "GameCtrlSystem.h"

RenderSystem::RenderSystem() {
	_cherrySrcRect = build_sdlrect(128 * 5, 128 * 2, 128, 128);
	_pearSrcRect = build_sdlrect(128 * 8, 128 * 2, 128, 128);
	_ghostSrcRect = build_sdlrect(128 * 5, 128 * 5, 128, 128);
}

RenderSystem::~RenderSystem() {

}

void RenderSystem::initSystem() {
}

void RenderSystem::update() {
	drawMsgs();
	drawFruits();
	drawPacMan();
}

void RenderSystem::drawFruits() {
	// draw stars
	for (auto e : _manager->getEntities(ecs::grp::FRUITS)) {

		auto tr = _manager->getComponent<Transform>(e);
		auto tex = _manager->getComponent<Image>(e)->_tex;

		SDL_Rect src;
		if (_manager->hasComponent<Miraculous>(e)) {
			bool type = _manager->getComponent<Miraculous>(e)->_state;
			src = type
				? _cherrySrcRect
				: _pearSrcRect;
		}
		else src = _cherrySrcRect;

		drawSrc(tr, tex, src);
	}
}

void RenderSystem::drawPacMan() {
	auto e = _manager->getHandler(ecs::hdlr::PACMAN);
	auto tr = _manager->getComponent<Transform>(e);
	auto tex = _manager->getComponent<Image>(e)->_tex;
	draw(tr, tex);
}

void RenderSystem::drawGhosts() {
	for (auto ghost : _manager->getEntities(ecs::grp::GHOSTS)) {
		auto tr = _manager->getComponent<Transform>(ghost);
		auto tex = _manager->getComponent<Image>(ghost)->_tex;
		draw(tr, tex);
	}
}


void RenderSystem::drawMsgs() {
	// draw the score
	//
	auto score = _manager->getSystem<GameCtrlSystem>()->getScore();

	Texture scoreTex(sdlutils().renderer(), std::to_string(score),
			sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0x444444ff));

	SDL_Rect dest = build_sdlrect( //
			(sdlutils().width() - scoreTex.width()) / 2.0f, //
			10.0f, //
			scoreTex.width(), //
			scoreTex.height());

	scoreTex.render(dest);

	// draw add stars message
	sdlutils().msgs().at("addstars").render(10, 10);

}

void RenderSystem::draw(Transform *tr, Texture *tex) {
	SDL_Rect dest = build_sdlrect(tr->_pos, tr->_width, tr->_height);

	assert(tex != nullptr);
	tex->render(dest, tr->_rot);
}

void 
RenderSystem::drawSrc(Transform* tr, Texture* tex, SDL_Rect src) {
	SDL_Rect dest = build_sdlrect(tr->_pos, tr->_width, tr->_height);

	assert(tex != nullptr);
	tex->render(src, dest, tr->_rot);
}

