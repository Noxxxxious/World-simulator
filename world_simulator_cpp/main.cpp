#include "World.h"
#include "Organism.h"
#include<iostream>
#include <conio.h>
using namespace std;
int main() {
	cout << "VIRTUAL WORLD SIMULATOR" << endl << "AUTHOR: Michal Wrzosek 184608" << endl;
	cout << "Enter map dimensions" << endl;
	int height = 0, width = 0;
	while (!(height > 5) || !(width > 5)) {
		cout << "Height: ";
		cin >> height;
		cout << "Widht: ";
		cin >> width;
		if (!(height > 5) || !(width > 5))
			cout << "Given dimensions not allowed, both have to be greater than 5" << endl;
	}
	World* world = new World(width, height);
	world->DrawInfo();
	cout << "Press any key to start playing" << endl;
	_getch();
	while (world->GetHumanAlive()) {
		world->Draw();
		world->Play();
	}
	cout << "You died";
}