#pragma once
#include "Plant.h"

class Guarana : public Plant {
private:

public:
	Guarana(World* currentWorld, int X_coordinate, int Y_coordinate);

	void Collision(Organism* predator, Organism* prey) override;
};

