#include <memory>
#include <algorithm>
#include "EnvironmentGrid.h"
#include "GameManager.h"
#include "Shelter.h"

void EnvironmentGrid::UpdateCell(Position pos, EntityType entityType, bool isAlienPresent)
{
	_grid[pos.x][pos.y]->SetEntity(entityType);
	_grid[pos.x][pos.y]->SetIsAlienPresent(isAlienPresent);
}

EnvironmentGrid::EnvironmentGrid() :
	_maxX(10),
	_maxY(10)
{
	for (int i = 0; i < _maxX; i++)
	{
		std::vector<std::unique_ptr<Cell>> cells;
		for (int j = 0; j < _maxY; j++) {
			Position pos = { i,j };
			cells.push_back(std::make_unique<Cell>(pos, EntityType::Empty));
		}
		_grid.push_back(std::move(cells));
	}
}

EnvironmentGrid::~EnvironmentGrid()
{
}

int EnvironmentGrid::GetSizeY()
{
	return _maxY - 1;
}

int EnvironmentGrid::GetSizeX()
{
	return _maxX - 1;
}

bool EnvironmentGrid::SetAlien(Position pos, std::shared_ptr<Alien> alien)
{
	if (_grid[pos.x][pos.y]->IsEmpty())
	{
		UpdateCell(pos, EntityType::Alien, true);
		alien->SetPosition(pos);
		return true;
	}
	else
	{
		return false;
	}
}

bool EnvironmentGrid::SetResource(Position pos, std::shared_ptr<Resource> resource)
{
	if (_grid[pos.x][pos.y]->IsEmpty())
	{
		UpdateCell(pos, EntityType::Resource, false);
		resource->SetPosition(pos);

		return true;
	}
	else
	{
		return false;
	}
}

bool EnvironmentGrid::SetShelters(Position pos, std::shared_ptr<Shelter> shelter)
{
	if (_grid[pos.x][pos.y]->IsEmpty())
	{
		UpdateCell(pos, EntityType::Shelter, false);
		shelter->SetPosition(pos);
		return true;
	}
	else
	{
		return false;
	}
}

void EnvironmentGrid::MoveAlien(std::shared_ptr<Alien> alien)
{
	//Get current position of alien and update cell entity to empty as alien is going to move
	Position pos = alien->GetPosition();
	EntityType updatedEntityType{};
	if (_grid[pos.x][pos.y]->GetEntity() == EntityType::Shelter) 
	{
		shared_ptr<Shelter> shelter = GameManager::GetInstance()->GetShelterFromGrid(pos).lock();
		shelter->SetIsOccupied(false);
;	}

	UpdateCell(pos, EntityType::Empty, false);

	//Update the position in temporary variable and check if any entity is present on that.
	pos = alien->GetNewPosition(_maxX - 1, _maxY - 1);

	//According to entity present set the state of alien and update the cell status
	switch (_grid[pos.x][pos.y]->GetEntity())
	{
	case EntityType::Shelter:
	{
		alien->SetCurrentState(AlienState::Sheltered);
		break;
	}
	case EntityType::Resource:
	{
		alien->SetCurrentState(AlienState::GatherResources);
		_grid[pos.x][pos.y]->SetEntity(EntityType::Alien);
		break;
	}
	case EntityType::Alien:
	{
		alien->SetCurrentState(AlienState::Attack);
		break;
	}
	default:
	{
		alien->SetCurrentState(AlienState::Walk);
		break;
	}
	}

	EntityType updatedEntityInCell{};
	updatedEntityInCell == EntityType::Shelter ?
		updatedEntityType = EntityType::Shelter : EntityType::Alien;

	UpdateCell(pos, updatedEntityType, true);

	alien->SetPosition(pos);
}