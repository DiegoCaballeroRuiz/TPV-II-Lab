#pragma once 

#include "../facade/FighterFacade.h"

namespace ecs {
	class Manager;
}

class FighterUtils : public FighterFacade {
	ecs::Manager* _mngr;
public:
	FighterUtils(ecs::Manager* manager);
	~FighterUtils() {}
	void create_fighter();
	void reset_fighter();
	void reset_lives();
	int update_lives(int n);
};