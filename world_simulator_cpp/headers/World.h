#pragma once
#include <vector>
#include <string>
#include "Organism.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Fox.h"
#include "Tortoise.h"
#include "Antelope.h"
#include "Grass.h"
#include "Dandelion.h"
#include "Guarana.h"
#include "Nightshade.h"
#include "Hogweed.h"
#include "Human.h"

class World {
private:
	int width;
	int height;
	int round = 0;
	bool humanAlive;
	std::vector <Organism*> organismsList;
	Organism*** map;
	int GetRound() const;
	int GetWidth() const;
	int GetHeight() const;
	void SetRound(int round);
	void AgeAll();
	void UpdateList();
	void SortList();
	void GenerateOrganisms();
	void GenerateRandomField(int* coordinates);
public:
	World(int width, int height);
	void CreateMap(int width, int height);

	void SetField(Organism* organism, int X_coordiante, int Y_coordinate);
	void SetHumanAlive(bool alive);

	bool GetHumanAlive();
	Organism* GetField(int X_coordinate, int Y_coordinate) const;
	Organism*** GetCurrentWorld() const;

	bool IsOutsideBorder(int X_coordiante, int Y_coordinate);
	bool IsFieldOccupied(int X_coordinate, int Y_coordinate);
	void AddToWorldMap(Organism* organism);
	void AddToOrganismList(Organism* organism);
	void DelFromWorldMap(Organism* organism);
	void DelFromOrganismList(Organism* organism);
	void GiveBirth(Organism* parent);
	void GrowPlant(Organism* plant, int X_coordiante, int Y_coordinate);

	void Play();
	void Draw();
	void DrawInfo();

	~World();
};