#pragma once

#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

#include <array>

class Texture;
class InputHandler;

class Gun : public ecs::Component {
public:
	Gun(Texture* texture);
	// ... 
	struct Bullet {
		bool used = false;
		Vector2D pos;
		Vector2D vel;
		int width;
		int height;
		float rot;
	};
	constexpr static uint8_t _max_bullets = 20;
	
	typedef std::array<Bullet, _max_bullets> bullets_array_t;
	typedef bullets_array_t::iterator iterator;
	iterator begin() {
		return _bullets.begin();
	}
	iterator end() {
		return _bullets.end();
	}
	
	void reset();
	void render() override;
	void update() override;
	void initComponent() override;


private:
	void shoot(Vector2D p, Vector2D v, int width, int height, float r);
	bullets_array_t _bullets;
	iterator _lastBullet;
	Texture* _bulletTexture;
	InputHandler* _inputHandler;
};