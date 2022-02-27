#include <iostream>
#include "World.h"
#include "Dandelion.h"
using namespace std;

Dandelion::Dandelion(World* currentWorld, int X_coordinate, int Y_coordinate) : Plant(currentWorld, X_coordinate, Y_coordinate, 0, 0, 'D') {

}

void Dandelion::Action() {
	if (this->GetAge() < 3)
		return;
	for (int i = 0; i < 3; i++) {
		int sow = rand() % 10;
		if (sow == 0) {
			int new_x = this->GetX(), new_y = this->GetY();
			bool freeSpace = false;

			if (!this->currentWorld->IsOutsideBorder(this->GetX() - 1, this->GetY())) {
				if (!this->currentWorld->IsFieldOccupied(this->GetX() - 1, this->GetY())) {
					new_x--;
					freeSpace = true;
				}
			}
			if (!this->currentWorld->IsOutsideBorder(this->GetX() + 1, this->GetY()) && !freeSpace) {
				if (!this->currentWorld->IsFieldOccupied(this->GetX() + 1, this->GetY())) {
					new_x++;
					freeSpace = true;
				}
			}
			if (!this->currentWorld->IsOutsideBorder(this->GetX(), this->GetY() - 1) && !freeSpace) {
				if (!this->currentWorld->IsFieldOccupied(this->GetX(), this->GetY() - 1)) {
					new_y--;
					freeSpace = true;
				}
			}
			if (!this->currentWorld->IsOutsideBorder(this->GetX(), this->GetY() + 1) && !freeSpace) {
				if (!this->currentWorld->IsFieldOccupied(this->GetX(), this->GetY() + 1)) {
					new_y++;
					freeSpace = true;
				}
			}

			if (freeSpace) {
				this->GetWorld()->GrowPlant(this, new_x, new_y);
			}
		}
	}
}