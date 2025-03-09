#include "ImageWithFrames.h"

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

ImageWithFrames::ImageWithFrames(Texture* texture, int frameWidth, int frameHeight, int frameCountX, int frameCountY) 
	: Component(), _texture(texture), _frameHeight(frameHeight), _frameWidth(frameWidth), _frameCountX(frameCountX), _frameCountY(frameCountY), 
	_lastFrameChange(0), _currentFrameX(0), _currentFrameY(0)
{

}

void 
ImageWithFrames::initComponent() {
	_transform = _ent->getMngr()->getComponent<Transform>(_ent);
}

void 
ImageWithFrames::render() {
	if ((sdlutils().virtualTimer().currTime() - _lastFrameChange) > 50) {
		_lastFrameChange = sdlutils().virtualTimer().currTime();
		_currentFrameX++;
		if (_currentFrameX >= _frameCountX) {
			_currentFrameX = 0;
			_currentFrameY++;
			if (_currentFrameY >= _frameCountY) _currentFrameY = 0;
		}
	}
	SDL_Rect src = { _frameWidth * _currentFrameX, _frameHeight * _currentFrameY, _frameWidth, _frameHeight };
	SDL_Rect dest = { _transform->getPos().getX(), _transform->getPos().getY(), _transform->getWidth(), _transform->getHeight()};

	_texture->render(src, dest);
}