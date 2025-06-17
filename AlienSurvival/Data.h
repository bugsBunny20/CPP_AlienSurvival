#pragma once
#include <vector>
#include <string>
using namespace std;

enum class EntityType
{
	Empty = 0,
	Alien = 1,
	Resource = 2,
	Shelter = 3
};

enum class AlienState {
	Sheltered = 0,
	Walk = 1,
	Run = 2,
	Attack = 3,
	Dead = 4,
	GatherResources = 5
};

enum class ResourceType {
	Food = 0,
	Water = 1,
	Minerals = 2
};

struct Position {
	int x;
	int y;
	bool operator==(Position& pos) {
		if (pos.x == x && pos.y == y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

enum class Direction
{
	South = 0,
	North = 1,
	East = 2,
	West = 3

};

