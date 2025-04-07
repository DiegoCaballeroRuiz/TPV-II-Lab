// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"
#include <SDL.h>

class Texture;
struct Transform;

class RenderSystem: public ecs::System {
public:

	RenderSystem();
	virtual ~RenderSystem();
	void initSystem() override;
	void update() override;
private:
	void drawFruits();
	void drawPacMan();
	void drawGhosts();
	void drawMsgs();
	void draw(Transform *tr, Texture *tex);
	void drawSrc(Transform* tr, Texture* tex, SDL_Rect src);

	
};

