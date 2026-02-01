#include "parking.h"
#include <windows.h>

/* ===== Enable ANSI ===== */
void enableANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD mode = 0;
    if (!GetConsoleMode(hOut, &mode)) return;

    mode |= 0x0004;
    SetConsoleMode(hOut, mode);
}

/* ===== Queue ===== */
WaitingQueue::WaitingQueue() {
    front = rear = NULL;
}

void WaitingQueue::enqueue(string v) {
    QueueNode* temp = new QueueNode(v);
    if (!rear) front = rear = temp;
    else {
        rear->next = temp;
        rear = temp;
    }
}

string WaitingQueue::dequeue() {
    if (!front) return "";
    QueueNode* temp = front;
    string v = temp->vehicleNumber;
    front = front->next;
    if (!front) rear = NULL;
    delete temp;
    return v;
}

bool WaitingQueue::isEmpty() {
    return front == NULL;
}

void WaitingQueue::display() {
    cout << CYAN << "Waiting Queue: " << RESET;
    if (!front) {
        cout << "[Empty]\n";
        return;
    }
    QueueNode* temp = front;
    while (temp) {
        cout << temp->vehicleNumber << " ";
        temp = temp->next;
    }
    cout << endl;
}

/* ===== Stack ===== */
HistoryStack::HistoryStack() {
    top = NULL;
}

void HistoryStack::push(string vehicle) {
    HistoryNode* node = new HistoryNode(vehicle);
    node->next = top;
    top = node;
}

void HistoryStack::display() {
    if (!top) {
        cout << YELLOW << "No parking history.\n" << RESET;
        return;
    }
    HistoryNode* temp = top;
    while (temp) {
        cout << GREEN << temp->vehicleNumber << RESET
             << " | " << ctime(&temp->checkoutTime);
        temp = temp->next;
    }
}

/* ===== Hash Table ===== */
HashTable::HashTable() {
    for (int i = 0; i < SIZE; i++) table[i] = NULL;
}

int HashTable::hashFunc(string key) {
    int sum = 0;
    for (char c : key) sum += c;
    return sum % SIZE;
}

bool HashTable::search(string key) {
    int idx = hashFunc(key);
    HashNode* temp = table[idx];
    while (temp) {
        if (temp->key == key) return true;
        temp = temp->next;
    }
    return false;
}

void HashTable::insert(string key) {
    if (search(key)) return;
    int idx = hashFunc(key);
    HashNode* node = new HashNode(key);
    node->next = table[idx];
    table[idx] = node;
}

