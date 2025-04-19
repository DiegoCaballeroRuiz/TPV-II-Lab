// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameCtrlSystem.h"

#include "../components/GameState.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "BallSystem.h"
#include "NetworkSystem.h"
GameCtrlSystem::GameCtrlSystem() :
		_score(), //
		_state(NEWGAME), //
		_maxScore(2) {
}

GameCtrlSystem::~GameCtrlSystem() {
}

void GameCtrlSystem::update() {
	if (!_mngr->getSystem<NetworkSystem>()->isReday())
		return;

	if (_state != RUNNING) {

		auto &inhdlr = ih();

		if (inhdlr.isKeyDown(SDL_SCANCODE_SPACE)) {
			switch (_state) {
			case NEWGAME:
				requestToStartRound();
				break;
			case PAUSED:
				requestToStartRound();
				break;
			case GAMEOVER:
				requestToStartGame();
				break;
			default:
				break;
			}
		}
	}
}

void GameCtrlSystem::startRound() {

	if (_state != PAUSED && _state != NEWGAME)
		return;

	Message m;

	_state = RUNNING;
	m.id = _m_ROUND_START;
	_mngr->send(m);
}

void GameCtrlSystem::startGame() {

	if (_state != GAMEOVER)
		return;

	Message m;

	_state = NEWGAME;
	_score[0] = 0;
	_score[1] = 0;
	m.id = _m_NEW_GAME;
	_mngr->send(m);

}

void GameCtrlSystem::requestToStartRound() {
	if (_mngr->getSystem<NetworkSystem>()->isHost()) {
		startRound();
	} else {
		_mngr->getSystem<NetworkSystem>()->sendStarRoundtRequest();
	}
}

void GameCtrlSystem::requestToStartGame() {
	if (_mngr->getSystem<NetworkSystem>()->isHost()) {
		startGame();
	} else {
		_mngr->getSystem<NetworkSystem>()->sendStarGameRequest();
	}
}

void GameCtrlSystem::killPacMan() {
	Message m;
	_state = PAUSED;
	m.id = _m_ROUND_OVER;
	_mngr->send(m);
}

void GameCtrlSystem::gameOver() {
	Message m;
	_state = GAMEOVER;
	m.id = _m_ROUND_OVER;
	_mngr->send(m);
	m.id = _m_GAME_OVER;
	_mngr->send(m);
}

void GameCtrlSystem::onBallExit(Uint8 side) {

	assert(_state == RUNNING); // this should be called only when game is running

	if (side == LEFT) {
		_score[1]++;
	} else {
		_score[0]++;
	}

	if (_score[0] < _maxScore && _score[1] < _maxScore) {
		killPacMan();
	} else {
		gameOver();
	}

}

void GameCtrlSystem::stopTheGame() {
	Message m;
	_state = NEWGAME;
	_score[0] = 0;
	_score[1] = 0;
	m.id = _m_NEW_GAME;
	_mngr->send(m);
}

void GameCtrlSystem::recieve(const Message &m) {
	switch (m.id) {
	case _m_BALL_EXIT:
		onBallExit(static_cast<Side>(m.ball_exit.side));
		break;
	default:
		break;
	}
}
