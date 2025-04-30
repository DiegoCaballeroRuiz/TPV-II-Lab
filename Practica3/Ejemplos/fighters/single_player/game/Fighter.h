// This file is part of the course TPV2@UCM - Samir Genaim

/*
 * The content of this class is based on https://glouw.com/2018/03/11/littlewolf.html
 */

#pragma once

#include <SDL.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <array>
#include <string>
#include <fstream>

#include "../sdlutils/InputHandler.h"
#include "../utils/Vector2D.h"
#include "BulletsManager.h"

class Texture;
class InputHandler;

class Fighter {
public:

	// the status of a player
	enum PlayerState : uint8_t {
		NOT_USED, ALIVE, DEAD
	};

	// player information
	struct Player {
		uint8_t id;          // the id
		Vector2D vel;        // vel
		Vector2D pos;        // position;
		int width;
		int height;
		float speed;         // maximum speed
		float rot;         // rotation
		PlayerState state;   // the state
	};

	Fighter(BulletManager &bm);
	virtual ~Fighter();

	// render the walls, etc
	void render();

	// update the world, tec
	void update();

private:

	void shoot(Player &p);
	void spin(Player &p);
	void move(Player &p);


	// array of players
	Player _player;

	Texture &_fighter_img;
	InputHandler &_ihdlr;
	BulletManager &_bm;
	Uint32 _lastShoot;

};

