#pragma once
#include<memory>
#include<vector>
#include"EnvironmentGrid.h"
#include "AlienManager.h"
#include "ResourceManager.h"
#include "ShelterManager.h"
#include "Data.h"

class Resource;

class GameManager
{
private:
	static GameManager* _instance;
	bool _isGameRunning;
	int _numberOfAliens;
	int _numberOfResources;
	int _numberOfShelters;
	int _simulationCurrentTurn;
	int _simulationTotalTurns;
	shared_ptr<EnvironmentGrid> _grid;
	unique_ptr<AlienManager> _alienManager;
	unique_ptr<ShelterManager> _shelterManager;
	unique_ptr<ResourceManager> _resourceManager;

private:
	GameManager(int, int, int, int);

public:
	void DisplayStatus();
	static GameManager* GetInstance(int numberOfAliens = 10, int numberOfResources = 40, int numberOfShelters = 10, int totalGameTurns = 10);
	~GameManager();

	void Intialize();
	void Run();
	bool IsGameRunning();

	weak_ptr<Resource> GetResourceFromGrid(Position);
	weak_ptr<Shelter> GetShelterFromGrid(Position, int range = 0);
};