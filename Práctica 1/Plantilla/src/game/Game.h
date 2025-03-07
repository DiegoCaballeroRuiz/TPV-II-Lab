// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../utils/Singleton.h"
#include "GameState.h"

namespace ecs {
class Manager;
}
class AsteroidsUtils;
class FighterUtils;

class Game : public Singleton<Game> {
	GameState* _state;
	GameState* _paused_state;
	GameState* _runing_state;
	GameState* _newgame_state;
	GameState* _newround_state;
	GameState* _gameover_state;

	void checkCollisions();
	ecs::Manager* _mngr;
	AsteroidsUtils* _asteroidUtils;
	FighterUtils* _fighterUtils;
public:
	enum State {
		RUNNING, PAUSED, NEWGAME, NEWROUND, GAMEOVER
	};

	inline void setState(State s) {
		_state->leave();
		switch (s) {
		case RUNNING:
			_state = _runing_state;
			break;
		case PAUSED:
			_state = _paused_state;
			break;
		case NEWGAME:
			_state = _newgame_state;
			break;
		case NEWROUND:
			_state = _newround_state;
			break;
		case GAMEOVER:
			_state = _gameover_state;
			break;
		default:
			break;
		}
		_state->enter();
	}

	inline AsteroidsUtils* getAsteroidsUtils() { return _asteroidUtils; }
	inline FighterUtils* getFightersUtils() { return _fighterUtils; }

	Game();
	virtual ~Game();
	bool init();
	void initGame();
	void start();
};

