#include<iostream>
#include <time.h>
#include "World.h"
using namespace std;

World::World(int width, int height) {
	srand(time(NULL));
	this->width = width;
	this->height = height;
	this->round = 0;
	CreateMap(width, height);
	Human* human = new Human(this, this->GetWidth()/2, this->GetHeight()/2);
	GenerateOrganisms();
}
void World::CreateMap(int width, int height) {
	this->map = new Organism** [height];
	for (int i = 0; i < height; i++) {
		this->map[i] = new Organism * [width];
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			this->map[i][j] = nullptr;
	}
}

void World::SetRound(int round) {
	this->round = round;
}
void World::SetField(Organism* organism, int X_coordinate, int Y_coordinate) {
	this->map[Y_coordinate][X_coordinate] = organism;
}
void World::SetHumanAlive(bool alive) {
	this->humanAlive = alive;
}

int World::GetWidth() const {
	return this->width;
}
int World::GetHeight() const {
	return this->height;
}
int World::GetRound() const {
	return this->round;
}
bool World::GetHumanAlive() {
	return this->humanAlive;
}
Organism* World::GetField(int X_coordinate, int Y_coordinate) const {
	return this->map[Y_coordinate][X_coordinate];
}
Organism*** World::GetCurrentWorld() const {
	return this->map;
}

bool World::IsOutsideBorder(int X_coordinate, int Y_coordinate) {
	if (Y_coordinate < 0 || X_coordinate < 0 || Y_coordinate >= this->GetHeight() || X_coordinate >= this->GetWidth())
		return true;
	return false;
}
bool World::IsFieldOccupied(int X_coordinate, int Y_coordinate) {
	if (this->map[Y_coordinate][X_coordinate] != nullptr)
		return true;
	return false;
}
void World::AddToWorldMap(Organism* organism) {
	this->map[organism->GetY()][organism->GetX()] = organism;
}
void World::AddToOrganismList(Organism* organism) {
	this->organismsList.push_back(organism);
}
void World::DelFromWorldMap(Organism* organism) {
	this->map[organism->GetY()][organism->GetX()] = nullptr;
}
void World::DelFromOrganismList(Organism* organism) {
	for (int i = 0; i < this->organismsList.size(); i++) {
		if (this->organismsList[i] == organism){
			this->organismsList[i] = nullptr;
			return;
		}
	}
}
void World::GiveBirth(Organism* parent) {
	bool freeSpace = false;
	int new_x = parent->GetX(), new_y = parent->GetY();
	if (!this->IsOutsideBorder(parent->GetX() - 1, parent->GetY())) {
		if (!this->IsFieldOccupied(parent->GetX() - 1, parent->GetY())) {
			new_x--;
			freeSpace = true;
		}
	}
	if (!this->IsOutsideBorder(parent->GetX() + 1, parent->GetY()) && !freeSpace) {
		if (!this->IsFieldOccupied(parent->GetX() + 1, parent->GetY())) {
			new_x++;
			freeSpace = true;
		}
	}
	if (!this->IsOutsideBorder(parent->GetX(), parent->GetY() - 1) && !freeSpace) {
		if (!this->IsFieldOccupied(parent->GetX(), parent->GetY() - 1)) {
			new_y--;
			freeSpace = true;
		}
	}
	if (!this->IsOutsideBorder(parent->GetX(), parent->GetY() + 1) && !freeSpace) {
		if (!this->IsFieldOccupied(parent->GetX(), parent->GetY() + 1)) {
			new_y++;
			freeSpace = true;
		}
	}

	if (freeSpace) {
		if (parent->GetToken() == 'W') {
			Wolf* newWolf = new Wolf(this, new_x, new_y);
		}
		else if (parent->GetToken() == 'S') {
			Sheep* newSheep = new Sheep(this, new_x, new_y);
		}
		else if (parent->GetToken() == 'F') {
			Fox* newFox = new Fox(this, new_x, new_y);
		}
		else if (parent->GetToken() == 'T') {
			Tortoise* newTortoise = new Tortoise(this, new_x, new_y);
		}
		else if (parent->GetToken() == 'A') {
			Antelope* newAntelope = new Antelope(this, new_x, new_y);
		}
		cout << "New " << parent->GetToken() << " born on x: " << new_x << " y: " << new_y << endl;
	}	
}
void World::GrowPlant(Organism* plant, int X_coordiante, int Y_coordinate) {
	if (plant->GetToken() == 'G') {
		Grass* newGrass = new Grass(this, X_coordiante, Y_coordinate);
	}
	if (plant->GetToken() == 'D') {
		Dandelion* newDandelion = new Dandelion(this, X_coordiante, Y_coordinate);
	}
	if (plant->GetToken() == 'P') {
		Guarana* newGuarana = new Guarana(this, X_coordiante, Y_coordinate);
	}
	if (plant->GetToken() == 'N') {
		Nightshade* newNightshade = new Nightshade(this, X_coordiante, Y_coordinate);
	}
	if (plant->GetToken() == 'H') {
		Hogweed* newHogweed = new Hogweed(this, X_coordiante, Y_coordinate);
	}
}

