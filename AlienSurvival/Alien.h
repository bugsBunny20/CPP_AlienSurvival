#pragma once
#include<memory>
#include<vector>
#include"Data.h"
#include"Resource.h"
#include "Shelter.h"

class Alien
{
private:
	const int _maxEnergy =150;
	const int _maxHealth=125;
	const int _minHealth=25;

	int _id;
	int _health;
	int _energy;
	int _energyMultiplerForRun;
	int _damagePower;
	int _moveSpeed;
	int _range;
	int _numberOfDirections;
	Direction _currentDirection;
	Position _pos;
	bool _isSheltered;
	bool _isShelterInRange;
	AlienState _currentState;
	std::vector <std::weak_ptr<Resource>> _ownedResources;

private:
	bool ShouldAttack();
	int ClampValue(int value, int minSize, int maxSize);

public:
	Alien(int id, int health, int energy, int damagePower);
	~Alien();

	void SetPosition(Position);
	Position GetPosition();
	Position GetNewPosition(int,int);

	int GetCurrentDirection();
	void SetCurrentDirection();
	void RevertCurrentDirection();

	void SetIsShelterInRange(bool isShelterInRange);

	int GetSpeed();
	int GetRange();

	void SetCurrentState(AlienState);
	AlienState GetAlienState();

	void GatherResources(std::weak_ptr<Resource>);
	void ConsumeEnergy(int energyConsumed);
	void RunToShelter(shared_ptr<Shelter>);
	void Regenerate();
	void Attack(shared_ptr<Alien>);
	void TakeDamage(int damge);
	bool IsSheltered();
	bool IsAlive();

	void DisplayStatus();
};