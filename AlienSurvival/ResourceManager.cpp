#include<iostream>
#include"ResourceManager.h"
#include"Data.h"
#include "EnvironmentGrid.h"

ResourceManager::ResourceManager(int numberOfResources) :
	_numberOfResources(numberOfResources),
	_resourceTypeCount(static_cast<int>(_resourceTypes.size()))
{
	for (int i = 0; i < _resourceTypeCount; i++)
	{
		ResourceType resourceType = (ResourceType)i;
		_resourceCounts[resourceType] = 0;
	}
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::InitializeResources()
{
	for (int i = 0; i < _numberOfResources; i++)
	{
		int randomSeed = (rand() % _resourceTypeCount);
		ResourceType resourceType = static_cast<ResourceType>(randomSeed);
		_resources.push_back(std::make_shared<Resource>(resourceType));
		_resourceCounts[resourceType]++;
	}
}

void ResourceManager::SetResourcesOnGrid(shared_ptr<EnvironmentGrid> grid)
{
	for (int i = 0; i < _numberOfResources; i++)
	{
		Position position;
		do {
			position.x = (rand() % grid->GetSizeX()) + 1;
			position.y = (rand() % grid->GetSizeY()) + 1;

		} while (!grid->SetResource(position, _resources[i]));
	}
}

weak_ptr<Resource> ResourceManager::GetResource(Position pos)
{
	weak_ptr<Resource> resource;
	for (int i = 0; i < _numberOfResources; i++)
	{
		if (_resources[i]->GetPosition() == pos && !_resources[i]->GetIsOwned())
		{
			resource = _resources[i];
			break;
		}
	}
	return resource;
}

void ResourceManager::UpdateResourceStatus()
{
	for (int i = 0; i < _resources.size(); i++) 
	{
		if(!_resources[i]->GetIsUpdated() && _resources[i]->GetResourceEnergy()<=0)
		{
			_resources[i]->SetIsUpdated(true);
			_resourceCounts[_resources[i]->GetResourceType()]--;
		}
	}
}

void ResourceManager::DisplayStatus()
{
	for (int i = 0; i < _resourceTypeCount; i++) {
		ResourceType resourceType = (ResourceType)i;
		int count = _resourceCounts[resourceType];
		cout << _resourceTypes[i] << ": " << count << " | ";
	}
	cout << endl;
}
