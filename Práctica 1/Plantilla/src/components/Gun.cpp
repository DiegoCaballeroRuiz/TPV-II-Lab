#include "Gun.h"
#include "Transform.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include <cmath>

#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"

Gun::Gun(Texture* texture) : Component(), _bulletTexture(texture)
{

}

void Gun::initComponent() {
	_inputHandler = InputHandler::Instance();
	_transform = _ent->getMngr()->getComponent<Transform>(_ent);
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

	*_lastBullet = { true, p, v, width, height, r };
}

void Gun::update() {
	if (_inputHandler->isKeyDown(SDLK_s)) {
		Vector2D vel = { std::sin(_transform->getRot()), std::cos(_transform->getRot()) };
		shoot(_transform->getPos(), vel, _bulletTexture->width(), _bulletTexture->height(), _transform->getRot());
	}

	for (auto bullet : _bullets)
		if (bullet.used) bullet.pos = bullet.pos + bullet.vel;
}