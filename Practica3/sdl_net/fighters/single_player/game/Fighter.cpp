// This file is part of the course TPV2@UCM - Samir Genaim

#include "Fighter.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

Fighter::Fighter(BulletManager &bm) :
		_fighter_img(sdlutils().images().at("fighter")), //
		_ihdlr(ih()), //
		_bm(bm), //
		_lastShoot(0) {

	auto &rand = sdlutils().rand();

	int x = rand.nextInt(0, sdlutils().width() - 40);
	int y = rand.nextInt(0, sdlutils().height() - 40);

	_player = { 0, Vector2D(), Vector2D(x, y), 40, 40, 2.0f, 0.0f, ALIVE };

}

Fighter::~Fighter() {
}

void Fighter::update() {

	Player &p = _player;

	// dead player don't move/spin/shoot
	if (p.state != ALIVE)
		return;

	spin(p);  // handle spinning
	move(p);  // handle moving
	shoot(p); // handle shooting

	// move
	p.pos = p.pos + p.vel;

	// deaccelerate
	p.vel = p.vel * 0.995f;
	if (p.vel.magnitude() < 0.05f)
		p.vel.set(0.0f, 0.0f);

	// show at opposite side
	if (p.pos.getY() + p.height < 0.0f) {
		p.pos.setY(sdlutils().height() - 1);
	} else if (p.pos.getY() > sdlutils().height()) {
		p.pos.setY(-p.height + 1);
	}

	if (p.pos.getX() + p.width < 0.0f) {
		p.pos.setX(sdlutils().width() - 1);
	} else if (p.pos.getX() > sdlutils().width()) {
		p.pos.setX(-p.width + 1);
	}

}

void Fighter::render() {
	Player &p = _player;
	if (p.state == ALIVE) {
		SDL_Rect dest = build_sdlrect(p.pos, p.width, p.height);
		_fighter_img.render(dest, p.rot);
	}
}

void Fighter::move(Player &p) {
	if (_ihdlr.isKeyDown(SDL_SCANCODE_W)) {

		p.vel = p.vel + Vector2D(0, -1).rotate(p.rot) * 0.1f;
		if (p.vel.magnitude() > p.speed)
			p.vel = p.vel.normalize() * p.speed;
	}
}

void Fighter::spin(Player &p) {
	if (_ihdlr.isKeyDown(SDL_SCANCODE_L)) {
		p.rot += 5.0f;
	} else if (_ihdlr.isKeyDown(SDL_SCANCODE_H)) {
		p.rot -= 5.0f;
	}
}

void Fighter::shoot(Player &p) {
	if (_ihdlr.keyDownEvent() && _ihdlr.isKeyDown(SDL_SCANCODE_SPACE)) {
		if (sdlutils().virtualTimer().currTime() < _lastShoot + 250)
			return;

		_lastShoot = sdlutils().virtualTimer().currTime();

		auto c = p.pos + Vector2D(p.width / 2.0f, p.height / 2.0f);

		int bwidth = 5;
		int bheight = 20;

		Vector2D bp = c
				- Vector2D(0.0f, p.height / 2.0f + bheight / 2).rotate(p.rot)
				- Vector2D(bwidth / 2, bheight / 2);

		Vector2D bv = Vector2D(0, -1).rotate(p.rot)
				* (p.vel.magnitude() + 5.0f);

		_bm.shoot(bp, bv, bwidth, bheight, Vector2D(0, -1).angle(bv));
	}
}
