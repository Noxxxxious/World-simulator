#pragma once
#include "Organism.h"

class Animal : public Organism {
private:

public:
	Animal(World* currentWorld, int X_coordinate, int Y_coordinate, int strength, int initiative, char token);

	bool IsAnimal() override;
	void Action() override;
	void Collision(Organism* predator, Organism* prey) override;
	virtual void Move();

	~Animal() override;
};