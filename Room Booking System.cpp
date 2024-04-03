#include <iostream>
#include <string>
#include<windows.h>
#include <stack>
#include <queue>
#include <list>
using namespace std;
class Room {
public:
    int roomId;
    int roomNumber;
    string roomType;
    int capacity;
    bool isBooked;
    Room(int id, int number, string type, int cap)
        : roomId(id), roomNumber(number), roomType(type), capacity(cap), isBooked(false) {}
};
class Customer {
public:
    int customerId;
    string name;
    string contactInfo;
    Room* bookedRoom;
    Customer(int id, string n, string contact)
        : customerId(id), name(n), contactInfo(contact), bookedRoom(nullptr) {}
};
class RoomManagement {
public:
    stack<Room*> availableRooms;
    queue<Room*> bookedRooms;
    list<Customer> customers;
    int roomIdCount;
    int customerIdCount;
    RoomManagement()
        : roomIdCount(1), customerIdCount(1) {}
    ~RoomManagement() {
        while (!availableRooms.empty()) {
            Room* room = availableRooms.top();
            availableRooms.pop();
            delete room;
        }
        while (!bookedRooms.empty()) {
            Room* room = bookedRooms.front();
            bookedRooms.pop();
            delete room;
        }
    }
    void addRoom(int number, string type, int capacity) {
        Room* newRoom = new Room(roomIdCount, number, type, capacity);
        availableRooms.push(newRoom);
        roomIdCount++;
        cout << "Room added successfully!" << endl;
    }void viewAvailableRooms() {
        if (availableRooms.empty()) {
            cout << "No available rooms." << endl;
            return;
        }
        cout << "Available Rooms:" << endl;
        stack<Room*> tempStack;
        while (!availableRooms.empty()) {
            Room* room = availableRooms.top();
            availableRooms.pop();
            cout << "Room ID: " << room->roomId << endl;
            cout << "Room Number: " << room->roomNumber << endl;
            cout << "Room Type: " << room->roomType << endl;
            cout << "Capacity: " << room->capacity << endl;
            cout << endl;
            tempStack.push(room);
        }
        while (!tempStack.empty()) {
            Room* room = tempStack.top();
            tempStack.pop();
            availableRooms.push(room);
        }
    }
    void viewBookedRooms() {
        if (bookedRooms.empty()) {
            cout << "No booked rooms." << endl;
            return;
        }
        cout << "Booked Rooms:" << endl;
        queue<Room*> tempQueue = bookedRooms;
        while (!tempQueue.empty()) {
            Room* room = tempQueue.front();
            tempQueue.pop();
            cout << "Room ID: " << room->roomId << endl;
            cout << "Room Number: " << room->roomNumber << endl;
            cout << "Room Type: " << room->roomType << endl;
            cout << "Capacity: " << room->capacity << endl;
            cout << endl;
        }
    }
    void bookRoom(int customerId, int roomNumber) {
        Customer* customer = getCustomerById(customerId);
        if (customer == nullptr) {
            cout << "Customer with ID " << customerId << " does not exist." << endl;
            return;
        }
        Room* room = getAvailableRoomByNumber(roomNumber);
        if (room == nullptr) {
            cout << "Room with number " << roomNumber << " is not available." << endl;
            return;
        }
        if (room->isBooked) {
            cout << "Room with number " << roomNumber << " is already booked." << endl;
            return;
        }
        room->isBooked = true;
        customer->bookedRoom = room;
        bookedRooms.push(room);
        cout << "Room booked successfully!" << endl;
    }
    void cancelBooking(int customerId) {
        Customer* customer = getCustomerById(customerId);
        if (customer == nullptr) {
            cout << "Customer with ID " << customerId << " does not exist." << endl;
            return;
        }
        Room* room = customer->bookedRoom;
        if (room == nullptr) {
            cout << "Customer with ID " << customerId << " has not booked any room." << endl;
            return;
        }
        room->isBooked = false;
        customer->bookedRoom = nullptr;
        removeRoomFromBookedRooms(room);
        cout << "Booking canceled successfully!" << endl;
    }
    void addCustomer(string name, string contactInfo) {
        Customer newCustomer(customerIdCount, name, contactInfo);
        customers.push_back(newCustomer);
        customerIdCount++;
        cout << "Customer added successfully!" << endl;
    }
    void displayCustomers() {
        if (customers.empty()) {
            cout << "No customers found." << endl;
            return;
        }
        cout << "Customers:" << endl;
        for (const auto& customer : customers) {
            cout << "Customer ID: " << customer.customerId << endl;
            cout << "Name: " << customer.name << endl;
            cout << "Contact Info: " << customer.contactInfo << endl;
            if (customer.bookedRoom != nullptr) {
                cout << "Booked Room: " << customer.bookedRoom->roomNumber << endl;
            } else {
                cout << "No booked room." << endl;
            }
            cout << endl;
        }
    }
    void searchCustomers(const string& name) {
        if (customers.empty()) {
            cout << "No customers found." << endl;
            return;
        }
        bool found = false;
        cout << "Search Results for \"" << name << "\":" << endl;
        for (const auto& customer : customers) {
            if (customer.name == name) {
                found = true;
                cout << "Customer ID: " << customer.customerId << endl;
                cout << "Name: " << customer.name << endl;
                cout << "Contact Info: " << customer.contactInfo << endl;
if (customer.bookedRoom != nullptr) {
       cout << "Booked Room: " << customer.bookedRoom->roomNumber << endl;
             } else 
      cout << "No booked room." << endl;
                }
     cout << endl;
            }
        }
        if (!found) {
            cout << "No customers found with the given name." << endl;
        }
    }
    void searchRoomByNumber(int number) {
        Room* room = getAvailableRoomByNumber(number);
        if (room == nullptr) {
            cout << "Room with number " << number << " is not available." << endl;
            return;
        }

        cout << "Room ID: " << room->roomId << endl;
        cout << "Room Number: " << room->roomNumber << endl;
        cout << "Room Type: " << room->roomType << endl;
        cout << "Capacity: " << room->capacity << endl;
        cout << endl;
    }
    void editRoomDetails(int roomId, int number, string type, int capacity) {
        Room* room = getAvailableRoomById(roomId);
        if (room == nullptr) {
            cout << "Room with ID " << roomId << " is not available." << endl;
            return;
        }
        room->roomNumber = number;
        room->roomType = type;
        room->capacity = capacity;
        cout << "Room details updated successfully!" << endl;
    }
    void editCustomerDetails(int customerId, string name, string contactInfo) {
        Customer* customer = getCustomerById(customerId);
        if (customer == nullptr) {
            cout << "Customer with ID " << customerId << " does not exist." << endl;
            return;
        }
        customer->name = name;
        customer->contactInfo = contactInfo;
        cout << "Customer details updated successfully!" << endl;
    }
