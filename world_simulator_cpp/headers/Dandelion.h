#pragma once
#include "Plant.h"

class Dandelion : public Plant {
private:

public:
	Dandelion(World* currentWorld, int X_coordinate, int Y_coordinate);

	void Action() override;
};
