#include <iostream>
#include <string>
#include "Organism.h"
#include "World.h"
using namespace std;

Organism::Organism(World* currentWorld, int X_coordinate, int Y_coordinate, int strength, int initiative, char token) {
	this->strength = strength;
	this->initiative = initiative;
	this->X_coordinate = X_coordinate;
	this->Y_coordinate = Y_coordinate;
	this->currentWorld = currentWorld;
	this->token = token;
	currentWorld->AddToWorldMap(this);
	currentWorld->AddToOrganismList(this);
}

int Organism::GetAge() const { 
	return this->age; 
}
int Organism::GetStrength() const { 
	if (this == nullptr)
		return 0;
	return this->strength; 
}
int Organism::GetInitiative() const { 
	return this->initiative; 
}
int Organism::GetX() const {
	return this->X_coordinate;
}
int Organism::GetY() const {
	return this->Y_coordinate;
}
char Organism::GetToken() const {
	return this->token;
}
World* Organism::GetWorld() const {
	return this->currentWorld;
}

void Organism::SetStrength(int strength) {
	this->strength = strength;
}
void Organism::SetInitiative(int initiative) {
	this->initiative = initiative;
}
void Organism::SetAge(int age) {
	this->age = age;
}
void Organism::SetPosition(int X_coordinate, int Y_coordinate) {
	this->X_coordinate = X_coordinate;
	this->Y_coordinate = Y_coordinate;
}
void Organism::SetWorld(World* world) {
	this->currentWorld = world;
}

void Organism::Draw() {
	this->currentWorld->SetField(this, X_coordinate, Y_coordinate);
}
void Organism::ChangeLocation(int X_coordinate, int Y_coordinate)
{
	currentWorld->GetCurrentWorld()[Y_coordinate][X_coordinate] = currentWorld->GetCurrentWorld()[GetY()][GetX()];
	currentWorld->GetCurrentWorld()[GetY()][GetX()] = nullptr;
	SetPosition(X_coordinate, Y_coordinate);
}
Organism::~Organism() {}