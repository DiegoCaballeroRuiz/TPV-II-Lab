#pragma once 
#include "../facade/AsteroidsFacade.h"
namespace ecs {
	class Manager;
}
class AsteroidsUtils : public AsteroidsFacade {
	ecs::Manager* _manager;
public:
	AsteroidsUtils(ecs::Manager* manager);
	~AsteroidsUtils();

	void create_asteroids(int n) override;
	void remove_all_asteroids() override;
	void split_astroid(Entity* a) override;
};