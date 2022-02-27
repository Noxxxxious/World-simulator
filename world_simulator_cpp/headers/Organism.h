#pragma once
class World;

class Organism {
private:
	int strength;
	int initiative;
	int age = 0;
	int X_coordinate;
	int Y_coordinate;
	char token;
protected:
	World* currentWorld;
public:
	Organism(World* currentWorld, int X_coordinate, int Y_coordinate, int strength, int initiative, char token);

	virtual void Action() = 0;
	virtual void Collision(Organism* predator, Organism* prey) = 0;
	void Draw();
	void ChangeLocation(int X_coordinate, int Y_coordinate);
	virtual bool IsAnimal() = 0;

	int GetStrength() const;
	int GetInitiative() const;
	int GetAge() const;
	int GetX() const;
	int GetY() const;
	char GetToken() const;
	World* GetWorld() const;

	void SetStrength(int strength);
	void SetInitiative(int initiative);
	void SetAge(int age);
	void SetPosition(int X_coordinate, int Y_coordinate);
	void SetWorld(World* world);
	
	virtual ~Organism();
};