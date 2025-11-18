#pragma once
#include <iostream>
#include <string>
using namespace std;

class Flight {
private:
    string flightno;
    string origin;
    string destination;
    string deptime;
    string arrivaltime;

public:
    // default constructor
    Flight(){}

    // Parameterized constructor 
    Flight(string fn, string o, string d, string dt, string at)
    {
        flightNo = fn;
        origin = o;
        destination = d;
        depTime = dt;
        arrTime = at;
    }

    // Getters : naming could be more uniform
    string getFlightNumber() const { return flightNo; }
    string getOrigin() const { return origin; }
    string getDestination() const { return destination; }
    string getDepartureTime() const { return depTime; }
    string getArrivalTime() const { return arrTime; }

    // Setters ;used mostly in Admin.
    void setFlightDetails(string fn, string o, string d, string dt, string at)
    {
        flightNo = fn;
        origin = o;
        destination = d;
        depTime = dt;
        arrTime = at;
    }

    void setDepartureTime(string t)
    {
        depTime = t;
    }

    void setArrivalTime(string t)
    {
        arrTime = t;
    }

    // Displays flight info 
    void display() const
    {
        cout << "Flight: " << flightNo
            << " | From: " << origin
            << " | To: " << destination
            << " | Departure: " << depTime
            << " | Arrival: " << arrTime
            << endl;
    }

};

