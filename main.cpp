#include "parking.h"
#include <stdexcept>
#include <limits>

int main() {
    ParkingLot lot(3, 5);

    while (true) {
        try {
            cout << BOLD << UNDERLINE << ITALIC << BLUE
                 << "\n<<< Parking Menu >>>\n" << RESET;

            cout << YELLOW
                 << "1. Check-In\n"
                 << "2. Check-Out\n"
                 << "3. Display Slots\n"
                 << "4. Search Vehicle\n"
                 << "5. View Parking History\n"
                 << "6. Save\n"
                 << "7. Exit\n"
                 << RESET;

            cout << CYAN << "Choose: " << RESET;

            int ch;
            cin >> ch;

            // Input validation
            if (cin.fail()) {
                cin.clear(); // clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Invalid input! Please enter a number.");
            }

            switch (ch) {
                case 1: lot.checkIn(); break;
                case 2: lot.checkOut(); break;
                case 3: lot.showSlots(); break;
                case 4: lot.searchVehicle(); break;
                case 5: lot.showHistory(); break;
                case 6:
                    lot.saveToFile();
                    cout << GREEN << "Data saved successfully. Exiting...\n" << RESET;
                    break;
                case 7:
                    cout << YELLOW << "Exiting. Drive safe\n" << RESET;
                    return 0;
                default:
                    throw out_of_range("Choice out of range! Select 1-7.");
            }
        }
        catch (const exception& e) {
            cout << RED << e.what() << "\n" << RESET;
        }
    }
}