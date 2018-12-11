#pragma once
#include <string>
#include <vector>
#include "Date.h"
#include "Flight.h"

class Flight;

class Hub
{
public:
	std::string name;
	std::string location;
	Date* d;
	double cost;
	int f;
	Hub* parent;
	std::vector<Flight*> flights;

	Hub(std::string n, std::string loc);

	void addFlight(std::string n, double p, Hub* t, std::string de, int d, std::string c);
	void printFlights();

	~Hub();
};