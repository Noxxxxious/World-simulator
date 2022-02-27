#pragma once
#include "Animal.h"

class Fox : public Animal {

public:
	Fox(World* currentWorld, int X_coordinate, int Y_coordinate);

	void Move() override;
	void Action() override;
};


