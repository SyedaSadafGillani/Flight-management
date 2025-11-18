#pragma once
#include "Flight.h"
#include "Booking.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_BOOKINGS = 50;

class Client {
private:
    string name;
    Flight* bookedFlights[MAX_BOOKINGS];
    int bookingCount;
    Booking bookings[MAX_BOOKINGS];
    int totalBookings;

public:
    Client(string n = "")
    {
        name = n;
        bookingCount = 0;
        totalBookings = 0;
    }

    // Simply prints all flights
    void viewAllFlights(const Flight flights[], int count)
    {
        if (count == 0)
        {
            cout << "No available flights right now.\n";
            return;
        }

        for (int i = 0; i < count; i++)
        {
            flights[i].display();
        }
    }

    // Searches for matching flights (origin + destination)
    void searchFlights(const Flight fl[], int count, string src, string dest)
    {
        bool found = false;

        for (int i = 0; i < count; i++)
        {
            if (fl[i].getOrigin() == src && fl[i].getDestination() == dest)
            {
                fl[i].display();
                found = true;
            }
        }

        if (!found)
        {
            cout << "No flights match your search.\n";
        }
    }

    // Returns the first matching flight, or nullptr if not found
    Flight* selectFlight(const Flight flights[], int count, string src, string dest)
    {
        for (int i = 0; i < count; i++)
        {
            if (flights[i].getOrigin() == src && flights[i].getDestination() == dest)
            {
                return (Flight*)&flights[i];
            }
        }

        return nullptr;
    }

    // Books a flight :stores references and booking records
    void bookFlight(Flight* f)
    {
        if (totalBookings >= MAX_BOOKINGS)
        {
            cout << "Cannot store more bookings.\n";
            return;
        }

        bookings[totalBookings] = Booking(name, f->getFlightNumber());

        bookedFlights[bookingCount] = f;

        bookingCount++;
        totalBookings++;

        cout << "Your booking is complete.\n";
    }

    // Shows user's booked flights
    void viewBookings()
    {
        if (bookingCount == 0)
        {
            cout << "You have no bookings yet.\n";
            return;
        }

        for (int i = 0; i < bookingCount; i++)
        {
            bookedFlights[i]->display();
        }
    }

    // Cancels a booking by flight number 
    void cancelBooking(string flightNumber)
    {
        bool removed = false;

        for (int i = 0; i < bookingCount; i++)
        {
            if (bookedFlights[i]->getFlightNumber() == flightNumber)
            {
                for (int j = i; j < bookingCount - 1; j++)
                {
                    bookedFlights[j] = bookedFlights[j + 1];
                }

                bookingCount--;
                removed = true;
                cout << "Your booking has been canceled.\n";
                break;
            }
        }

        if (!removed)
        {
            cout << "No booking found under that flight number.\n";
        }
    }

    // Writes all booking entries to a file
    void saveBookingsToFile()
    {
        ofstream file("bookings.txt");

        if (!file)
        {
            cout << "Problem saving bookings.\n";
            return;
        }

        for (int i = 0; i < totalBookings; i++)
        {
            bookings[i].saveToText(file);
        }

        file.close();
        cout << "Your bookings were saved.\n";
    }

    // Reads bookings from the database
    void loadBookingsFromFile()
    {
        ifstream file("bookings.txt");

        totalBookings = 0;
        bookingCount = 0;

        string line;

        while (getline(file, line))
        {
            bookings[totalBookings].loadFromText(line);
            totalBookings++;
        }

        file.close();
    }

};

    
