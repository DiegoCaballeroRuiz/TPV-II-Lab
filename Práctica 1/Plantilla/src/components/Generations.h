#pragma once 

#include "../ecs/Component.h"

class Generations : public ecs::Component {
	int _generation;
public:
	__CMPID_DECL__(ecs::cmp::GENERATIONS);
	inline Generations(int initialGeneration = 3) : _generation(initialGeneration) {}

	inline void advanceGeneration() { _generation++; }
	inline void setGeneration(int gen) { _generation = gen; }
	inline int getGeneration() const { return _generation; }
};