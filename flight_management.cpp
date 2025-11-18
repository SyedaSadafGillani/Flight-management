#include <iostream>
#include <string>
#include <windows.h> 
#include "Admin.h"
#include "Client.h"

using namespace std;

inline void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
}

int mainChoice;

do
{
    cout << "\n=== MAIN MENU ===\n"
        << "1. Admin Module\n"
        << "2. Client Module\n"
        << "3. Exit\n"
        << "Enter choice: ";

    cin >> mainChoice;

    if (mainChoice == 1)
    {
        if (!admin.verifyPasscode())
        {
            continue; 
        }

        int c;

        do
        {
            cout << "\n--- Admin Menu ---\n"
                << "1. Add Flight\n"
                << "2. Modify Flight\n"
                << "3. View Flights\n"
                << "4. Back\n"
                << "Enter: ";

            cin >> c;

            switch (c)
            {
            case 1:
                admin.addFlight();
                break;

            case 2:
                admin.modifyFlight();
                break;

            case 3:
                admin.viewFlights();
                break;
            }

        } while (c != 4);
    }
    else if (mainChoice == 2)
    {
        cin.ignore();  
        string username;

        cout << "Enter your name: ";
        getline(cin, username);

        Client client(username);
        client.loadBookingsFromFile();

        int c;

        do
        {
            cout << "\n--- Client Menu ---\n"
                << "1. View All Flights\n"
                << "2. Search Flights\n"
                << "3. Book Flight\n"
                << "4. View Bookings\n"
                << "5. Cancel Booking\n"
                << "6. Save Bookings\n"
                << "7. Back\n"
                << "Enter: ";

            cin >> c;

            if (c == 1)
            {
                client.viewAllFlights(admin.getFlights(), admin.getFlightCount());
            }
            else if (c == 2)
            {
                string src, dest;
                cout << "Source: ";
                cin >> src;
                cout << "Destination: ";
                cin >> dest;

                client.searchFlights(admin.getFlights(), admin.getFlightCount(), src, dest);
            }
            else if (c == 3)
            {
                string src, dest;
                cout << "Source: ";
                cin >> src;
                cout << "Destination: ";
                cin >> dest;

                Flight* f = client.selectFlight(admin.getFlights(), admin.getFlightCount(), src, dest);

                if (f)
                    client.bookFlight(f);
                else
                    cout << "No matching flight found.\n";
            }
            else if (c == 4)
            {
                client.viewBookings();
            }
            else if (c == 5)
            {
                string id;
                cout << "Enter Flight Number: ";
                cin >> id;

                client.cancelBooking(id);
            }
            else if (c == 6)
            {
                client.saveBookingsToFile();
            }

        } while (c != 7);
    }

} while (mainChoice != 3);

admin.saveFlightsToFile();
cout << "Goodbye!\n";

return 0;
