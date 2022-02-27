#include <iostream>
#include "World.h"
#include "Nightshade.h"
using namespace std;

Nightshade::Nightshade(World* currentWorld, int X_coordinate, int Y_coordinate) : Plant(currentWorld, X_coordinate, Y_coordinate, 99, 0, 'N') {

}

void Nightshade::Collision(Organism* predator, Organism* prey) {
	cout << predator->GetToken() << " eats " << prey->GetToken() << " and dies from poisoning" << endl;
	prey->GetWorld()->DelFromWorldMap(prey);
	prey->GetWorld()->DelFromOrganismList(prey);
	predator->GetWorld()->DelFromWorldMap(predator);
	predator->GetWorld()->DelFromOrganismList(predator);
	delete predator;
}