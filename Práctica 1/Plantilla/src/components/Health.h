#pragma once

#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

#include <SDL.h>

class Texture;

class Health : public ecs::Component {
protected:
	int _maxHealth;
	int _currentHealth;
	SDL_Rect _heartPosition;
	float _distanceBetweenHearts;
	Texture* _heartTexture;

public:
	__CMPID_DECL__(ecs::cmp::HEALTH)

	Health(SDL_Rect heartPosition, float distanceBetweenHearts, Texture* texture, int startingHealth = 3);

	inline int getHealth() const { return _currentHealth; }

	inline void addLife(int lives) { _currentHealth += lives; }
	inline void resetLifes() { _currentHealth = _maxHealth; }

	void render() override;
};