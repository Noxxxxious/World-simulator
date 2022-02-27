#include<iostream>
#include<time.h>
#include "World.h"
#include "Tortoise.h"
using namespace std;

Tortoise::Tortoise(World* currentWorld, int X_coordinate, int Y_coordinate) : Animal(currentWorld, X_coordinate, Y_coordinate, 2, 1, 'T') {

}

void Tortoise::Action() {
	if (this->GetAge() == 0)
		return;
	int move = rand() % 4;
	if (move == 3)
		Move();
}
void Tortoise::Collision(Organism* predator, Organism* prey) {
	if (predator->GetToken() != prey->GetToken()) {
		if (predator->GetStrength() > 5) {
			cout << predator->GetToken() << " attacks " << prey->GetToken() << " on x: " << prey->GetX() << " y: " << prey->GetY() << endl;
			predator->ChangeLocation(prey->GetX(), prey->GetY());
			this->GetWorld()->DelFromWorldMap(prey);
			this->GetWorld()->DelFromOrganismList(prey);
			predator->Draw();
		}
		else
			cout << prey->GetToken() << " defends attack from " << predator->GetToken() << endl;
	}
	else {
		if (predator->GetAge() > 3 && prey->GetAge() > 3)
			this->currentWorld->GiveBirth(predator);
	}
}