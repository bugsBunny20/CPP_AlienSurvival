#pragma once
#include <iostream>
#include <vector>
#include<memory>
#include"Data.h"
#include"Cell.h"
#include"Alien.h"
#include"Resource.h"
#include"Shelter.h"

class EnvironmentGrid
{
private:
	std::vector<vector<unique_ptr<Cell>>> _grid;
	int _maxX;
	int _maxY;

private:
	void UpdateCell(Position, EntityType,bool);

public:
	EnvironmentGrid();
	~EnvironmentGrid();

	int GetSizeY();
	int GetSizeX();

	bool SetAlien(Position, std::shared_ptr<Alien>);
	bool SetResource(Position, std::shared_ptr<Resource>);
	bool SetShelters(Position, std::shared_ptr<Shelter>);

	void MoveAlien(std::shared_ptr<Alien>);
};