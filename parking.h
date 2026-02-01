#ifndef PARKING_H
#define PARKING_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>
using namespace std;

// ================= ANSI Styling =================
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"
#define ITALIC  "\033[3m"
#define UNDERLINE "\033[4m"

// Enable ANSI colors in Windows PowerShell
void enableANSI();

// ================= Linked List =================
struct Slot {
    int level;
    int slotNumber;
    bool isOccupied;
    string vehicleNumber;
    Slot* next;

    Slot(int L, int n) {
        level = L;
        slotNumber = n;
        isOccupied = false;
        vehicleNumber = "";
        next = NULL;
    }
};

// ================= Queue =================
struct QueueNode {
    string vehicleNumber;
    QueueNode* next;

    QueueNode(string v) {
        vehicleNumber = v;
        next = NULL;
    }
};

class WaitingQueue {
private:
    QueueNode* front;
    QueueNode* rear;

public:
    WaitingQueue();
    void enqueue(string v);
    string dequeue();
    bool isEmpty();
    void display();
};

// ================= Stack =================
struct HistoryNode {
    string vehicleNumber;
    time_t checkoutTime;
    HistoryNode* next;

    HistoryNode(string v) {
        vehicleNumber = v;
        checkoutTime = time(0);
        next = NULL;
    }
};

class HistoryStack {
private:
    HistoryNode* top;

public:
    HistoryStack();
    void push(string vehicle);
    void display();
};

// ================= Hash Table =================
struct HashNode {
    string key;
    HashNode* next;

    HashNode(string k) {
        key = k;
        next = NULL;
    }
};

class HashTable {
private:
    static const int SIZE = 10;
    HashNode* table[SIZE];
    int hashFunc(string key);

public:
    HashTable();
    void insert(string key);
    bool search(string key);
    void remove(string key);
};

// ================= Parking Lot =================
class ParkingLot {
private:
    WaitingQueue queue;
    HashTable ht;
    HistoryStack history;

    int totalLevels;
    int slotsPerLevel;
    Slot** levels;

    void loadingAnimation(const string& msg);

public:
    ParkingLot(int l, int s);

    void checkIn();
    void checkOut();
    void showSlots();
    void searchVehicle();
    void showHistory();

    void saveToFile();
    void loadFromFile();
};

#endif
