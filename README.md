# Flight Booking System
This is a small project I worked on one summer in my free time after taking a data structures and algorithms class at my university.

## Features
* Read in provided CSV files to get hub and flight information
* User selects departure hub, destination, number of bags and whether they wish to book the fastest or cheapest flight
* Apply Djikstra's shortest path algorithm to print itinerary based on user inputs
* User may book more than 1 flight
* Add up all ticket prices and fees (different airlines have different baggage fees)

##### To test
###### Linux
* Clone the project and move to its directory
* Run `make` to build the executable
* Run `./main.out`
* Follow the prompts

###### Windows
This project was written for Linux so running on Visual Studio may require an installation of Windows Subsystem for Llinux (WSL)
* Clone the project
* Open the solution file in Visual Studio
* Configure a connection to your WSL installation
* Run the program