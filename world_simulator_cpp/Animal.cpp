#include <iostream>
#include "World.h"
#include "Animal.h"
#include "enumList.h"
using namespace std;

Animal::Animal(World* currentWorld, int X_coordinate, int Y_coordinate, int strength, int initiative, char token)
	:Organism(currentWorld, X_coordinate, Y_coordinate, strength, initiative, token) {
}

bool Animal::IsAnimal() {
	return true;
}

void Animal::Action() {
	if (this->GetAge() == 0)
		return;
	Move();
}
void Animal::Collision(Organism* predator, Organism* prey) {
	if (predator->GetToken() != prey->GetToken()) {
		cout << predator->GetToken() << " attacks " << prey->GetToken() << " on x: " << prey->GetX() << " y: " << prey->GetY() << endl;
		if (prey->GetStrength() > predator->GetStrength()) {
			this->GetWorld()->DelFromWorldMap(predator);
			this->GetWorld()->DelFromOrganismList(predator);
			delete predator;
		}
		else {
			predator->ChangeLocation(prey->GetX(), prey->GetY());
			this->GetWorld()->DelFromWorldMap(prey);
			this->GetWorld()->DelFromOrganismList(prey);
			predator->Draw();
		}
	}
	else {
		if (predator->GetAge() > 3 && prey->GetAge() > 3)
			this->currentWorld->GiveBirth(predator);
	}
}
void Animal::Move() {
	bool LegalMove = false;
	int x, y;
	while (!LegalMove) {
		x = 0;
		y = 0;
		int direction = rand() % 4;
		if (direction == DOWN) {
			y++;
			if (!currentWorld->IsOutsideBorder(x + GetX(), y + GetY()))
				LegalMove = true;
		}
		else if (direction == RIGHT) {
			x++;
			if (!currentWorld->IsOutsideBorder(x + GetX(), y + GetY()))
				LegalMove = true;
		}
		else if (direction == UP) {
			y--;
			if (!currentWorld->IsOutsideBorder(x + GetX(), y + GetY()))
				LegalMove = true;
		}
		else {
			x--;
			if (!currentWorld->IsOutsideBorder(x + GetX(), y + GetY()))
				LegalMove = true;
		}
		if (LegalMove) {
			if (this->currentWorld->IsFieldOccupied(x + this->GetX(), y + this->GetY())){
				this->currentWorld->GetField(x + this->GetX(), y + this->GetY())->Collision(this, this->currentWorld->GetField(x + this->GetX(), y + this->GetY()));
			}
			else {
				ChangeLocation(x + GetX(), y + GetY());
				cout << this->GetToken() << " moves to x: " << this->GetX() << " y: " << this->GetY() << endl;
			}	
		}
	}

}

Animal::~Animal() {

}
