#include "Date.h"

using namespace std;

Date::Date(string date)
{
	dateAsString = date;

	int pos = date.find('/');
	minute = stoi(date.substr(0, pos));
	date.erase(0, pos + 1);

	pos = date.find('/');
	hour = stoi(date.substr(0, pos));
	date.erase(0, pos + 1);

	pos = date.find('/');
	day = stoi(date.substr(0, pos));
	date.erase(0, pos + 1);

	pos = date.find('/');
	month = stoi(date.substr(0, pos));
	date.erase(0, pos + 1);

	year = stoi(date);
}

string Date::toString()
{
	string m, h, d, mo;
	if (minute < 10)
		m = "0" + to_string(minute);
	else m = to_string(minute);
	if (hour < 10)
		h = "0" + to_string(hour);
	else h = to_string(hour);
	if (day < 10)
		d = "0" + to_string(day);
	else d = to_string(day);
	if (month < 10)
		mo = "0" + to_string(month);
	else mo = to_string(month);

	string str = "";
	str += h + ":" + m + "   " + mo + "/" + d + "/" + to_string(year);
	return str;
}

// Converts minutes to 12 hour time
string Date::minutesToTime(int m)
{
	int minutes, hours;
	hours = m / 60;
	minutes = m % 60;

	string hoursString = to_string(hours);
	if (hours < 10)
		hoursString = "0" + to_string(hours);

	string minutesString = to_string(minutes);
	if (minutes < 10)
		minutesString = "0" + to_string(minutes);

	string str = hoursString + ":" + minutesString;
	return str;
}

// Add minutes to date and returns new date
Date* Date::addTime(int duration)
{
	int hoursToAdd, minutesToAdd;
	hoursToAdd = duration / 60;
	minutesToAdd = duration % 60;

	Date* arrivalTime = new Date(dateAsString);
	arrivalTime->minute += minutesToAdd;
	arrivalTime->hour += hoursToAdd;

	if (arrivalTime->minute > 59)
	{
		arrivalTime->minute -= 60;
		arrivalTime->hour++;
	}

	if (arrivalTime->hour > 23)
	{
		arrivalTime->hour -= 24;
		arrivalTime->day++;
	}

	if ((arrivalTime->month == 1 || arrivalTime->month == 3 || arrivalTime->month == 5 || arrivalTime->month == 7
		|| arrivalTime->month == 8 || arrivalTime->month == 10 || arrivalTime->month == 12) && arrivalTime->day > 31)
	{
		arrivalTime->day -= 31;
		arrivalTime->month++;
	}
	else if ((arrivalTime->month == 4 || arrivalTime->month == 6 ||
		arrivalTime->month == 9 || arrivalTime->month == 11) && arrivalTime->day > 30)
	{
		arrivalTime->day -= 30;
		arrivalTime->month++;
	}
	else if (arrivalTime->month == 2)
	{
		if (arrivalTime->year % 4 == 0 && arrivalTime->day > 29)
		{
			arrivalTime->day -= 29;
			arrivalTime->month++;
		}
		else if (arrivalTime->year % 4 != 0 && arrivalTime->day > 28)
		{
			arrivalTime->day -= 28;
			arrivalTime->month++;
		}
	}
	if (arrivalTime->month > 12)
	{
		arrivalTime->month -= 12;
		arrivalTime->year++;
	}

	return arrivalTime;
}

// Return 1 if this is greater, -1 if less than, or 0 if equal
int Date::compareDates(Date* other)
{
	if (year == other->year)
	{
		if (month == other->month)
		{
			if (day == other->day)
			{
				if (hour == other->hour)
				{
					if (minute == other->minute)
						return 0;
					else if (minute > other->minute)
						return 1;
				}
				else if (hour > other->hour)
					return 1;
			}
			else if (day > other->day)
				return 1;
		}
		else if (month > other->month)
			return 1;
	}
	else if (year > other->year)
		return 1;
	return -1;
}