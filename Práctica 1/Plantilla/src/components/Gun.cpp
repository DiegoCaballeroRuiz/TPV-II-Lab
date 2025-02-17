#include "Gun.h"

#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"

Gun::Gun(Texture* texture) : Component(), _bulletTexture(texture)
{

}

void Gun::initComponent() {
	_inputHandler = InputHandler::Instance();
}

void Gun::reset() {
	for (auto bullet : _bullets) bullet.used = false;
}

void Gun::render() {
	for (auto bullet : _bullets) {
		if (!bullet.used) continue;
		
		SDL_Rect renderRect;
		renderRect.x = bullet.pos.getX();
		renderRect.y = bullet.pos.getY();
		renderRect.w = bullet.width;
		renderRect.h = bullet.height;

		_bulletTexture->render(renderRect, bullet.rot);
	}
}

void Gun::shoot(Vector2D p, Vector2D v, int width, int height, float r) {
	iterator currentBullet = _lastBullet;
	++_lastBullet;

	while (_lastBullet != currentBullet && _lastBullet->used) {
		if (_lastBullet == _bullets.end()) _lastBullet = _bullets.begin();
		else _lastBullet++;
	}

	if (_lastBullet == currentBullet) return;

	_lastBullet->used = true;
	_lastBullet->pos = p;
	_lastBullet->vel = v;
	_lastBullet->width = width;
	_lastBullet->height = height;
	_lastBullet->rot = r;
}

void Gun::update() {
	//if(_inputHandler->isKeyDown(SDLK_s)) 
}