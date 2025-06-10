Overview
This C++ program is a simple Hotel Management System that allows hotel staff to manage room bookings, customer records, and food orders. The system provides a menu-driven interface for various operations including room booking, food ordering, customer record viewing, and checkout.

Features
Room Management

Initialize hotel rooms with numbers, types, and prices

Display available rooms with their status (booked/available)

Book rooms for customers

Customer Management

Add new customers with their personal details

View all customer records

Checkout customers and generate bills

Food Ordering

Initialize a food menu with items and prices

Display food menu to customers

Add food items to customer orders

Calculate total bill including room charges and food orders

Data Management

Uses dynamic memory allocation for all data storage

Proper memory cleanup on exit

How to Use
Initial Setup

Run the program

Enter the number of rooms in the hotel and their details

Set the maximum number of customers the hotel can handle

Initialize the food menu with items and prices

Main Menu Options

1. Display Available Rooms: Shows all rooms with their current status

2. Book a Room: Allows booking an available room for a new customer

3. Order Food: Lets a customer order food items from the menu

4. View Customer Records: Displays all current customer information

5. Checkout and Generate Bill: Processes customer checkout and displays final bill

6. Exit: Closes the program

Technical Details
Data Structures: Uses dynamic arrays to store:

Room information (numbers, types, prices, status)

Customer information (names, contacts, room assignments, bills)

Food menu items and prices

Customer food orders

Memory Management:

Allocates memory dynamically for all data structures

Includes a cleanup function to free all allocated memory before exit

Limitations
The system uses simple arrays and doesn't persist data between runs

Customer identification is based on array indices which might be confusing

No input validation for data types (e.g., entering letters where numbers are expected)

Limited error handling for edge cases

Future Improvements
Add file I/O to save data between program runs

Implement proper customer IDs instead of array indices

Add more robust input validation

Include date tracking for bookings

Add room service and other hotel amenities

Implement a search function for customers/rooms

Requirements
C++ compiler (supports C++11 or later)

Standard Library headers: <iostream>, <string>

How to Compile and Run
Save the code to a file (e.g., hotel_management.cpp)

Compile with: g++ hotel_management.cpp -o hotel

Run with: ./hotel (Linux/Mac) or hotel.exe (Windows)

Author
[Your Name]

License
This project is open-source and available for educational purposes
