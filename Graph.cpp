#include "Graph.h"

void Graph::addHub(Hub* hub)
{
	hubs.push_back(hub);
}

void Graph::printGraph()
{
	for (size_t i = 0; i < hubs.size(); i++)
		hubs[i]->printFlights();
}