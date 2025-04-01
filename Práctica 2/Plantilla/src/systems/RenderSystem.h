// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

class Texture;
struct Transform;
class SDL_Rect;

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

	SDL_Rect _cherrySrcRect, _pearSrcRect, _ghostSrcRect;
};

