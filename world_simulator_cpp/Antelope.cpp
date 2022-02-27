#include<iostream>
#include<time.h>
#include "enumList.h"
#include "World.h"
#include "Antelope.h"
using namespace std;

Antelope::Antelope(World* currentWorld, int X_coordinate, int Y_coordinate) : Animal(currentWorld, X_coordinate, Y_coordinate, 4, 4, 'A') {

}

void Antelope::Collision(Organism* predator, Organism* prey) {
	if (predator->GetToken() != prey->GetToken()) {
		cout << predator->GetToken() << " attacks " << prey->GetToken() << " on x: " << prey->GetX() << " y: " << prey->GetY() << endl;
		int escape = rand() % 2;
		if (escape == 0) {
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
			predator->ChangeLocation(prey->GetX(), prey->GetY());
			predator->Draw();
			bool freeSpace = false;
			int new_x = prey->GetX(), new_y = prey->GetY();
			if (!this->currentWorld->IsOutsideBorder(prey->GetX() - 1, prey->GetY())) {
				if (!this->currentWorld->IsFieldOccupied(prey->GetX() - 1, prey->GetY())) {
					new_x--;
					freeSpace = true;
				}
			}
			if (!this->currentWorld->IsOutsideBorder(prey->GetX() + 1, prey->GetY()) && !freeSpace) {
				if (!this->currentWorld->IsFieldOccupied(prey->GetX() + 1, prey->GetY())) {
					new_x++;
					freeSpace = true;
				}
			}
			if (!this->currentWorld->IsOutsideBorder(prey->GetX(), prey->GetY() - 1) && !freeSpace) {
				if (!this->currentWorld->IsFieldOccupied(prey->GetX(), prey->GetY() - 1)) {
					new_y--;
					freeSpace = true;
				}
			}
			if (!this->currentWorld->IsOutsideBorder(prey->GetX(), prey->GetY() + 1) && !freeSpace) {
				if (!this->currentWorld->IsFieldOccupied(prey->GetX(), prey->GetY() + 1)) {
					new_y++;
					freeSpace = true;
				}
			}
			if (freeSpace) {
				prey->ChangeLocation(new_x, new_y);
				prey->Draw();
				predator->Draw();
				cout << "A escaped to x: " << prey->GetX() << " y: " << prey->GetY() << endl;
			}
		}
	}
	else {
		if (predator->GetAge() > 3 && prey->GetAge() > 3)
			this->currentWorld->GiveBirth(predator);
	}
}
void Antelope::Move() {
	bool LegalMove = false;
	int x, y;
	while (!LegalMove) {
		x = 0;
		y = 0;
		int direction = rand() % 4;
		if (direction == DOWN) {
			y += 2;
			if (!currentWorld->IsOutsideBorder(x + GetX(), y + GetY()))
				LegalMove = true;
		}
		else if (direction == RIGHT) {
			x += 2;
			if (!currentWorld->IsOutsideBorder(x + GetX(), y + GetY()))
				LegalMove = true;
		}
		else if (direction == UP) {
			y -= 2;
			if (!currentWorld->IsOutsideBorder(x + GetX(), y + GetY()))
				LegalMove = true;
		}
		else {
			x -= 2;
			if (!currentWorld->IsOutsideBorder(x + GetX(), y + GetY()))
				LegalMove = true;
		}
		if (LegalMove) {
			if (this->currentWorld->IsFieldOccupied(x + this->GetX(), y + this->GetY())) {
				this->currentWorld->GetField(x + this->GetX(), y + this->GetY())->Collision(this, this->currentWorld->GetField(x + this->GetX(), y + this->GetY()));
			}
			else {
				ChangeLocation(x + GetX(), y + GetY());
				cout << this->GetToken() << " moves to x: " << this->GetX() << " y: " << this->GetY() << endl;
			}

		}
	}
}

