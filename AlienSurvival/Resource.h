#pragma once
#include "Data.h"

enum class ResourceEnergyByType {
	Food = 10,
	Water = 5,
	Minerals = 3
};

class Resource
{
private:
	ResourceType _resourceType;
	int _resourceEnergy;
	bool _isOwned;
	bool _isActive;
	bool _isUpdated;
	Position _pos;

private:
	void SetResourceEnergy();

public:
	Resource(ResourceType);
	~Resource();

	void SetIsOwned(bool);
	bool GetIsOwned();

	bool GetIsActive();

	void SetIsUpdated(bool);
	bool GetIsUpdated();

	void SetPosition(Position);
	Position GetPosition();

	int GetResourceEnergy();
	void ResourceAmountConsumed(int);
	ResourceType GetResourceType();
};