#pragma once
#include<memory>
#include<vector>
#include"Alien.h"
#include "EnvironmentGrid.h"

class AlienManager
{
private:
	int _numberOfAliens;
	vector<shared_ptr<Alien>> _aliens;

public:
	AlienManager(int);
	~AlienManager();

	void InitializeAliens();
	void SetAliensOnGrid(shared_ptr<EnvironmentGrid> grid);

	void MoveAliensOnGrid(shared_ptr<EnvironmentGrid> grid);
	weak_ptr<Alien> GetTargetedAlien(Position, shared_ptr<Alien>);
	
	void PerformAction(shared_ptr<Alien>);

	void DisplayStatus();
};