#pragma once

class Game;
class GameState {
	Game* _game;
public:
	GameState(Game* game) {}
	virtual ~GameState() {}
	virtual void enter() = 0;
	virtual void leave() = 0;
	virtual void update() = 0;
};