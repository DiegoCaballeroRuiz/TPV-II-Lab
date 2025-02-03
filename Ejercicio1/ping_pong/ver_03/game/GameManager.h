// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <array>
#include "GameObject.h"

class GameManager: public GameObject {
public:

	enum Side {
		LEFT = 0, //
		RIGHT
	};
	
	enum GameState {
		NEWGAME = 0, // just before starting a new game
		PAUSED, // between rounds
		RUNNING, // playing
		GAMEOVER // game over
	};

	GameManager(GameObject *ball);
	virtual ~GameManager();

	inline GameState getState() {
		return _state;
	}

	void onBallExit(Side side);

	void handleInput() override;
	void update() override;
	void render() override;

private:
	void resetBall();
	void moveBall();
	std::array<unsigned int, 2> _score;
	GameState _state;
	const unsigned int _maxScore;
	GameObject *_ball;
};

