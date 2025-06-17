#pragma once
#include<memory>
#include<map>
#include "Resource.h"
#include "EnvironmentGrid.h"

using namespace std;

class ResourceManager
{
private:
	vector <string> _resourceTypes{ "Food","Water","Minerals" };

	int _numberOfResources;
	int _resourceTypeCount;
	vector<shared_ptr<Resource>> _resources;
	map<ResourceType, int> _resourceCounts;

public:
	ResourceManager(int);
	~ResourceManager();
	void InitializeResources();
	void SetResourcesOnGrid(shared_ptr<EnvironmentGrid> grid);
	weak_ptr<Resource> GetResource(Position);
	void UpdateResourceStatus();
	void DisplayStatus();
};