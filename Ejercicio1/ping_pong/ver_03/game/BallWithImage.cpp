// This file is part of the course TPV2@UCM - Samir Genaim

#include "BallWithImage.h"

#include "../sdlutils/macros.h"
#include "../sdlutils/Texture.h"

BallWithImage::BallWithImage(Texture *img) :
		_img(img) {

}

BallWithImage::~BallWithImage() {
}

void BallWithImage::render() {
	SDL_Rect dest = build_sdlrect(_pos, _width, _height);
	_img->render(dest);
}
