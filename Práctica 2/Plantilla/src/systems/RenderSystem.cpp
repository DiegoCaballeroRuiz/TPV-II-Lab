// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/Miraculous.h"
#include "../components/TextureSrc.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "GameCtrlSystem.h"

RenderSystem::RenderSystem() {
	
}

RenderSystem::~RenderSystem() {

}

void RenderSystem::initSystem() {
}

void RenderSystem::update() {
	drawFruits();
	drawPacMan();
	drawGhosts();
}

void RenderSystem::drawFruits() {
	// draw stars
	for (auto e : _manager->getEntities(ecs::grp::FRUITS)) {
		auto tr = _manager->getComponent<Transform>(e);
		auto tex = _manager->getComponent<Image>(e)->_tex;
		auto src = _manager->getComponent<TextureSrc>(e)->_src;
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
		auto src = _manager->getComponent<TextureSrc>(ghost)->_src;
		drawSrc(tr, tex, src);
	}
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

