#include<iostream>
#include<time.h>
#include "World.h"
#include "Fox.h"
#include "enumList.h"
using namespace std;

Fox::Fox(World* currentWorld, int X_coordinate, int Y_coordinate) : Animal(currentWorld, X_coordinate, Y_coordinate, 3, 7, 'F') {
	
}

void Fox::Action() {
	if (this->GetAge() == 0)
		return;
	if ((currentWorld->IsOutsideBorder(this->GetX() - 1, this->GetY()) || currentWorld->GetField(GetX() - 1, GetY())->GetStrength() > this->GetStrength())
		&& (currentWorld->IsOutsideBorder(this->GetX() + 1, this->GetY()) || currentWorld->GetField(GetX() + 1, GetY())->GetStrength() > this->GetStrength())
		&& (currentWorld->IsOutsideBorder(this->GetX(), this->GetY() - 1) || currentWorld->GetField(GetX(), GetY() - 1)->GetStrength() > this->GetStrength())
		&& (currentWorld->IsOutsideBorder(this->GetX(), this->GetY() + 1) || currentWorld->GetField(GetX(), GetY() + 1)->GetStrength() > this->GetStrength()))
		return;
	Move();
}
void Fox::Move() {
	bool LegalMove = false;
	int x, y;
	while (!LegalMove) {
		x = 0;
		y = 0;
		int direction = rand() % 4;
		if (direction == DOWN) {
			y++;
			if (!currentWorld->IsOutsideBorder(x + GetX(), y + GetY()) && currentWorld->GetField(x + GetX(), y + GetY())->GetStrength() <= this->GetStrength())
				LegalMove = true;
		}
		else if (direction == RIGHT) {
			x++;
			if (!currentWorld->IsOutsideBorder(x + GetX(), y + GetY()) && currentWorld->GetField(x + GetX(), y + GetY())->GetStrength() <= this->GetStrength())
				LegalMove = true;
		}
		else if (direction == UP) {
			y--;
			if (!currentWorld->IsOutsideBorder(x + GetX(), y + GetY()) && currentWorld->GetField(x + GetX(), y + GetY())->GetStrength() <= this->GetStrength())
				LegalMove = true;
		}
		else {
			x--;
			if (!currentWorld->IsOutsideBorder(x + GetX(), y + GetY()) && currentWorld->GetField(x + GetX(), y + GetY())->GetStrength() <= this->GetStrength())
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
