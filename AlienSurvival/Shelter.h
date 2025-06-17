#pragma once
#include "Data.h"
class Shelter
{
private:
	bool _isOccupied;
	Position _pos;
public:
	Shelter();
	~Shelter();
	void SetPosition(Position);
	Position GetPosition();
	void SetIsOccupied(bool);
	bool GetIsOccupied();
};

