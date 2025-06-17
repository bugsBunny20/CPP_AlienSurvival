#include "Shelter.h"

Shelter::Shelter() :
	_isOccupied(false)
{
}

Shelter::~Shelter()
{
}

void Shelter::SetPosition(Position pos)
{
	_pos = pos;
}

Position Shelter::GetPosition()
{
	return _pos;
}

void Shelter::SetIsOccupied(bool isOccupied)
{
	_isOccupied = isOccupied;
}

bool Shelter::GetIsOccupied()
{
	return _isOccupied;
}
