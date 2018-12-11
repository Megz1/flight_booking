#pragma once
#include <string>
#include "Hub.h"

class Hub;

class Flight
{
public:
	std::string number;
	double price;
	Hub* source;
	Hub* destination;
	Date* departure;
	int duration;
	std::string company;
	double baggageFees;

	Flight(std::string n, double p, Hub* f, Hub* t, std::string de, int d, std::string c);
	virtual void setBaggageFees(int n);
	void toString();
	~Flight();
};

class USAirways :public Flight
{
public:
	USAirways(std::string n, double p, Hub* f, Hub* t, std::string de, int d, std::string c);
	void setBaggageFees(int n);
};

class Delta :public Flight
{
public:
	Delta(std::string n, double p, Hub* f, Hub* t, std::string de, int d, std::string c);
	void setBaggageFees(int n);
};

class SouthWest :public Flight
{
public:
	SouthWest(std::string n, double p, Hub* f, Hub* t, std::string de, int d, std::string c);
	void setBaggageFees(int n);
};