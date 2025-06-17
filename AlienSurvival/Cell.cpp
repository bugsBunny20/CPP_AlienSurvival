#include "Cell.h"

Cell::Cell(Position pos, EntityType entityType) :
	_pos(pos),
	_entityType(entityType)
{
}

Cell::~Cell()
{
}

void Cell::SetEntity(EntityType entityType)
{
	_entityType = entityType;
}

bool Cell::IsEmpty()
{
	if (_entityType == EntityType::Empty)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Cell::SetIsAlienPresent(bool isAlienPresent)
{
	_isAlienPresent = isAlienPresent;
}

bool Cell::GetIsAlienPresent()
{
	return _isAlienPresent;
}

EntityType Cell::GetEntity()
{
	return _entityType;
}
