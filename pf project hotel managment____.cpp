#include <iostream>
#include <string>
using namespace std;

// Global variables
int totalRooms;        // Total number of rooms
int totalCustomers;    // Maximum customers at a time
int totalMenuItems;    // Number of food items

// Room data
int *roomNumbers;
string *roomTypes;
float *roomPrices;
bool *roomStatus;

// Customer data
string *customerNames;
string *customerContacts;
int *customerRoomNumbers;
float *customerBills;
string **customerFoodOrders;
int *customerFoodOrderCount;
int customerCount = 0;     // Keep track of number of customers

// Food menu
string *foodMenu;
float *foodPrices;

// Initialize hotel rooms
void initializeHotel() {
    cout << "Enter the number of rooms in the hotel: ";
    cin >> totalRooms;

    roomNumbers = new int[totalRooms];
    roomTypes = new string[totalRooms];
    roomPrices = new float[totalRooms];
    roomStatus = new bool[totalRooms];

    cout << "Enter room details:\n";
    for (int i = 0; i < totalRooms; i++) {
        cout << "Room " << i + 1 << " number: ";
        cin >> roomNumbers[i];
        cout << "Room " << i + 1 << " type (Single/Double): ";
        cin >> roomTypes[i];
        cout << "Room " << i + 1 << " price: ";
        cin >> roomPrices[i];
        roomStatus[i] = false;  // Initially, all rooms are available
    }

    cout << "Enter the maximum number of customers the hotel can handle: ";
    cin >> totalCustomers;

    customerNames = new string[totalCustomers];
    customerContacts = new string[totalCustomers];
    customerRoomNumbers = new int[totalCustomers];
    customerBills = new float[totalCustomers];
    customerFoodOrderCount = new int[totalCustomers];
    customerFoodOrders = new string *[totalCustomers];

    for (int i = 0; i < totalCustomers; i++) {
        customerFoodOrders[i] = new string[totalRooms];  // Each customer can order up to totalRooms items
        customerFoodOrderCount[i] = 0;
    }
}

// Initialize food menu
void initializeFoodMenu() {
    cout << "Enter the number of items in the food menu: ";
    cin >> totalMenuItems;

    foodMenu = new string[totalMenuItems];
    foodPrices = new float[totalMenuItems];

    cout << "Enter food menu details:\n";
    for (int i = 0; i < totalMenuItems; i++) {
        cout << "Food " << i + 1 << " name: ";
        cin >> foodMenu[i];
        cout << "Food " << i + 1 << " price: ";
        cin >> foodPrices[i];
    }
}

// Display available rooms
void displayAvailableRooms() {
    cout << "\nAvailable Rooms:\n";
    cout << "Room No\tType\tPrice\tStatus\n";
    for (int i = 0; i < totalRooms; i++) {
        cout << roomNumbers[i] << "\t" << roomTypes[i] << "\t" 
             << roomPrices[i] << "\t" 
             << (roomStatus[i] ? "Booked" : "Available") << endl;
    }
}

// Book a room
void bookRoom() {
    int roomNo;
    string name, contact;

    displayAvailableRooms();
    cout << "Enter room number to book: ";
    cin >> roomNo;

    int roomIndex = -1;
    for (int i = 0; i < totalRooms; i++) {
        if (roomNumbers[i] == roomNo) {
            roomIndex = i;
            break;
        }
    }

    if (roomIndex == -1 || roomStatus[roomIndex]) {
        cout << "Invalid room number or room already booked.\n";
        return;
    }

    cout << "Enter customer name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter contact number: ";
    getline(cin, contact);

    roomStatus[roomIndex] = true;
    customerNames[customerCount] = name;
    customerContacts[customerCount] = contact;
    customerRoomNumbers[customerCount] = roomNumbers[roomIndex];
    customerBills[customerCount] = roomPrices[roomIndex];
    customerCount++;

    cout << "Room " << roomNo << " has been successfully booked.\n";
}

// Display food menu
void displayFoodMenu() {
    cout << "\n--- Food Menu ---\n";
    for (int i = 0; i < totalMenuItems; i++) {
        cout << i + 1 << ". " << foodMenu[i] << " - $" << foodPrices[i] << endl;
    }
}

