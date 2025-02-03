#pragma once

#include "InputComponent.h"

class FighterCtrl : public InputComponent
{
public:
	FighterCtrl(): InputComponent(), _rotationDegrees(5.0f), _thrust(0.2), _speedLimit(3.0f) {}
	void handleInput(Container* o) override;

protected:
	float _rotationDegrees;
	float _thrust;
	float _speedLimit;
};

