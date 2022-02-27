#pragma once
#include "Plant.h"

class Nightshade : public Plant {
private:

public:
	Nightshade(World* currentWorld, int X_coordinate, int Y_coordinate);

	void Collision(Organism* predator, Organism* prey) override;
};