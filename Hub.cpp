#include "Hub.h"

using namespace std;

Hub::Hub(string n, string loc)
{
	name = n;
	location = loc;
}

void Hub::addFlight(string n, double p, Hub* t, string de, int d, string c)
{
	Flight* newFlight;
	if (c == "Delta")
		newFlight = new Delta(n, p, this, t, de, d, c);
	else if (c == "SouthWest")
		newFlight = new SouthWest(n, p, this, t, de, d, c);
	else
		newFlight = new USAirways(n, p, this, t, de, d, c);

	flights.push_back(newFlight);
}

void Hub::printFlights()
{
	for (size_t i = 0; i < flights.size(); i++)
		flights[i]->toString();
}

Hub::~Hub()
{
	for (size_t i = 0; i < flights.size(); i++)
		delete flights[i];
}