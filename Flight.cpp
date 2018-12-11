#include <iomanip>
#include <iostream>
#include "Flight.h"

using namespace std;

Flight::Flight(string n, double p, Hub* f, Hub* t, string de, int d, string c)
{
	number = n;
	price = p;
	source = f;
	destination = t;
	departure = new Date(de);
	duration = d;
	company = c;
}

void Flight::setBaggageFees(int n)
{
	baggageFees = 0.0;
}

void Flight::toString()
{
	cout << left << setw(10) << company << " " << number << right << setw(16) << "Departure: " << departure->toString()
		<< "\nFrom: " << source->name << ", " << source->location
		<< "\nTo:   " << destination->name << ", " << destination->location
		<< "\nDuration: " << Date::minutesToTime(duration) << "\t\tArrival: " << destination->d->toString() << "\tPrice: $" << setprecision(2) << fixed << price
		<< "\n\t\t\t\t\t\t Baggage fees: $" << baggageFees << "\n\n";
}

Flight::~Flight()
{
	delete departure;
}

USAirways::USAirways(string n, double p, Hub* f, Hub* t, string de, int d, string c) : Flight(n, p, f, t, de, d, c)
{
	number = n;
	price = p;
	source = f;
	destination = t;
	departure = new Date(de);
	duration = d;
	company = c;
}

void USAirways::setBaggageFees(int n)
{
	if (n == 0)
		baggageFees = 0.0;
	else
		baggageFees = (n - 1) * 25;
}

Delta::Delta(string n, double p, Hub* f, Hub* t, string de, int d, string c) : Flight(n, p, f, t, de, d, c)
{
	number = n;
	price = p;
	source = f;
	destination = t;
	departure = new Date(de);
	duration = d;
	company = c;
}

void Delta::setBaggageFees(int n)
{
	baggageFees = 25 * n;
}

SouthWest::SouthWest(string n, double p, Hub* f, Hub* t, string de, int d, string c) : Flight(n, p, f, t, de, d, c)
{
	number = n;
	price = p;
	source = f;
	destination = t;
	departure = new Date(de);
	duration = d;
	company = c;
}

void SouthWest::setBaggageFees(int n)
{
	baggageFees = 0.0;
}