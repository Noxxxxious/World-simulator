#pragma once
#include "Organism.h"

class World;
class Organism;
class Plant : public Organism {
private:

public:
	Plant(World* currentWorld, int X_coordinate, int Y_coordinate, int strength, int initiative, char token);

	bool IsAnimal() override;
	void Action() override;
	void Collision(Organism* predator, Organism* prey) override;
};