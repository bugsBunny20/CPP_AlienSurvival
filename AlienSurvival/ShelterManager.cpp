#include "ShelterManager.h"

ShelterManager::ShelterManager(int numberOfShelters) :
	_numberOfShelters(numberOfShelters)
{
}

ShelterManager::~ShelterManager()
{
}

void ShelterManager::InitializeShelters()
{
	for (int i = 0; i < _numberOfShelters; i++) {
		_shelters.push_back(make_shared<Shelter>());
	}
}

void ShelterManager::SetSheltersOnGrid(shared_ptr<EnvironmentGrid> grid)
{
	for (int i = 0; i < _numberOfShelters; i++)
	{
		Position position;
		do {
			position.x = (rand() % grid->GetSizeX()) + 1;
			position.y = (rand() % grid->GetSizeY()) + 1;

		} while (!grid->SetShelters(position, _shelters[i]));
	}
}

weak_ptr<Shelter> ShelterManager::GetShelterFromGrid(Position pos, int range)
{
	weak_ptr<Shelter> shelter;
	int distance = 0;

	for (int i = 0; i < _shelters.size(); i++)
	{
		if(!_shelters[i]->GetIsOccupied())
		{
			Position shelterPos = _shelters[i]->GetPosition();
			distance = static_cast<int>(sqrt(pow((shelterPos.x - pos.x), 2) + pow((shelterPos.y - pos.y), 2)));
			if (distance <= range)
			{
				shelter = _shelters[i];
				break;
			}
		}
	}

	return shelter;
}