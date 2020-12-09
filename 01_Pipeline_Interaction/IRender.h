#pragma once
#include "Component.h"

class IRender : public Component {
public:
	IRender(Entity &parent) : Component(parent) {};
	virtual void Draw() = 0;
};