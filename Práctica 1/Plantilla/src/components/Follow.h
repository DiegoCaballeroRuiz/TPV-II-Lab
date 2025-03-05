#pragma once 

#include "../ecs/Component.h"

class Transform;
class Follow : public ecs::Component {
	Transform* _target;
	Transform* _mTransform;
public:
	__CMPID_DECL__(ecs::cmp::FOLLOW);
	Follow(Transform* target);

	void initComponent() override;

	void update() override;
};