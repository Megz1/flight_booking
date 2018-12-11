#pragma once
#include <string>

class Date
{
public:
	std::string dateAsString;
	int minute;
	int hour;
	int day;
	int month;
	int year;
	Date(std::string date);

	std::string toString();
	static std::string minutesToTime(int m);
	Date* addTime(int duration);
	int compareDates(Date* other);
};