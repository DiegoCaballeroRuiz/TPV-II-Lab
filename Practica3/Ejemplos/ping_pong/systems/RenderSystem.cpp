// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"

#include <SDL_rect.h>
#include "../components/Image.h"
#include "../components/RectangleViewer.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "GameCtrlSystem.h"
#include "NetworkSystem.h"

RenderSystem::RenderSystem() {
}

RenderSystem::~RenderSystem() {
}

void RenderSystem::initSystem() {
}

void RenderSystem::update() {
	if (_mngr->getSystem<NetworkSystem>()->isReday()) {
		drawMsgs();
		drawScore();
	} else {
		drawWaitingMsg();
	}
	drawBall();
	drawPaddles();
}

void RenderSystem::drawMsgs() {

	auto state = _mngr->getSystem<GameCtrlSystem>()->getState();

	// message when game is not running
	if (state != GameCtrlSystem::RUNNING) {

		// game over message
		if (state == GameCtrlSystem::GAMEOVER) {
			auto &t = sdlutils().msgs().at("gameover");
			t.render((sdlutils().width() - t.width()) / 2,
					(sdlutils().height() - t.height()) / 2);
		}

		// new game message
		if (state == GameCtrlSystem::NEWGAME) {
			auto &t = sdlutils().msgs().at("start");
			t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
		} else {
			auto &t = sdlutils().msgs().at("continue");
			t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
		}
	}
}

void RenderSystem::drawScore() {

	auto leftScore = _mngr->getSystem<GameCtrlSystem>()->getScore(0);
	auto rightScore = _mngr->getSystem<GameCtrlSystem>()->getScore(1);

	Texture scoreMsg(
			sdlutils().renderer(), //
			std::to_string(leftScore) + " - " + std::to_string(rightScore),
			sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0xffffffff));
	scoreMsg.render((sdlutils().width() - scoreMsg.width()) / 2, 10);

}

void RenderSystem::drawBall() {
	auto ball = _mngr->getHandler(ecs::hdlr::_hdlr_BALL);
	auto ballTr = _mngr->getComponent<Transform>(ball);
	auto ballImg = _mngr->getComponent<Image>(ball);

	SDL_Rect dest = build_sdlrect(ballTr->_pos, ballTr->_width,
			ballTr->_height);

	assert(ballImg->_tex != nullptr);
	ballImg->_tex->render(dest, ballTr->_rot);

}

void RenderSystem::drawPaddles() {
	for (auto e : _mngr->getEntities(ecs::grp::_grp_PADDLES)) {
		auto paddleTr = _mngr->getComponent<Transform>(e);

		SDL_Rect dest = build_sdlrect(paddleTr->_pos.getX(),
				paddleTr->_pos.getY(), paddleTr->_width, paddleTr->_height);

		_mngr->getComponent<RectangleViewer>(e)->draw(sdlutils().renderer(),
				dest);
	}
}

void RenderSystem::drawWaitingMsg() {
	auto port = _mngr->getSystem<NetworkSystem>()->getPort();

	Texture waiting(
			sdlutils().renderer(), //
			"Waiting for the other to connect ...",
			sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0xccddaaaff));
	waiting.render((sdlutils().width() - waiting.width()) / 2, 10);

	Texture portmsg(
			sdlutils().renderer(), //
			"Your are connected at port " + std::to_string(port),
			sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0x1155aaff));
	portmsg.render((sdlutils().width() - portmsg.width()) / 2,
			waiting.height() + 30);
}
