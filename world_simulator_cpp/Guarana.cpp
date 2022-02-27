#include <iostream>
#include "World.h"
#include "Guarana.h"
using namespace std;

Guarana::Guarana(World* currentWorld, int X_coordinate, int Y_coordinate) : Plant(currentWorld, X_coordinate, Y_coordinate, 0, 0, 'P') {

}

void Guarana::Collision(Organism* predator, Organism* prey) {
	cout << predator->GetToken() << " eats " << prey->GetToken() << ", +3 strength" << endl;
	predator->ChangeLocation(prey->GetX(), prey->GetY());
	predator->SetStrength(predator->GetStrength() + 3);
	prey->GetWorld()->DelFromWorldMap(prey);
	prey->GetWorld()->DelFromOrganismList(prey);
	predator->Draw();
}