#pragma once
#include "Animal.h"

class Antelope : public Animal {

public:
	Antelope(World* currentWorld, int X_coordinate, int Y_coordinate);

	void Move() override;
	void Collision(Organism* predator, Organism* prey) override;
};

