#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Hub.h"
#include "Graph.h"

using namespace std;

//declare global variables
vector<Hub*> Q;
vector<Hub*> S;
double totalCost;
double finalCost = 0;
int baggage;
int ticketType;

//declare functions
void fastest(Graph G, Hub* s);
void init(Graph G, Hub* s);
void relax(Hub* u, Hub* v, Flight* flight, int index);
Hub* min(vector<Hub*> &Q);
void printRoute(Hub* source, Hub* destination);
void loadGraph(Graph &G);

int main()
{
	//load flight information
	Graph G;
	loadGraph(G);

	Hub* source = NULL;
	Hub* destination = NULL;
	totalCost = 0.0;
	char again;
	int purchaseCount = 0;

	cout << "\n\t\tWelcome to Hammoud Travel's flight booking system\n" << endl;

	do
	{
		//get source
		int sourceChoice;

		cout << "Where are you leaving from?" << endl;
		for (size_t i = 0; i < G.hubs.size(); i++)
			cout << "\t" << i + 1 << " - " << G.hubs[i]->name << endl;

		do
		{
			cin >> sourceChoice;
			if (sourceChoice < 1 || (size_t)sourceChoice > G.hubs.size())
				cout << "Invalid option, please try again." << endl;
		} while (sourceChoice < 1 || (size_t)sourceChoice > G.hubs.size());
		source = G.hubs[sourceChoice - 1];

		//get destination
		int destinationChoice;

		int j = 1;
		size_t indexOfSource;
		cout << "Where do you want to go?" << endl;
		for (size_t i = 0; i < G.hubs.size(); i++)
		{
			//exclude source from destination list
			if (G.hubs[i]->name != source->name)
			{
				cout << "\t" << j << " - " << G.hubs[i]->name << endl;
				j++;
			}
			else
				indexOfSource = i;
		}
		do
		{
			cin >> destinationChoice;
			if (destinationChoice < 1 || (size_t)destinationChoice > G.hubs.size() - 1)
				cout << "Invalid option, please try again." << endl;
		} while (destinationChoice < 1 || (size_t)destinationChoice > G.hubs.size() - 1);

		//get destination from hub list
		if (destinationChoice <= indexOfSource)
			destination = G.hubs[destinationChoice - 1];
		else
			destination = G.hubs[destinationChoice];

		//get baggage amount
		cout << "How many bags do you have?" << endl;
		do
		{
			cin >> baggage;
			if (baggage < 0)
				cout << "Invalid baggage amount. Please enter 0 or more." << endl;
		} while (baggage < 0);

		//get ticket type
		cout << "Are you looking for fastest or cheapest flight?" << endl;
		cout << "\t1 - Fastest" << endl;
		cout << "\t2 - Cheapest" << endl;
		do
		{
			cin >> ticketType;
			if (ticketType < 1 || ticketType > 2)
				cout << "Invalid option. Please enter 1 or 2." << endl;
		} while (ticketType < 1 || ticketType > 2);

		//call main algorithm
		fastest(G, source);

		//print final route
		cout << "======================================================================\n";
		cout << "\nHere is your Itinerary:\n" << endl;
		printRoute(source, destination);
		cout << "======================================================================\n";
		cout << "\t\t\t\t\t\tTotal cost is: $" << setprecision(2) << fixed << totalCost << endl;

		char buy;
		cout << "Would like to buy this ticket? (y/n)" << endl;
		cin >> buy;
		if (buy == 'y')
		{
			finalCost += totalCost;
			purchaseCount++;
		}

		totalCost = 0;


		cout << "Would you like to search for another flight? (y/n)" << endl;
		cin >> again;
		if (again == 'n')
		{
			cout << "======================================================================\n" << endl;
			cout << "\n\t\t**Final cost of " << purchaseCount << " ticket(s): $" << finalCost << "**" << endl;
			cout << "\n\n*** Have a nice day :) ***\n" << endl;
		}
	} while (again == 'y');

	for (size_t i = 0; i < G.hubs.size(); i++)
	{
		delete G.hubs[i];
	}

    return 0;
}

//modified Dijkstra's
void fastest(Graph G, Hub* s)
{
	init(G, s);

	while (Q.size() != 0)
	{
		Hub* u = min(Q);
		S.push_back(u);
		for (int i = 0; i < u->flights.size(); i++)
		{
			if (u->d->compareDates(u->flights[i]->departure) < 0)
				relax(u, u->flights[i]->destination, u->flights[i], i);
		}
	}
}

