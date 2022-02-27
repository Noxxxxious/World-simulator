#pragma once
#include "Animal.h"

class Human : public Animal {
private:
	int ShieldDuration = 0;
	int ShieldCooldown = 0;
public:
	Human(World* currentWorld, int X_coordinate, int Y_coordinate);

	bool ShieldActive();
	bool OnCooldown();
	int GetShieldDuration();
	int GetShieldCooldown();

	void SetAlzur(bool active);
	void SetCooldown(bool cooldown);
	void SetShieldDuration(int duration);
	void SetShieldCooldown(int cooldown);

	void Action() override;
	void Collision(Organism* predator, Organism* prey) override;

	~Human() override;
};