void viewBookingHistory(int customerId) {
        Customer* customer = getCustomerById(customerId);
        if (customer == nullptr) {
            cout << "Customer with ID " << customerId << " does not exist." << endl;
            return;
       }
        cout << "Booking History for Customer ID: " << customer->customerId << endl;
        if (customer->bookedRoom == nullptr) {
            cout << "No booking history found." << endl;
            return;
        }

        cout << "Room ID: " << customer->bookedRoom->roomId << endl;
        cout << "Room Number: " << customer->bookedRoom->roomNumber << endl;
        cout << "Room Type: " << customer->bookedRoom->roomType << endl;
        cout << "Capacity: " << customer->bookedRoom->capacity << endl;
    }
private:
        Room* getAvailableRoomByNumber(int number) {
        stack<Room*> tempStack;
        Room* result = nullptr;
        while (!availableRooms.empty()) {
            Room* room = availableRooms.top();
            availableRooms.pop();
            if (room->roomNumber == number) {
                result = room;
            }
            tempStack.push(room);
        }
        while (!tempStack.empty()) {
            Room* room = tempStack.top();
            tempStack.pop();
            availableRooms.push(room);
        }
      return result;
    }
    Room* getAvailableRoomById(int roomId) {
        stack<Room*> tempStack;
        Room* result = nullptr;
        while (!availableRooms.empty()) {
            Room* room = availableRooms.top();
            availableRooms.pop();
            if (room->roomId == roomId) {
                result = room;
            }
            tempStack.push(room);
        }
        while (!tempStack.empty()) {
            Room* room = tempStack.top();
            tempStack.pop();
            availableRooms.push(room);
        }
return result;
    }Customer* getCustomerById(int customerId) {
        for (auto&customer : customers) {
            if (customer.customerId == customerId) {
                return &customer;
            }
        }
        return nullptr;
    }
