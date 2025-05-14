#include "../ecs/System.h"
#include <vector>

class Immunity;

class ImmunitySystem : public ecs::System {
public:
	ImmunitySystem();
	~ImmunitySystem();

	void initSystem() override;
	void update() override;
	void recieve(const Message& m) override;

private:
	std::vector<Immunity*> _immunityComponents;
	Immunity* _pacManImmunity;
	std::uint32_t _immunityTime = 3000U;
};