// Order food
void orderFood(int customerIndex) {
    displayFoodMenu();
    int choice;

    if (customerFoodOrderCount[customerIndex] >= totalMenuItems) {
        cout << "You have reached the maximum number of food orders.\n";
        return;
    }

    cout << "Enter the number of the food item to order (0 to exit): ";
    cin >> choice;

    if (choice < 1 || choice > totalMenuItems) {
        cout << "Invalid choice.\n";
        return;
    }

    customerFoodOrders[customerIndex][customerFoodOrderCount[customerIndex]] = foodMenu[choice - 1];
    customerBills[customerIndex] += foodPrices[choice - 1];
    customerFoodOrderCount[customerIndex]++;

    cout << foodMenu[choice - 1] << " has been added to your order.\n";
}

// View customer records
void viewCustomerRecords() {
    if (customerCount == 0) {
        cout << "No customer records found.\n";
        return;
    }

    cout << "\nCustomer Records:\n";
    cout << "Name\tContact\tRoom No\tTotal Bill\n";
    for (int i = 0; i < customerCount; i++) {
        cout << customerNames[i] << "\t" << customerContacts[i] 
             << "\t" << customerRoomNumbers[i] << "\t" << customerBills[i] << endl;
    }
}

// Checkout and generate bill
void checkoutCustomer() {
    int roomNo;
    cout << "Enter room number for checkout: ";
    cin >> roomNo;

    int customerIndex = -1;
    for (int i = 0; i < customerCount; i++) {
        if (customerRoomNumbers[i] == roomNo) {
            customerIndex = i;
            break;
        }
    }

    if (customerIndex == -1) {
        cout << "Invalid room number or no customer found.\n";
        return;
    }

    cout << "\n--- Final Bill ---\n";
    cout << "Customer Name: " << customerNames[customerIndex] << endl;
    cout << "Room Number: " << customerRoomNumbers[customerIndex] << endl;
    cout << "Food Orders:\n";
    for (int i = 0; i < customerFoodOrderCount[customerIndex]; i++) {
        cout << "- " << customerFoodOrders[customerIndex][i] << endl;
    }
    cout << "Total Bill: $" << customerBills[customerIndex] << endl;

    // Free the room
    for (int i = 0; i < totalRooms; i++) {
        if (roomNumbers[i] == roomNo) {
            roomStatus[i] = false;
            break;
        }
    }

    // Remove customer from records
    for (int i = customerIndex; i < customerCount - 1; i++) {
        customerNames[i] = customerNames[i + 1];
        customerContacts[i] = customerContacts[i + 1];
        customerRoomNumbers[i] = customerRoomNumbers[i + 1];
        customerBills[i] = customerBills[i + 1];
        customerFoodOrderCount[i] = customerFoodOrderCount[i + 1];
        for (int j = 0; j < totalMenuItems; j++) {
            customerFoodOrders[i][j] = customerFoodOrders[i + 1][j];
        }
    }
    customerCount--;

    cout << "Checkout complete. Thank you!\n";
}


// Cleanup dynamically allocated memory
void cleanupMemory() {
    delete[] roomNumbers;
    delete[] roomTypes;
    delete[] roomPrices;
    delete[] roomStatus;

    delete[] customerNames;
    delete[] customerContacts;
    delete[] customerRoomNumbers;
    delete[] customerBills;
    delete[] customerFoodOrderCount;

    for (int i = 0; i < totalCustomers; i++) {
        delete[] customerFoodOrders[i];
    }
    delete[] customerFoodOrders;

    delete[] foodMenu;
    delete[] foodPrices;
}
//Main Function
int main() {
    cout << "Welcome to the Hotel Management System!" << endl;

    // Initialize the hotel
    initializeHotel();
    initializeFoodMenu();

    int choice;
    do {
        cout << "\n--- Hotel Management System ---\n";
        cout << "1. Display Available Rooms\n";
        cout << "2. Book a Room\n";
        cout << "3. Order Food\n";
        cout << "4. View Customer Records\n";
        cout << "5. Checkout and Generate Bill\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayAvailableRooms();
                break;
            case 2:
                bookRoom();
                break;
            case 3:
                if (totalCustomers > 0) {
                    int customerId;
                    cout << "Enter customer index (0 to " << totalCustomers - 1 << ") to order food: ";
                    cin >> customerId;
                    if (customerId >= 0 && customerId < totalCustomers) {
                        orderFood(customerId);
                    } else {
                        cout << "Invalid customer ID.\n";
                    }
                } else {
                    cout << "No customers have booked rooms yet.\n";
                }
                break;
            case 4:
                viewCustomerRecords();
                break;
            case 5:
                checkoutCustomer();
                break;
            case 6:
                cout << "Exiting the system. Thank you!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

     // Cleanup dynamically allocated memory
     cleanupMemory();

}
