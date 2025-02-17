#include "Health.h"

#include "../sdlutils/Texture.h"

Health::Health(SDL_Rect heartPosition, float distanceBetweenHearts, Texture* texture, int startingHealth)
	: Component(), _maxHealth(startingHealth), _currentHealth(_maxHealth), _heartPosition(heartPosition), _distanceBetweenHearts(distanceBetweenHearts), _heartTexture(texture) 
{

}

void Health::render() {
	SDL_Rect renderRect = _heartPosition;
	for (int i = 0; i < _currentHealth; ++i) {
		_heartTexture->render(renderRect);
		renderRect.x += _distanceBetweenHearts + renderRect.w;
	}
}