#pragma once
#include<memory>
#include<vector>
#include"Shelter.h"
#include "EnvironmentGrid.h"

class ShelterManager
{
private:
	int _numberOfShelters;
	vector<shared_ptr<Shelter>> _shelters;

public:
	ShelterManager(int);
	~ShelterManager();
	void InitializeShelters();
	void SetSheltersOnGrid(shared_ptr<EnvironmentGrid> grid);
	weak_ptr<Shelter> GetShelterFromGrid(Position pos, int range = 0);
};

