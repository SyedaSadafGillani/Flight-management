#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Booking {
private:
    string clientName;
    string flightno;
    string tempNote;

public:
    // Default constructor 
    Booking() {}

    // constructor when data is already known.
    Booking(string cname, string fno)
    {
        clientName = cname;
        flightNo = fno;
    }

    // Gets (maybe rename later to be consistent with other)
    string getClientName() const
    {
        return clientName;
    }

    string getFlightNumber() const
    {
        return flightNo;
    }

    // prints to the screen 
    void display() const
    {
        cout << "Client: " << clientName
            << " | Flight: " << flightNo << endl;
    }

    // Save to text file 
    void saveToText(ofstream& file) const
    {
       
        file << clientName << "," << flightNo << "\n";
    }

   
    void loadFromText(const string& line)
    {
        int commaPos = line.find(",");

        clientName = line.substr(0, commaPos);
        flightNo = line.substr(commaPos + 1);
    }


};


