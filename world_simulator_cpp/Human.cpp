#include <iostream>
#include <conio.h>
#include "World.h"
#include "Human.h"
#include "enumList.h"
using namespace std;

Human::Human(World* currentWorld, int X_coordinate, int Y_coordinate) : Animal(currentWorld, X_coordinate, Y_coordinate, 5, 4, 'X') {
	this->GetWorld()->SetHumanAlive(true);
}

bool Human::ShieldActive() {
	if (this->ShieldDuration == 0)
		return false;
	return true;
}
bool Human::OnCooldown() {
	if (this->ShieldCooldown == 0)
		return false;
	return true;
}
int Human::GetShieldDuration() {
	return this->ShieldDuration;
}
int Human::GetShieldCooldown() {
	return this->ShieldCooldown;
}

void Human::SetShieldDuration(int duration) {
	this->ShieldDuration = duration;
}
void Human::SetShieldCooldown(int cooldown) {
	this->ShieldCooldown = cooldown;
}

void Human::Action() {
	if (this->ShieldActive()) {
		this->SetShieldDuration(this->GetShieldDuration() - 1);
	}
	if (this->OnCooldown()) {
		this->SetShieldCooldown(this->GetShieldCooldown() - 1);
	}
	char move;
	bool goodKey = false;
	int new_x = this->GetX(), new_y = this->GetY();
	while (!goodKey) {
		move = _getch();
		if (move == 72 || move == 75 || move == 77 || move == 80) {
			goodKey = true;
			if (move == 72) {
				if (this->GetWorld()->IsOutsideBorder(this->GetX(), this->GetY() - 1))
					goodKey = false;
				else
					new_y--;
			}
			else if (move == 75) {
				if (this->GetWorld()->IsOutsideBorder(this->GetX() - 1, this->GetY()))
					goodKey = false;
				else
					new_x--;
			}
			else if (move == 80) {
				if (this->GetWorld()->IsOutsideBorder(this->GetX(), GetY() + 1))
					goodKey = false;
				else
					new_y++;
			}
			else if (move == 77) {
				if (this->GetWorld()->IsOutsideBorder(this->GetX() + 1, GetY()))
					goodKey = false;
				else
					new_x++;
			}
			if (goodKey == false)
				cout << "You can't move there, try different direction" << endl;
		}
		else if (move == 32) {
			if (this->OnCooldown()) {
				cout << "You can't use the shield for another " << this->GetShieldCooldown() << " rounds" << endl;
			}
			else {
				this->SetShieldDuration(5);
				this->SetShieldCooldown(10);
				cout << "Alzur's Shield activated" << endl;
			}
		}	
	}
	if (this->currentWorld->IsFieldOccupied(new_x, new_y)) {
		this->currentWorld->GetField(new_x, new_y)->Collision(this, this->currentWorld->GetField(new_x, new_y));
	}
	else {
		ChangeLocation(new_x, new_y);
		cout << this->GetToken() << " moves to x: " << new_x << " y: " << new_y << endl;
	}
}

void Human::Collision(Organism* predator, Organism* prey) {
	if (ShieldActive()) {
		bool LegalMove = false;
		int new_x, new_y;
		while (!LegalMove) {
			new_x = this->GetX();
			new_y = this->GetY();
			int direction = rand() % 4;
			if (direction == DOWN) {
				new_y++;
				if (!currentWorld->IsOutsideBorder(new_x, new_y))
					LegalMove = true;
			}
			else if (direction == RIGHT) {
				new_x++;
				if (!currentWorld->IsOutsideBorder(new_x, new_y))
					LegalMove = true;
			}
			else if (direction == UP) {
				new_y--;
				if (!currentWorld->IsOutsideBorder(new_x, new_y))
					LegalMove = true;
			}
			else {
				new_x--;
				if (!currentWorld->IsOutsideBorder(new_x, new_y))
					LegalMove = true;
			}
			if (LegalMove) {
				if (this->currentWorld->IsFieldOccupied(new_x, new_y)) {
					this->currentWorld->GetField(new_x, new_y)->Collision(predator, this->currentWorld->GetField(new_x, new_y));
				}
				else {
					predator->ChangeLocation(new_x, new_y);
					predator->Draw();
				}
			}
		}
		cout << this->GetToken() << " defends attack from " << predator->GetToken() << ". " << predator->GetToken() << " moves to x: " << predator->GetX() << " y: " << predator->GetY() << endl;
	}
	else {
		cout << predator->GetToken() << " attacks X on x: " << prey->GetX() << " y: " << prey->GetY() << endl;
		if (prey->GetStrength() > predator->GetStrength()) {
			this->GetWorld()->DelFromWorldMap(predator);
			this->GetWorld()->DelFromOrganismList(predator);
			delete predator;
		}
		else {
			this->GetWorld()->SetHumanAlive(false);
			predator->ChangeLocation(prey->GetX(), prey->GetY());
			this->GetWorld()->DelFromWorldMap(prey);
			this->GetWorld()->DelFromOrganismList(prey);
			predator->Draw();
		}
	}
}

Human::~Human() {
	currentWorld->SetHumanAlive(false);
}