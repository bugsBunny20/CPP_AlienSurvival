#pragma once
#include "Data.h"
class Cell
{
private:
	Position _pos;
	bool _isAlienPresent;
	EntityType _entityType;

public:
	Cell(Position, EntityType);
	~Cell();
	void SetEntity(EntityType);
	bool IsEmpty();
	void SetIsAlienPresent(bool);
	bool GetIsAlienPresent();
	EntityType GetEntity();

};