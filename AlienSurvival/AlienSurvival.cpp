#include <iostream>
#include "GameManager.h"

int main()
{
	std::cout << "************Alien survival simulation************\n";
	int numberOfAliens = 10;
	int numberOfResources = 20;
	int numberOfShelters = 20;
	int simulationTotalTurns = 10;

	GameManager::GetInstance(numberOfAliens, numberOfResources, numberOfShelters, simulationTotalTurns)->Intialize();
	GameManager::GetInstance()->Run();
	delete GameManager::GetInstance();
}