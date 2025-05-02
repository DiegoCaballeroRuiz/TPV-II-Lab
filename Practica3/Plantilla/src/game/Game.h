// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "stdint.h"

class LittleWolf;
class Networking;

class Game {
public:
	Game();
	virtual ~Game();
	void init(const char *map, char* host, uint8_t port);
	void initGame();
	void start();

	Networking* getNetworking() { return _networking; }
	LittleWolf* getLittleWolf() { return _little_wolf; }
private:
	LittleWolf* _little_wolf;
	Networking* _networking;
};