void removeRoomFromBookedRooms(Room* room) {
        queue<Room*> tempQueue;
        while (!bookedRooms.empty()) {
        Room* r = bookedRooms.front();
        bookedRooms.pop();

            if (r != room) {
                tempQueue.push(r);
            }
        }
 bookedRooms = tempQueue;
    } 
};
int main() {
    RoomManagement roomManagement;
int choice;
    do {
       cout << "\t\t\t==============================================" << endl;
        cout << "\t\t\t>>>>>>>>>ROOM BOOKING SYSTEM <<<<<<<<<<<" <<endl;
        cout << "\t\t\t==============================================" << endl;
       cout<<"\n\t\t\t------------------------------------------------";
        cout<<"\n\t\t\tENTER   1:   Add a Rooms";                               
        cout<<"\n\t\t\t------------------------------------------------";
        cout<<"\n\t\t\tENTER   2:   View Available Rooms";
        cout<<"\n\t\t\t------------------------------------------------";
        cout<<"\n\t\t\tENTER   3:   View Booked Rooms";;
        cout<<"\n\t\t\t------------------------------------------------";
        cout<<"\n\t\t\tENTER   4:   Book a Room";
        cout<<"\n\t\t\t------------------------------------------------";
       cout<<"\n\t\t\tENTER   5:   Cancel Booking";
        cout<<"\n\t\t\t------------------------------------------------";
        cout<<"\n\t\t\tENTER   6:   Add a Customer"; 
        cout<<"\n\t\t\t------------------------------------------------";
        cout<<"\n\t\t\tENTER   7:   Diaplay All Customer's details'";
        cout<<"\n\t\t\t------------------------------------------------";
        cout<<"\n\t\t\tENTER   8:   Search Customer by Name";
        cout<<"\n\t\t\t------------------------------------------------";
        cout<<"\n\t\t\tENTER   9:   Search Room By Number";
        cout<<"\n\t\t\t------------------------------------------------";
        cout<<"\n\t\t\tENTER   10:   Edit Room Details";
        cout<<"\n\t\t\t------------------------------------------------";
        cout<<"\n\t\t\tENTER   11:   Edit Customer Details";
        cout<<"\n\t\t\t------------------------------------------------";
        cout<<"\n\t\t\tENTER   12:   View Booking History";
        cout<<"\n\t\t\t------------------------------------------------";
        cout<<"\n\t\t\tENTER   0:   To Exit";
        cout<<"\n\t\t\t------------------------------------------------";
        cout<<"\n\n\t\t\t   Please Enter Your Choice: ";
        
        cin >> choice;
        cout << endl;
        system("CLS");
switch (choice) {
           case 0:
                cout << "Exiting program..." << endl;
	   exit(0);
                break;
           case 1: {
                int number, capacity;
                string type;
                cout << "Enter Room Number: ";
                cin >> number;
                cout << "Enter Room Type: ";
                cin >> type;
                cout << "Enter Room Capacity: ";
                cin >> capacity;
                roomManagement.addRoom(number, type, capacity);
                break;
           }
           case 2:
                roomManagement.viewAvailableRooms();
                break;
           case 3:
                roomManagement.viewBookedRooms();
                break;
           case 4: {
                int customerId, roomNumber;
                cout << "Enter Customer ID: ";
                cin >> customerId;
                cout << "Enter Room Number: ";
                cin >> roomNumber;
                roomManagement.bookRoom(customerId, roomNumber);
                break;
           }
   case 5: {
                int customerId;
                cout << "Enter Customer ID: ";
                cin >> customerId;
                roomManagement.cancelBooking(customerId);
                break;
	    }
case 6: {
                string name, contactInfo;
                cout << "Enter Customer Name: ";
                cin >> name;
                cout << "Enter Customer Contact Info: ";
                cin >> contactInfo;
                roomManagement.addCustomer(name, contactInfo);
                break;
           }
           case 7:
                roomManagement.displayCustomers();
                break;
           case 8: {
                string name;
                cout << "Enter Customer Name: ";
                cin >> name;
                roomManagement.searchCustomers(name);
                break;
           	   }
  case 9: {
                int number;
                cout << "Enter Room Number: ";
                cin >> number;
                roomManagement.searchRoomByNumber(number);
                break;
                }
  case 10: {
                int roomId, number, capacity;
                string type;
                cout << "Enter Room ID: ";
                cin >> roomId;
                cout << "Enter Room Number: ";
                cin >> number;
                cout << "Enter Room Type: ";
                cin >> type;
                cout << "Enter Room Capacity: ";
                cin >> capacity;
                roomManagement.editRoomDetails(roomId, number, type, capacity);
                break;
           }           
	    case 11: {
                int customerId;
                string name, contactInfo;
                cout << "Enter Customer ID: ";
                cin >> customerId;
                cout << "Enter Customer Name: ";
                cin >> name;
                cout << "Enter Customer Contact Info: ";
                cin >> contactInfo;
                roomManagement.editCustomerDetails(customerId, name, contactInfo);
                break;
		    }
	case 12: {
                int customerId;
                cout << "Enter Customer ID: ";
                cin >> customerId;
                roomManagement.viewBookingHistory(customerId);
                break;
		    }
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
        cout << endl;
    } while (choice != 0);

    return 0;
}
