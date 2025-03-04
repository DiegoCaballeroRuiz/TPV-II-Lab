#pragma once 

#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

class Transform;
class TowardDestination : public ecs::Component {
	Vector2D _destination;
	Transform* _transform;

protected:
	void getRandomDestination();
public:
	TowardDestination();

	void initComponent() override;

	void update() override;
};