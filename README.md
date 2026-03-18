# ParkNexus - A Parking Management System

## Description

*ParkNexus* is a multi level parking lot management system implemented in C++ using various data structures such as Linked Lists, Queues, Stacks, and Hash Tables. The system allows users to manage parking slots, check vehicles in and out, search for vehicles, view parking history, and save/load data from files.

## Features

- **Check-In**: Park a vehicle in an available slot.
- **Check-Out**: Remove a vehicle from a slot and record the checkout time.
- **Display Slots**: Show the current status of all parking slots.
- **Search Vehicle**: Check if a vehicle is parked and its location.
- **View Parking History**: Display the history of checked-out vehicles.
- **Save & Exit**: Save the current state to a file and exit the program.

## Data Structures Used

- **Linked List**: For managing parking slots.
- **Queue**: For handling waiting vehicles when slots are full.
- **Stack**: For storing parking history.
- **Hash Table**: For quick search of vehicles (with chaining for collision handling).

## Prerequisites

- C++ Compiler
- VS Code (or any other editor)

## Compilation and Execution

1. Compile the program using the following command:
   
   ```bash
   g++ -o parking main.cpp parking.cpp
   ```

2. Run the executable:
   
   ```bash
   ./parking
   ```

Note: On Windows, you may need to use a MinGW or similar environment for g++, and run `parking.exe` instead of `./parking`.

## Usage

- Run the program and follow the on-screen menu to perform operations.
- The system supports multiple levels and slots per level (configurable in the code).

## File Structure

- `main.cpp`: Contains the main function and menu loop.
- `parking.cpp`: Implementation of the ParkingLot class and related data structures.
- `parking.h`: Header file with class definitions and ANSI color codes for console output.
- `parking.dat`: Record of all parking vehicles goes here.

## Saving and Loading Data

- The system saves the parking lot state to a file upon exit (option 6).
- Data is loaded automatically when the program starts (if a save file exists).

## Author

- Muhammad Hassan - F24608010
- Muhammad Rehan Muddassir Ranjha - F24608041
- Muhammad Hassan Khawaja - F24608030