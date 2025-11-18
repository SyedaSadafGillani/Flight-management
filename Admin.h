#pragma once
#include "Flight.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

const int MAX_FLIGHT = 50;
const string admin_code = "123";

class Admin {
private:
    Flight flights[MAX_FLIGHT];
    int flightCount;
    int extraFlightCounter = 0;

public:
    // Constructor set the count to zero.
    Admin()
    {
        totalFlights = 0;
        
    }

    // passcode checker 
    bool verifyPasscode()
    {
        string enteredCode;
        cout << "Enter admin passcode: ";
        cin >> enteredCode;

        if (enteredCode == admin_code)
        {
            cout << "Access granted. Welcome!\n";
            return true;
        }

        cout << "Wrong passcode. Please try again.\n";
        return false;   
    }

    // Add a flight .
    void addFlight()
    {
        if (totalFlights >= MAX_FLIGHT)
        {
            cout << "Oops… The flight database is full.\n";
        }

        string fnum, src, dst, dept, arrv;

        cout << "Enter Flight Number: ";
        cin >> fnum;

        cout << "Enter Origin: ";
        cin >> src;

        cout << "Enter Destination: ";
        cin >> dst;

        cout << "Enter Departure Time: ";
        cin >> dept;

        cout << "Enter Arrival Time: ";
        cin >> arrv;

        // Setting everything
        flightList[totalFlights].setFlightDetails(fnum, src, dst, dept, arrv);

        totalFlights++;
        cout << "Flight added successfully.\n";
    }

    // Modify an existing flight. 
    void modifyFlight()
    {
        string searchNum;
        cout << "Enter the flight number to modify: ";
        cin >> searchNum;

        bool foundSomething = false;

        for (int i = 0; i < totalFlights; i++)
        {
            if (flightList[i].getFlightNumber() == searchNum)
            {
                foundSomething = true;

                string newDep, newArr;
                cout << "New departure time: ";
                cin >> newDep;

                cout << "New arrival time: ";
                cin >> newArr;

                // Updating the flight times.
                flightList[i].setDepartureTime(newDep);
                flightList[i].setArrivalTime(newArr);

                cout << "Flight information updated!\n";
                break;  
                // if found the flight break here
            }
        }

        if (!foundSomething)
        {
            cout << "Sorry… Flight not found.\n";
        }
    }

    // Just show all flights 
    void viewFlights()
    {
        if (totalFlights == 0)
        {
            cout << "There are currently no flights to display.\n";
            return;
        }

        // Loop through and display them all
        for (int i = 0; i < totalFlights; i++)
        {
            flightList[i].display();
        }
    }

    // Getter for flight list 
    Flight* getFlights()
    {
        return flightList;   
    }

    // Just returns how many flights we’ve stored so far.
    int getFlightCount() const
    {
        return totalFlights;
    }

    // Save everything to a text file 
    void saveFlightsToFile()
    {
        ofstream file("flights.txt");

        if (!file)
        {
            cout << "Error opening file for writing…\n";
            return;
        }

        // Writing all flights line by line.
        for (int i = 0; i < totalFlights; i++)
        {
            file << flightList[i].getFlightNumber() << ","
                << flightList[i].getOrigin() << ","
                << flightList[i].getDestination() << ","
                << flightList[i].getDepartureTime() << ","
                << flightList[i].getArrivalTime() << "\n";
        }

        file.close();
        cout << "Flights saved into database.\n";
    }

    // Load flights from file 
    void loadFlightsFromFile()
    {
        ifstream file("flights.txt");

        if (!file)
        {
            return;
        }

        totalFlights = 0;
        string line;

        // Read each line and split it manually 
        while (getline(file, line))
        {
            int p1 = line.find(",");
            int p2 = line.find(",", p1 + 1);
            int p3 = line.find(",", p2 + 1);
            int p4 = line.find(",", p3 + 1);

            // Extract substring portions.
            string fn = line.substr(0, p1);
            string org = line.substr(p1 + 1, p2 - p1 - 1);
            string des = line.substr(p2 + 1, p3 - p2 - 1);
            string dep = line.substr(p3 + 1, p4 - p3 - 1);
            string arr = line.substr(p4 + 1);

            // Assign into array to be informed if the limit is exceed
            flightList[totalFlights++] = Flight(fn, org, des, dep, arr);
            
        }

        file.close();
    }

};
