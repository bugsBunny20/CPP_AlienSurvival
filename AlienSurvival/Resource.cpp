#include<iostream>
#include "Resource.h"

void Resource::SetResourceEnergy()
{
	switch (_resourceType)
	{
	case ResourceType::Food:
		_resourceEnergy = static_cast<int>(ResourceEnergyByType::Food);
		break;
	case ResourceType::Water:
		_resourceEnergy = static_cast<int>(ResourceEnergyByType::Water);
		break;
	case ResourceType::Minerals:
		_resourceEnergy = static_cast<int>(ResourceEnergyByType::Minerals);
		break;
	}
}

Resource::Resource(ResourceType resourceType) :
	_resourceType(resourceType),
	_isOwned(false),
	_isActive(true),
	_isUpdated(false)
{
	SetResourceEnergy();
}

Resource::~Resource()
{
}

void Resource::SetIsOwned(bool isOwned)
{
	_isOwned = isOwned;
}

bool Resource::GetIsOwned()
{
	return _isOwned;
}

bool Resource::GetIsActive()
{
	return _isActive;
}

void Resource::SetIsUpdated(bool isUpdated)
{
	_isUpdated = isUpdated;
}

bool Resource::GetIsUpdated()
{
	return _isUpdated;
}

int Resource::GetResourceEnergy()
{
	return _resourceEnergy;
}

void Resource::ResourceAmountConsumed(int resourceConsumed)
{
	_resourceEnergy -= resourceConsumed;
	if (_resourceEnergy <= 0) {
		_isActive = false;
	}
}

void Resource::SetPosition(Position pos)
{
	_pos = pos;
}

Position Resource::GetPosition()
{
	return _pos;
}

ResourceType Resource::GetResourceType()
{
	return _resourceType;
}
