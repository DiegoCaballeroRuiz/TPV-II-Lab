// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>

#include "../ecs/ecs.h"
#include "GameState.h"

class Game {
private:
	ecs::Manager* _mngr;
	ecs::System* _pacmanSys;
	ecs::System* _renderSys;
	ecs::System* _collisionSys;
	ecs::System* _fruitSys;
	ecs::System* _ghostSys;
	ecs::System* _stateSys;

	GameState* _state;
	GameState* _paused_state;
	GameState* _runing_state;
	GameState* _newgame_state;
	GameState* _newround_state;
	GameState* _gameover_state;
public:
	Game();
	virtual ~Game();
	void init();
	void start();

	inline ecs::Manager* getManager() { return _mngr; }

	inline ecs::System* getPacManSys() { return _pacmanSys; }
	inline ecs::System* getFruitSys() { return _fruitSys; }
	inline ecs::System* getGhostSys() { return _ghostSys; }
	inline ecs::System* getRenderSys() { return _renderSys; }
	inline ecs::System* getCollisionSys() { return _collisionSys; }

	enum State {
		RUNNING, PAUSED, NEWGAME, NEWROUND, GAMEOVER
	};

	inline void setState(State s) {
		if(_state != nullptr) _state->leave();
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

};

