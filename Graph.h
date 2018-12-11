#pragma once
#include <vector>
#include "Hub.h"

class Graph
{
public:
	std::vector<Hub*> hubs;
	void addHub(Hub* hub);
	void printGraph();
};