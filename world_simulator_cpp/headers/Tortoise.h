#pragma once
#include "Animal.h"

class Tortoise : public Animal {

public:
	Tortoise(World* currentWorld, int X_coordinate, int Y_coordinate);

	void Action() override;
	void Collision(Organism* predator, Organism* prey) override;
};