//Initialize single source
void init(Graph G, Hub* s)
{
	for (size_t i = 0; i < G.hubs.size(); i++)
	{
		G.hubs[i]->d = new Date("59/23/31/12/9999");
		G.hubs[i]->cost = 99999.99;
		G.hubs[i]->f = 0;
		G.hubs[i]->parent = NULL;
		Q.push_back(G.hubs[i]);
	}
	s->d = new Date("00/00/00/00/0000");
	s->cost = 0.0;
}

//Relax flight
void relax(Hub* u, Hub* v, Flight* flight, int index)
{
	int w = flight->duration;
	int compare = 0;
	flight->setBaggageFees(baggage);

	double flightCost = flight->source->cost + flight->price + flight->baggageFees;

	if (ticketType == 1)
	{
		Date* temp = flight->departure->addTime(w);
		compare = v->d->compareDates(temp);
	}
	else
	{
		if (v->cost > flightCost)
			compare = 1;
	}
	if (compare > 0)
	{
		v->d = flight->departure->addTime(w);
		v->cost = flightCost;
		v->parent = u;
		v->f = index;
	}
}

//Extract min and remove it from Q
Hub* min(vector<Hub*> &Q)
{
	Hub* min = Q[0];
	int minPos = 0;
	int compare = 0;
	for (int i = 1; i < Q.size(); i++)
	{
		if (ticketType == 1)
			compare = Q[i]->d->compareDates(min->d);
		else
		{
			if (Q[i]->cost < min->cost)
				compare = -1;
			else
				compare = 0;
		}
		if (compare < 0)
		{
			min = Q[i];
			minPos = i;
		}
	}
	Q.erase(Q.begin() + minPos);
	return min;
}

//Print route
void printRoute(Hub* source, Hub* destination)
{
	if (destination->parent == NULL)
	{
		cout << "We are sorry, but a flight \nto "
			<< destination->name
			<< "\nfrom " << source->name
			<< "\nis not available at this time." << endl;
		return;
	}

	vector<Flight*> route;
	Hub* iter = destination;
	Flight* flight;
	while (iter->name != source->name)
	{
		flight = iter->parent->flights[iter->f];
		totalCost += flight->price;
		totalCost += flight->baggageFees;
		route.push_back(flight);
		iter = iter->parent;
	}

	for (int i = route.size() - 1; i >= 0; i--)
		route[i]->toString();
}

//load graph
void loadGraph(Graph &G)
{
	string line, name, location;
	ifstream myfile("resources/Hub.csv");

	//Loads all the Hubs
	if (myfile.is_open())
	{
		//Below function will read until next comma ',' in same line and store that string in 'value' variable and print
		while (getline(myfile, line))// Omit the Caption Line.
		{
			while (getline(myfile, name, ','))//Get every value in order.
			{
				getline(myfile, location, '\n');
				Hub* hub = new Hub(name, location);
				G.addHub(hub);
			}
		}
		myfile.close();
	}
	else { cout << "Unable to open file"; }

	string flightNum, company, source, destination, time, temp;
	double price;
	int duration;
	Hub* sourceHub = NULL;
	Hub* destinationHub = NULL;
	vector<Flight> allFlights;
	ifstream myfile2("resources/Flight.csv");

	//loads all the Flights
	if (myfile2.is_open())
	{
		//Below function will read until next comma ',' in same line and store that string in 'value' variable and print
		while (getline(myfile2, line))// Omit the Caption Line.
		{
			while (getline(myfile2, flightNum, ','))//Get every value in order.
			{
				getline(myfile2, temp, ',');	// get the price
				price = atof(temp.c_str());	// convert to double

				getline(myfile2, source, ',');	//get source airport
				getline(myfile2, destination, ',');	//get destination airport

				getline(myfile2, time, ',');	//get departure time as a string

				getline(myfile2, temp, ',');	//get duration
				duration = atoi(temp.c_str());	//convert to int

				getline(myfile2, company, '\n');	//get company

				for (size_t i = 0; i < G.hubs.size(); i++)
				{
					if (G.hubs[i]->name == source)
						sourceHub = G.hubs[i];
					if (G.hubs[i]->name == destination)
						destinationHub = G.hubs[i];
				}

				//Flight* newFlight = new Flight(flightNum, price, sourceHub, destinationHub, time, duration, company);

				sourceHub->addFlight(flightNum, price, destinationHub, time, duration, company);
			}
		}
		myfile2.close();
	}
	else { cout << "Unable to open file"; }
}