void World::GenerateOrganisms() {
	int coordinates[2];
	for (int i = 0; i < 2; i++) {
		GenerateRandomField(coordinates);
		Wolf* newWolf = new Wolf(this, coordinates[0], coordinates[1]);
	}
	for (int i = 0; i < 2; i++) {
		GenerateRandomField(coordinates);
		Sheep* newSheep = new Sheep(this, coordinates[0], coordinates[1]);
	}
	for (int i = 0; i < 2; i++) {
		GenerateRandomField(coordinates);
		Fox* newFox = new Fox(this, coordinates[0], coordinates[1]);
	}
	for (int i = 0; i < 2; i++) {
		GenerateRandomField(coordinates);
		Tortoise* newTortoise = new Tortoise(this, coordinates[0], coordinates[1]);
	}
	for (int i = 0; i < 2; i++) {
		GenerateRandomField(coordinates);
		Antelope* newAntelope = new Antelope(this, coordinates[0], coordinates[1]);
	}

	GenerateRandomField(coordinates);
	Grass* newGrass = new Grass(this, coordinates[0], coordinates[1]);
	GenerateRandomField(coordinates);
	Dandelion* newDandelion = new Dandelion(this, coordinates[0], coordinates[1]);
	GenerateRandomField(coordinates);
	Guarana* newGuarana = new Guarana(this, coordinates[0], coordinates[1]);
	GenerateRandomField(coordinates);
	Nightshade* newNightshade = new Nightshade(this, coordinates[0], coordinates[1]);
	GenerateRandomField(coordinates);
	Hogweed* newHogweed = new Hogweed(this, coordinates[0], coordinates[1]);
}
void World::GenerateRandomField(int* coordinates) {
	coordinates[0] = rand() % this->GetWidth();
	coordinates[1] = rand() % this->GetHeight();
	while (IsFieldOccupied(coordinates[0], coordinates[1])) {
		coordinates[0] = rand() % this->GetWidth();
		coordinates[1] = rand() % this->GetHeight();
	}
}

void World::DrawInfo() {
	cout << "ANIMALS: " << endl << "A - Antelope,\t F - Fox,\t S - Sheep,\t T - Tortoise,\t W - Wolf" << endl;
	cout << "PLANTS: " << endl << "D - Dandelion,\t G - Grass,\t P - Guarana,\t H - Hogweed,\t N - Nightshade" << endl;
	cout << "You are X on the map, use arrow keys to move arround." << endl;
	cout << "Press SPACE to activate your special ability - Alzur's Shield." << endl;
}
void World::Draw() {
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			if (map[i][j] == nullptr)
				cout << " _";
			else
				cout << " " << map[i][j]->GetToken();
		}
		cout << endl;
	}
	cout << endl;
}
void World::AgeAll() {
	for (int i = 0; i < this->organismsList.size(); i++)
		this->organismsList[i]->SetAge(organismsList[i]->GetAge() + 1);
}
void World::UpdateList() {
	for (int i = 0; i < this->organismsList.size(); i++) {
		if (this->organismsList[i] == nullptr) {
			this->organismsList.erase(this->organismsList.begin() + i);
			i--;
		}
	}
}
void World::SortList() {
	for (int i = 0; i < this->organismsList.size() - 1; i++) {
		for (int j = 0; j < this->organismsList.size() - i - 1; j++) {
			if (this->organismsList[j]->GetInitiative() < this->organismsList[j + 1]->GetInitiative()) {
				Organism* tmpOrganism = organismsList[j];
				organismsList[j] = organismsList[j + 1];
				organismsList[j + 1] = tmpOrganism;
			}
		}
	}
	for (int i = 0; i < this->organismsList.size() - 1; i++) {
		if ((this->organismsList[i]->GetInitiative() == this->organismsList[i+1]->GetInitiative()) 
			&& (this->organismsList[i]->GetAge() < this->organismsList[i + 1]->GetAge())) {
			Organism* tmpOrganism = organismsList[i];
			organismsList[i] = organismsList[i + 1];
			organismsList[i + 1] = tmpOrganism;
		}
	}
}
void World::Play() {
	SetRound(GetRound() + 1);
	AgeAll();
	SortList();
	for (int i = 0; i < this->organismsList.size(); i++) {
		if(this->organismsList[i] != nullptr)
			this->organismsList[i]->Action();
	}
	UpdateList();
}

World::~World(){}