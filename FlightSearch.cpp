/*
* Filename: Flight Search
* Project: Flight Search
* Programmer: Salma Rageh
* Date: 2023-04-10
* Description: This program takes informations about flights,
*			   inserts it into 2 multimaps, displays information
*			   and allows user to change information 
*/


#include <iostream>
#include <map>
#include <iterator>
#include <string>
#include <iomanip>
#include <stdio.h>

#define stringOutputLength 30

#pragma warning(disable: 4996)

using namespace std;

typedef multimap<double, pair <string, string> > fareMap;
typedef multimap<string, pair <string, double> > destinationMap;

void printByFare(fareMap map);
void printByDestination(destinationMap name);

int main()
{
	//Fare sorted multimap
	fareMap fareSort;

	//Destination sorted multimap
	destinationMap destinationSort;

	string userDestination;
	string userDate;
	double userFare = 0;

	string newDestination;
	string newDate;
	double newFare = 0;

	//Get flight information from user
	while (1)
	{
		printf("Flight Destination: ");
		getline(cin, userDestination);
		if (userDestination[0] == '.')
		{
			break;
		}

		printf("Flight Date: ");
		getline(cin, userDate);
		if (userDate[0] == '.')
		{
			break;
		}

		printf("Flight Fare: ");
		cin >> userFare;

		cin.ignore();

		//Insert flight information into multimap
		fareSort.insert(make_pair(userFare, (make_pair(userDestination, userDate))));
		destinationSort.insert(make_pair(userDestination, (make_pair(userDate, userFare))));
	}

	printByFare(fareSort);
	printByDestination(destinationSort);

	//Ask user for flight information to search
	printf("\nDestination: ");
	getline(cin, newDestination);
	printf("Date: ");
	getline(cin, newDate);


	bool flightFound = false;
	
	//Find the flight
	for (destinationMap::iterator it = destinationSort.find(newDestination), end = destinationSort.end(); it != end; ++it)
	{
		if (it->second.first == newDate)
		{
			flightFound = true;

			//Print old fare
			cout << "" << endl << "Old Fare: " << it->second.second << endl;

			//Get new fare
			printf("New Fare: ");
			cin >> newFare;

			//See if fare changed
			if (newFare != it->second.second)
			{
				fareMap::iterator b = fareSort.find(it->second.second);

				//Change fare in destination sprted multimap
				it->second.second = newFare;

				if ((b->second.first == newDestination) && (b->second.second == newDate))
				{
					//Erase fare in fare sorted multimap
					fareSort.erase(b);
				}

				//Insert flight information into multimap with new fare
				fareSort.insert(make_pair(newFare, (make_pair(newDestination, newDate))));
			}
			else
			{
				printf("\nFare is unchanged.");
			}
			break;
		}
	}

	//Flight wasn't found
	if (flightFound == false)
	{
		printf("\nFlight not found\n");
	}

	//Display both multimaps
	printByFare(fareSort);
	printByDestination(destinationSort);

	return 0;
}



/*
 * Function: printByFare()
 * Description: This function diplays the information in the fare sorted multimap.
 * Parameters:  fareMap map: a multimap of type fareMap
 * Returns: Nothing
*/

void printByFare(fareMap map)
{
	char destination[stringOutputLength];
	char date[stringOutputLength];

	printf("\nSorted by fare:\n");
	for (fareMap::const_iterator it = map.begin(), end = map.end(); it != end; ++it)
	{
		strcpy(destination, it->second.first.c_str());
		strcpy(date, it->second.second.c_str());
		printf("%-35s%-35s$%-10.2f\n", destination, date, it->first);
	}
}


/*
 * Function: printByDestination()
 * Description: This function diplays the information in the destination sorted multimap.
 * Parameters:  destinationMap name: a multimap of type destinationMap
 * Returns: Nothing
*/

void printByDestination(destinationMap name)
{
	char destination[stringOutputLength];
	char date[stringOutputLength];

	printf("\nSorted by destination:\n");
	for (destinationMap::const_iterator it = name.begin(), end = name.end(); it != end; ++it)
	{
		strcpy(destination, it->first.c_str());
		strcpy(date, it->second.first.c_str());
		printf("%-35s%-35s$%-10.2f\n", destination, date, it->second.second);
	}
}

