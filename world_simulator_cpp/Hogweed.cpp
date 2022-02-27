#include <iostream>
#include "World.h"
#include "Hogweed.h"
#include "enumList.h"
using namespace std;

Hogweed::Hogweed(World* currentWorld, int X_coordinate, int Y_coordinate) : Plant(currentWorld, X_coordinate, Y_coordinate, 10, 0, 'H') {

}

void Hogweed::Action() {
	if (!this->GetWorld()->IsOutsideBorder(this->GetX() - 1, this->GetY())) {
		if (this->GetWorld()->GetField(this->GetX() - 1, this->GetY())) {
			if (this->GetWorld()->GetField(this->GetX() - 1, this->GetY())->IsAnimal()) {
				cout << this->GetToken() << " kills " << this->GetWorld()->GetField(this->GetX() - 1, this->GetY())->GetToken() << endl;
				if (this->GetWorld()->GetField(this->GetX() - 1, this->GetY())->GetToken() == 'X')
					this->GetWorld()->SetHumanAlive(false);
				this->GetWorld()->DelFromOrganismList(this->GetWorld()->GetField(this->GetX() - 1, this->GetY()));
				this->GetWorld()->DelFromWorldMap(this->GetWorld()->GetField(this->GetX() - 1, this->GetY()));
			}
		}
	}
	if (!this->GetWorld()->IsOutsideBorder(this->GetX() + 1, this->GetY())) {
		if (this->GetWorld()->GetField(this->GetX() + 1, this->GetY())) {
			if (this->GetWorld()->GetField(this->GetX() + 1, this->GetY())->IsAnimal()) {
				cout << this->GetToken() << " kills " << this->GetWorld()->GetField(this->GetX() + 1, this->GetY())->GetToken() << endl;
				if (this->GetWorld()->GetField(this->GetX() + 1, this->GetY())->GetToken() == 'X')
					this->GetWorld()->SetHumanAlive(false);
				this->GetWorld()->DelFromOrganismList(this->GetWorld()->GetField(this->GetX() + 1, this->GetY()));
				this->GetWorld()->DelFromWorldMap(this->GetWorld()->GetField(this->GetX() + 1, this->GetY()));
			}
		}
	}
	if (!this->GetWorld()->IsOutsideBorder(this->GetX(), this->GetY() - 1)) {
		if (this->GetWorld()->GetField(this->GetX(), this->GetY() - 1)) {
			if (this->GetWorld()->GetField(this->GetX(), this->GetY() - 1)->IsAnimal()) {
				cout << this->GetToken() << " kills " << this->GetWorld()->GetField(this->GetX(), this->GetY() - 1)->GetToken() << endl;
				if (this->GetWorld()->GetField(this->GetX(), this->GetY() - 1)->GetToken() == 'X')
					this->GetWorld()->SetHumanAlive(false);
				this->GetWorld()->DelFromOrganismList(this->GetWorld()->GetField(this->GetX(), this->GetY() - 1));
				this->GetWorld()->DelFromWorldMap(this->GetWorld()->GetField(this->GetX(), this->GetY() - 1));
			}
		}
	}
	if (!this->GetWorld()->IsOutsideBorder(this->GetX(), this->GetY() + 1)) {
		if (this->GetWorld()->GetField(this->GetX(), this->GetY() + 1)) {
			if (this->GetWorld()->GetField(this->GetX(), this->GetY() + 1)->IsAnimal()) {
				cout << this->GetToken() << " kills " << this->GetWorld()->GetField(this->GetX(), this->GetY() + 1)->GetToken() << endl;
				if (this->GetWorld()->GetField(this->GetX(), this->GetY() + 1)->GetToken() == 'X')
					this->GetWorld()->SetHumanAlive(false);
				this->GetWorld()->DelFromOrganismList(this->GetWorld()->GetField(this->GetX(), this->GetY() + 1));
				this->GetWorld()->DelFromWorldMap(this->GetWorld()->GetField(this->GetX(), this->GetY() + 1));
			}
		}
	}

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

void Hogweed::Collision(Organism* predator, Organism* prey) {
	cout << predator->GetToken() << " eats " << prey->GetToken() << " and dies from poisoning" << endl;
	prey->GetWorld()->DelFromWorldMap(prey);
	prey->GetWorld()->DelFromOrganismList(prey);
	predator->GetWorld()->DelFromWorldMap(predator);
	predator->GetWorld()->DelFromOrganismList(predator);
	delete predator;
}