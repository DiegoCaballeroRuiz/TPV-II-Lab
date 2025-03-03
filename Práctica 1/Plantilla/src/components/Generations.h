#pragma once 

#include "../ecs/Component.h"

class Generations : public ecs::Component {
	int _generation;
public:
	inline Generations(int initialGeneration) : _generation(initialGeneration) {}

	inline void advanceGeneration() { _generation++; }
	inline void setGeneration(int gen) { _generation = gen; }
	inline int getGeneration() const { return _generation; }
};