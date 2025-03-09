#pragma once 
#include "../facade/AsteroidsFacade.h"
#include "../utils/Vector2D.h"
namespace ecs {
	class Manager;
}
class AsteroidsUtils : public AsteroidsFacade {
	ecs::Manager* _manager;

	void create_asteroid(Vector2D p, Vector2D v, int gen);
public:
	AsteroidsUtils(ecs::Manager* manager);
	~AsteroidsUtils() override;

	void create_asteroids(int n) override;
	void remove_all_asteroids() override;
	void split_astroid(ecs::entity_t a) override;
	int getNumberOfAsteroids();
};