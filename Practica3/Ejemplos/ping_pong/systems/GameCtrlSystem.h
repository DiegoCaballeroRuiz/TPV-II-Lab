// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>
#include <array>
#include <cstdint>

#include "../ecs/System.h"

struct GameState;

class GameCtrlSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::_sys_GAMECTRL)


	enum Side : Uint8 {
		LEFT = 0, //
		RIGHT
	};

	enum State : Uint8 {
		NEWGAME = 0, // just before starting a new game
		PAUSED, // between rounds
		RUNNING, // playing
		GAMEOVER // game over
	};

	GameCtrlSystem();
	virtual ~GameCtrlSystem();

	inline State getState() {
		return _state;
	}

	inline unsigned int getScore(std::size_t player) {
		return _score[player];
	}

	void requestToStartRound();
	void requestToStartGame();
	void startRound();
	void startGame();
	void killPacMan();
	void gameOver();
	void onBallExit(Uint8 side);
	void stopTheGame();

	void update() override;
	void recieve(const Message&) override;



private:


	std::array<unsigned int, 2> _score;
	State _state;
	const unsigned int _maxScore;

};