void HashTable::remove(string key) {
    int idx = hashFunc(key);
    HashNode* temp = table[idx];
    HashNode* prev = NULL;

    while (temp) {
        if (temp->key == key) {
            if (prev) prev->next = temp->next;
            else table[idx] = temp->next;
            delete temp;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

/* ===== Parking Lot ===== */
ParkingLot::ParkingLot(int l, int s) {
    totalLevels = l;
    slotsPerLevel = s;
    levels = new Slot*[totalLevels];

    for (int L = 0; L < totalLevels; L++) {
        levels[L] = NULL;
        for (int i = 1; i <= slotsPerLevel; i++) {
            Slot* slot = new Slot(L + 1, i);
            slot->next = levels[L];
            levels[L] = slot;
        }
    }
    loadFromFile();
}

void ParkingLot::loadingAnimation(const string& msg) {
    cout << CYAN << msg;
    for (int i = 0; i < 5; i++) {
        cout << ".";
        Sleep(250);
    }
    cout << RESET << endl;
}

void ParkingLot::checkIn() {
    string vehicle;
    cout << "Enter vehicle number: ";
    cin >> vehicle;

    if (ht.search(vehicle)) {
        cout << RED << "Duplicate vehicle!\n" << RESET;
        return;
    }

    loadingAnimation("Checking in");

    for (int L = 0; L < totalLevels; L++) {
        Slot* temp = levels[L];
        while (temp) {
            if (!temp->isOccupied) {
                temp->isOccupied = true;
                temp->vehicleNumber = vehicle;
                ht.insert(vehicle);
                cout << GREEN << "Parked at Level "
                     << temp->level << ", Slot "
                     << temp->slotNumber << RESET << endl;
                return;
            }
            temp = temp->next;
        }
    }

    cout << YELLOW << "Parking full! Added to queue.\n" << RESET;
    queue.enqueue(vehicle);
}

void ParkingLot::checkOut() {
    string vehicle;
    cout << "Enter vehicle number: ";
    cin >> vehicle;

    loadingAnimation("Checking out");

    for (int L = 0; L < totalLevels; L++) {
        Slot* temp = levels[L];
        while (temp) {
            if (temp->isOccupied && temp->vehicleNumber == vehicle) {
                cout << YELLOW << "Vehicle removed from Level "
                     << temp->level << ", Slot "
                     << temp->slotNumber << RESET << endl;
                temp->isOccupied = false;
                temp->vehicleNumber = "";
                ht.remove(vehicle);
                history.push(vehicle);

                if (!queue.isEmpty()) {
                    string next = queue.dequeue();
                    temp->isOccupied = true;
                    temp->vehicleNumber = next;
                    ht.insert(next);
                }
                cout << GREEN << "Assigned waiting vehicle: " << temp->vehicleNumber << RESET << endl;
                return;
            }
            temp = temp->next;
        }
    }
    cout << RED << "Vehicle not found.\n" << RESET;
}

void ParkingLot::showSlots() {
    cout << BOLD << BLUE << "\n=== Parking Status ===\n" << RESET;
    for (int L = 0; L < totalLevels; L++) {
        cout << BOLD << "\n--- Level " << L + 1 << " ---\n" << RESET;
        Slot* temp = levels[L];
        while (temp) {
            cout << "Slot " << temp->slotNumber << ": ";
            if (temp->isOccupied)
                cout << RED << "Occupied (" << temp->vehicleNumber << ")" << RESET << endl;
            else
                cout << GREEN << "Free" << RESET << endl;
            temp = temp->next;
        }
    }
    queue.display();
}

void ParkingLot::searchVehicle() {
    string v;
    cout << "Enter vehicle number: ";
    cin >> v;

    if (!ht.search(v)) {
        cout << RED << "Vehicle not found.\n" << RESET;
        return;
    }

    for (int L = 0; L < totalLevels; L++) {
        Slot* temp = levels[L];
        while (temp) {
            if (temp->isOccupied && temp->vehicleNumber == v) {
                cout << GREEN << "Found at Level "
                     << temp->level << ", Slot "
                     << temp->slotNumber << RESET << endl;
                return;
            }
            temp = temp->next;
        }
    }
}

void ParkingLot::showHistory() {
    history.display();
}

void ParkingLot::saveToFile() {
    ofstream out("parking.dat");
    for (int L = 0; L < totalLevels; L++) {
        Slot* temp = levels[L];
        while (temp) {
            out << temp->level << " "
                << temp->slotNumber << " "
                << temp->isOccupied;
            if (temp->isOccupied)
                out << " " << temp->vehicleNumber;
            out << endl;
            temp = temp->next;
        }
    }
    out.close();
}

void ParkingLot::loadFromFile() {
    ifstream in("parking.dat");
    if (!in) return;

    int lvl, slot;
    bool occ;
    string veh;

    while (in >> lvl >> slot >> occ) {
        Slot* temp = levels[lvl - 1];
        if (occ) in >> veh;
        while (temp) {
            if (temp->slotNumber == slot) {
                temp->isOccupied = occ;
                temp->vehicleNumber = occ ? veh : "";
                if (occ) ht.insert(veh);
                break;
            }
            temp = temp->next;
        }
    }
    in.close();
}
