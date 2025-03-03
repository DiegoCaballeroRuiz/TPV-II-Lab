#include "Gun.h"
#include "Transform.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include <cmath>

#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

Gun::Gun(Texture* texture) : Component(), _bulletTexture(texture)
{
	_lastShootingTime = sdlutils().virtualTimer().currTime();
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
		
		SDL_Rect renderRect = { bullet.pos.getX(), bullet.pos.getY(), bullet.width, bullet.height };

		_bulletTexture->render(renderRect, bullet.rot);
	}
}

void Gun::shoot(Vector2D p, Vector2D v, int width, int height, float r) {
	if ((sdlutils().virtualTimer().currTime() - _lastShootingTime) < 250) return;
	size_t currentBullet = _lastBullet;

	do {
		if (_lastBullet >= _max_bullets - 1) _lastBullet = 0;
		else _lastBullet++;

		if (!_bullets[_lastBullet].used) break;
	} while (_lastBullet != currentBullet);
	
	if (_lastBullet == currentBullet) return;

	_bullets[_lastBullet] = { true, p, v, width, height, r };
	_lastShootingTime = sdlutils().virtualTimer().currTime();
}

void Gun::update() {
	if (_inputHandler->isKeyDown(SDLK_s)) {
		float radians = _transform->getRot() * M_PI / 180;
		Vector2D vel = { std::sin(radians), -std::cos(radians)};
		shoot(_transform->getPos(), vel * 10, _bulletTexture->width(), _bulletTexture->height(), _transform->getRot());
	}

	for (auto& bullet : _bullets)
		if (bullet.used) {
			bullet.used = !(bullet.pos.getX() > sdlutils().width()
				|| bullet.pos.getX() < -bullet.width
				|| bullet.pos.getY() > sdlutils().height()
				|| bullet.pos.getY() < -bullet.height);

			bullet.pos = bullet.pos + bullet.vel;
		}
}