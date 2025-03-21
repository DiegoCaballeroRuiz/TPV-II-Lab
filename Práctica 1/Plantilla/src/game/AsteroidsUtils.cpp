#include "AsteroidsUtils.h"

#include "../ecs/Manager.h"
#include "../ecs/ecs.h"
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

AsteroidsUtils::~AsteroidsUtils() {
	remove_all_asteroids();
}


void 
AsteroidsUtils::create_asteroids(int n) {
	for (int i = 0; i < n; i++) {
		float scale = 50.0f;

		//Posicion
		int x = sdlutils().rand().nextInt(0, sdlutils().width());
		int y = sdlutils().rand().nextInt(0, sdlutils().height());
		Vector2D pos = { float(x), float(y) };

		//Velocidad
		float speed = sdlutils().rand().nextInt(1, 10) / 10.0f;
		float centerX = (sdlutils().width() - scale) / 2.0f;
		float centerY = (sdlutils().height() - scale) / 2.0f;

		Vector2D vel = (Vector2D(centerX, centerY) - pos).normalize() * speed;

		create_asteroid(pos, vel, 3);
	}
}

void 
AsteroidsUtils::remove_all_asteroids() {
	auto asteroids = _manager->getEntities(ecs::grp::ASTEROIDS);

	for (auto asteroid : asteroids) _manager->setAlive(asteroid, false);

	_manager->refresh();
}

void 
AsteroidsUtils::split_astroid(ecs::entity_t a) {
	a->getMngr()->setAlive(a, false);

	if (a->getMngr()->getComponent<Generations>(a)->getGeneration() == 0) return;

	for (int i = 0; i < 2; ++i) {
		int r = sdlutils().rand().nextInt(0, 360);
		Transform* aTransform = a->getMngr()->getComponent<Transform>(a);
		Vector2D pos = aTransform->getPos() + aTransform->getVel().rotate(r) * 2 * std::max(aTransform->getWidth(), aTransform->getHeight());
		Vector2D vel = aTransform->getVel().rotate(r) * 1.1f;
		
		create_asteroid(pos, vel, a->getMngr()->getComponent<Generations>(a)->getGeneration() - 1);
	}
}

void
AsteroidsUtils::create_asteroid(Vector2D p, Vector2D v, int gen) {
	//Crear la entidad
	auto asteroide = _manager->addEntity(ecs::grp::ASTEROIDS);
	_manager->setHandler(ecs::hdlr::ASTEROIDS, asteroide);

	//Crear el transform
	auto transform = _manager->addComponent<Transform>(asteroide);

	const float scale = 25.0f + 5.0f * gen;
	
	transform->init(p, v, scale, scale, 0.0f);

	//Crear Image
	_manager->addComponent<ImageWithFrames>(asteroide, &sdlutils().images().at("asteroidG"), 510 / 6, 100, 6, 5);

	//Crear toroidal
	_manager->addComponent<ShowAtOppositeSide>(asteroide);

	//Crear follow o towards
	if (sdlutils().rand().nextInt(0, 2)) {
		auto target = _manager->getComponent<Transform>(_manager->getHandler(ecs::hdlr::SHIP));
		_manager->addComponent<Follow>(asteroide, target);
	}
	else {
		_manager->addComponent<TowardDestination>(asteroide);
	}

	//Crear generation
	_manager->addComponent<Generations>(asteroide, gen);
}

int 
AsteroidsUtils::getNumberOfAsteroids() {
	return _manager->getEntities(ecs::grp::ASTEROIDS).size();
}