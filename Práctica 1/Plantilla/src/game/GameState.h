#pragma once

class Game;
class InputHandler;
class GameState {
protected:
	Game* _game;
	InputHandler* _inputHandler;
public:
	GameState(Game* game) : _game(game) {}
	virtual ~GameState() {}
	virtual void enter() = 0;
	virtual void leave() = 0;
	virtual void update() = 0;
};