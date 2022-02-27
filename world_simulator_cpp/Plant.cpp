#include <iostream>
#include "World.h"
#include "Plant.h"
#include "enumList.h"
using namespace std;

Plant::Plant(World* currentWorld, int X_coordinate, int Y_coordinate, int strength, int initiative, char token)
	:Organism(currentWorld, X_coordinate, Y_coordinate, strength, initiative, token) {}

bool Plant::IsAnimal() {
	return false;
}

void Plant::Action() {
	if (this->GetAge() < 2)
		return;
	if ((currentWorld->IsOutsideBorder(this->GetX() - 1, this->GetY()) || currentWorld->IsFieldOccupied(this->GetX() - 1, this->GetY()))
		&& (currentWorld->IsOutsideBorder(this->GetX() + 1, this->GetY()) || currentWorld->IsFieldOccupied(this->GetX() + 1, this->GetY()))
		&& (currentWorld->IsOutsideBorder(this->GetX(), this->GetY() - 1) || currentWorld->IsFieldOccupied(this->GetX(), this->GetY() - 1))
		&& (currentWorld->IsOutsideBorder(this->GetX(), this->GetY() + 1) || currentWorld->IsFieldOccupied(this->GetX(), this->GetY() + 1)))
		return;
	int sow = rand() % 10;
	if (sow == 0) {
		int new_x = this->GetX(), new_y = this->GetY();
		bool freeSpace = false;
		while (!freeSpace) {
			int direction = rand() % 4;
			if (direction == DOWN) {
				if (!this->currentWorld->IsOutsideBorder(this->GetX(), this->GetY() + 1) && !freeSpace) {
					if (!this->currentWorld->IsFieldOccupied(this->GetX(), this->GetY() + 1)) {
						new_y++;
						freeSpace = true;
					}
				}
			}
			else if (direction == RIGHT) {
				if (!this->currentWorld->IsOutsideBorder(this->GetX() + 1, this->GetY()) && !freeSpace) {
					if (!this->currentWorld->IsFieldOccupied(this->GetX() + 1, this->GetY())) {
						new_x++;
						freeSpace = true;
					}
				}
			}
			else if (direction == UP) {
				if (!this->currentWorld->IsOutsideBorder(this->GetX(), this->GetY() - 1) && !freeSpace) {
					if (!this->currentWorld->IsFieldOccupied(this->GetX(), this->GetY() - 1)) {
						new_y--;
						freeSpace = true;
					}
				}
			}
			else {
				if (!this->currentWorld->IsOutsideBorder(this->GetX() - 1, this->GetY())) {
					if (!this->currentWorld->IsFieldOccupied(this->GetX() - 1, this->GetY())) {
						new_x--;
						freeSpace = true;
					}
				}
			}
			if (freeSpace) {
				this->GetWorld()->GrowPlant(this, new_x, new_y);
			}
		}
	}
}
void Plant::Collision(Organism* predator, Organism* prey) {
	cout << predator->GetToken() << " eats " << prey->GetToken() << endl;
	predator->ChangeLocation(prey->GetX(), prey->GetY());
	this->GetWorld()->DelFromWorldMap(prey);
	this->GetWorld()->DelFromOrganismList(prey);
	predator->Draw();
}