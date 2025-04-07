#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/macros.h"
#include <SDL.h>

struct TextureSrc : public ecs::Component {

	TextureSrc(SDL_Rect src) : _src(src) {}
	TextureSrc(int x, int y, int w, int h) : _src(build_sdlrect(x, y, w, h)) {}

	SDL_Rect _src;
};