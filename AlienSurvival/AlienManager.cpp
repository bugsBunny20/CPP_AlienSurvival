#include "AlienManager.h"
#include "GameManager.h"

AlienManager::AlienManager(int numberOfAliens) :
	_numberOfAliens(numberOfAliens)
{
}

AlienManager::~AlienManager()
{
}

void AlienManager::InitializeAliens()
{
	for (int i = 0; i < _numberOfAliens; i++)
	{
		_aliens.push_back(make_shared<Alien>(i + 1, 100, 100, 10));
	}
}

void AlienManager::SetAliensOnGrid(shared_ptr<EnvironmentGrid> grid)
{
	for (int i = 0; i < _numberOfAliens; i++)
	{
		Position position;
		do
		{
			position.x = (rand() % grid->GetSizeX()) + 1;
			position.y = (rand() % grid->GetSizeY()) + 1;

		} while (!grid->SetAlien(position, _aliens[i]));
	}
}

void AlienManager::MoveAliensOnGrid(shared_ptr<EnvironmentGrid> grid)
{
	for (int i = 0; i < _numberOfAliens; i++)
	{
		grid->MoveAlien(_aliens[i]);

		PerformAction(_aliens[i]);
	}
}

weak_ptr<Alien> AlienManager::GetTargetedAlien(Position pos, shared_ptr<Alien> attackingAlien)
{
	weak_ptr<Alien> alien;
	for (int i = 0; i < _numberOfAliens; i++)
	{
		if (_aliens[i]->GetPosition() == pos && attackingAlien != _aliens[i])
		{
			alien = _aliens[i];
			return alien;
		}
	}
	return weak_ptr<Alien>();
}

void AlienManager::PerformAction(shared_ptr<Alien> alien)
{
	alien->ConsumeEnergy(alien->GetSpeed());

	switch (alien->GetAlienState())
	{
	case AlienState::Sheltered:
	{
		alien->Regenerate();
		break;
	}

	case AlienState::Attack:
	{
		shared_ptr<Alien> targetAlien = GetTargetedAlien(alien->GetPosition(), alien).lock();
		alien->Attack(targetAlien);
		break;
	}

	case AlienState::GatherResources:
	{
		shared_ptr<Resource> resource = GameManager::GetInstance()->GetResourceFromGrid(alien->GetPosition()).lock();
		alien->GatherResources(resource);
		break;
	}
	}
}

void AlienManager::DisplayStatus()
{
	for (int i = 0; i < _numberOfAliens; i++)
	{
		_aliens[i]->DisplayStatus();
	}
}