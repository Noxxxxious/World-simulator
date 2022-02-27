#pragma once
#include "Plant.h"

class Hogweed : public Plant {
private:

public:
	Hogweed(World* currentWorld, int X_coordinate, int Y_coordinate);

	void Action() override;
	void Collision(Organism* predator, Organism* prey) override;
};