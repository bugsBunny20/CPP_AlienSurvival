#include "GameManager.h"
#include "Data.h"
#include "AlienManager.h"
#include "ResourceManager.h"
#include "EnvironmentGrid.h"
#include "ShelterManager.h"

using namespace std;
GameManager* GameManager::_instance;

GameManager::GameManager(int numberOfAliens, int numberOfResources, int numberOfShelters, int totalGameTurns) :
	_isGameRunning(true),
	_numberOfAliens(numberOfAliens),
	_numberOfResources(numberOfResources),
	_numberOfShelters(numberOfShelters),
	_simulationTotalTurns(totalGameTurns),
	_simulationCurrentTurn(1),
	_grid(make_shared<EnvironmentGrid>()),
	_alienManager(make_unique<AlienManager>(_numberOfAliens)),
	_resourceManager(make_unique<ResourceManager>(_numberOfResources)),
	_shelterManager(make_unique<ShelterManager>(_numberOfShelters))
{
}

void GameManager::DisplayStatus()
{
	std::cout << "*******Output cycle: " << _simulationCurrentTurn << "*******" << std::endl;
	_alienManager->DisplayStatus();
	_resourceManager->DisplayStatus();
	std::cout << std::endl;
}

GameManager* GameManager::GetInstance(int numberOfAliens, int numberOfResources, int numberOfShelters, int totalGameTurns)
{
	if (_instance == nullptr)
	{
		_instance = new GameManager(numberOfAliens, numberOfResources, numberOfShelters, totalGameTurns);
	}
	return _instance;
}

GameManager::~GameManager()
{
	_instance = nullptr;
}

void GameManager::Intialize()
{
	std::srand(static_cast<unsigned int>(std::time(0)));
	
	if ((_numberOfAliens + _numberOfResources + _numberOfShelters) > ((_grid->GetSizeX() * _grid->GetSizeY() - 20)))
	{
		std::cout << "Enitties exceed grid populated!!!";
		exit(404);
	}
	else
	{
		_alienManager->InitializeAliens();
		_alienManager->SetAliensOnGrid(_grid);

		_resourceManager->InitializeResources();
		_resourceManager->SetResourcesOnGrid(_grid);

		_shelterManager->InitializeShelters();
		_shelterManager->SetSheltersOnGrid(_grid);
	}
}

void GameManager::Run()
{
	do
	{
		_alienManager->MoveAliensOnGrid(_grid);
		_resourceManager->UpdateResourceStatus();
		DisplayStatus();
		_simulationCurrentTurn++;
	} while (_simulationCurrentTurn <= _simulationTotalTurns);
	_isGameRunning = false;
}

bool GameManager::IsGameRunning()
{
	return _isGameRunning;
}

weak_ptr<Resource> GameManager::GetResourceFromGrid(Position pos)
{
	return _resourceManager->GetResource(pos);
}

weak_ptr<Shelter> GameManager::GetShelterFromGrid(Position pos, int range)
{
	return _shelterManager->GetShelterFromGrid(pos, range);
}
