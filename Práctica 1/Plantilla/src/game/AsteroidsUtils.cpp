#include "AsteroidsUtils.h"

#include "../ecs/Manager.h"
#include "../components/Generations.h"
#include "../components/Follow.h"
#include "../components/TowardDestination.h"
#include "../components/Transform.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/ImageWithFrames.h"

#include "../sdlutils/SDLUtils.h"

AsteroidsUtils::AsteroidsUtils(ecs::Manager* manager) : AsteroidsFacade(), _manager(manager)
{
}


void 
AsteroidsUtils::create_asteroids(int n) {
	for (int i = 0; i < n; i++) {
		//Crear la entidad
		auto asteroide = _manager->addEntity(ecs::grp::ASTEROIDS);
		_manager->setHandler(ecs::hdlr::ASTEROIDS, asteroide);

		//Crear el transform
		auto transform = _manager->addComponent<Transform>(asteroide);
		//Posicion
		int x = sdlutils().rand().nextInt(0, sdlutils().width());
		int y = sdlutils().rand().nextInt(0, sdlutils().height());
		Vector2D pos = { float(x), float(y) };

		//Escala
		float scale = 50.0f;
		//Velocidad
		float speed = sdlutils().rand().nextInt(1, 10) / 10.0f;
		float centerX = (sdlutils().width() - scale) / 2.0f;
		float centerY = (sdlutils().height() - scale) / 2.0f;

		Vector2D vel = (Vector2D(centerX, centerY) - pos).normalize() * speed;

		transform->init(pos, vel, scale, scale, 0.0f);

		//Crear Image
		_manager->addComponent<ImageWithFrames>(asteroide, &sdlutils().images().at("asteroidG"), 510 / 6, 100, 6, 5);

		//Crear toroidal
		_manager->addComponent<ShowAtOppositeSide>(asteroide);

		//Crear follow o towards
		if (sdlutils().rand().nextInt(0, 1)) {
			auto target = _manager->getComponent<Transform>(_manager->getHandler(ecs::hdlr::SHIP));
			_manager->addComponent<Follow>(asteroide, target);
		}
		else {
			_manager->addComponent<TowardDestination>(asteroide);
		}

		//Crear generation
		_manager->addComponent<Generations>(asteroide);
	}
}

void 
AsteroidsUtils::remove_all_asteroids() {
	auto asteroids = _manager->getEntities(ecs::grp::ASTEROIDS);

	for (auto asteroid : asteroids) delete asteroid;

	asteroids.clear();
}

void 
AsteroidsUtils::split_astroid(Entity* a) {

}