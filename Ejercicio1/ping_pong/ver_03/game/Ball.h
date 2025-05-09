// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "GameObject.h"

class Ball: public GameObject {
public:
	Ball();
	Ball(SDL_Color color);
	virtual ~Ball();

	void update() override;
	void render() override;
	void handleInput() override;

private:
	SDL_Color _color;
};

