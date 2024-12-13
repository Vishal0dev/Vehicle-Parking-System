#include <iostream>
#include <ctime>
using namespace std;

int menu() {
    int ch;
    cout << "Press 1. If Vehicle has entered the parking.";
    cout << "\nPress 2. If Vehicle has exited the parking.";
    cout << "\nPress 3. If you want to check the total vehicles inserted.";
    cout << "\nPress 4: To close parking.";
    cout << "\nEnter the choice: ";
    cin >> ch;
    return ch;
}

int parking_size = 5;

struct parkingdetails {
    int parkingno;
    time_t entryTime;
    time_t exitTime;
    string vehicleno;
};

int main() {
    int choice;
    int allot = 0; // Parking number alloter
    parkingdetails parking[parking_size]; // Parking declaration
    int emptyparking[parking_size]; // Parking empty slots
    int vehicles = 0; // No of vehicles currently parked
    int front_ep = -1;
    int rear_ep = -1;
    //int empty = 0; // Empty spaces due to vehicle left
    int size_wait = 2; // Waiting lot size
    int waiting[size_wait]; // Vehicles waiting to enter
    int token_wait = 0; // Waiting token counter
    int front_wait = -1;
    int rear_wait = -1;

    do {
        choice = menu();
        switch (choice) {
            case 1: {
                if ((vehicles >= parking_size) && (rear_ep == -1 && front_ep == -1)) {
                    cout << "\nParking Full";
                    cout << "\nWait for some time";
                    if ((front_wait == 0 && rear_wait == size_wait - 1) || (rear_wait == front_wait - 1)) {
                        cout << "\nWaiting Lot Full.";
                        cout << "\nCome Back Another time.";
                    } else {
                        if (rear_wait == -1 && front_wait == -1) {
                            front_wait = rear_wait = 0;
                        } else if (rear_wait == size_wait - 1) {
                            rear_wait = 0;
                        } else {
                            rear_wait++;
                        }
                        token_wait++;
                        waiting[rear_wait] = token_wait;
                        cout << "\nVehicle in waiting Lot.";
                        cout << "\nToken Number : " << token_wait << "\n";
                    }
                }
                else if (vehicles < parking_size) {
                    cout << "Enter vehicle number: ";
                    cin >> parking[vehicles].vehicleno;
                    parking[vehicles].entryTime = time(0);

                    if (parking_size > allot) {
                        allot++;
                        parking[vehicles].parkingno = allot;
                    }
                    
                    cout<<"Vehicle Entered.";

                    cout << "\nVehicle Parking Number: " << parking[vehicles].parkingno;
                    cout << "\nVehicle Number: " << parking[vehicles].vehicleno;
                    cout << "\nEntry Date and Time: " << ctime(&parking[vehicles].entryTime);
                    vehicles++;
                }
                else {
                    int park = emptyparking[front_ep];
                    if (front_ep == rear_ep) {
                        front_ep = rear_ep = -1;
                    } else if (front_ep == parking_size - 1) {
                        front_ep = 0;
                    } else {
                        front_ep++;
                    }
                    cout << "Enter vehicle number: ";
                    cin >> parking[park].vehicleno;
                    parking[park].entryTime = time(0);

                    vehicles++;
                    cout << "Vehicle Parking Number: " << parking[park].parkingno;
                    cout << "Vehicle Number: " << parking[park].vehicleno;
                    cout << "Entry Date and Time: " << ctime(&parking[park].entryTime);
                }
                break;
            }

            case 2: {
                string tempno;
                cout << "Enter the vehicle that exited: ";
                cin >> tempno;
                int i = 0;
                for (i = 0; i < parking_size; i++) {
                    if (parking[i].vehicleno == tempno) {
                        cout << "Vehicle found. Exiting...\n";
                        break;
                    }
                }
                if (i >= parking_size) {
                    cout << "\nNo vehicle found with the specified number.";
                    cout << "\nPlease try again.";
                }
                else{
                    parking[i].exitTime = time(0);
                    double duration = difftime(parking[i].exitTime, parking[i].entryTime) / 60; // Time in minutes
                    cout << "Parking Number: " << parking[i].parkingno;
                    cout << "\nVehicle Number: " << parking[i].vehicleno;
                    cout << "\nEntry Time: " << ctime(&parking[i].entryTime);
                    cout << "Exit Time: " << ctime(&parking[i].exitTime);
                    
                    if (rear_ep == -1 && front_ep == -1) {
                        front_ep = rear_ep = 0;
                    } else if (rear_ep == parking_size - 1) {
                        rear_ep = 0;
                    } else {
                        rear_ep++;
                    }
                    emptyparking[rear_ep] = parking[i].parkingno;
                    parking[i].vehicleno = "";
                    //price acc to time
                    cout << "Time Parked: " << duration << " minutes";
                    if(duration<60){
                        cout<<"\nCost: $10"<<"\n";
                    }
                    else if(duration<120){
                        cout<<"\nCost: $20"<<"\n";
                    }
                    else{
                        cout<<"\nCost: $30"<<"\n";
                    }
                        
                }
                //waiting queue check
                if(front_wait==-1&&rear_wait==-1){
                    //NOTHINGGGGG
                }
                else{
                    cout<<"Waiting Vehicle Found:";
                    cout<<"\nVehicle Token Number:"<<waiting[front_wait];
                    if(front_wait==rear_wait){
                        front_wait=rear_wait=-1;
                    }
                    else if(front_wait==size_wait-1){
                        front_wait=0;
                    }
                    else{
                        front_wait++;
                    }
                    int park = emptyparking[front_ep];
                    if (front_ep == rear_ep) {
                        front_ep = rear_ep = -1;
                    } else if (front_ep == parking_size - 1) {
                        front_ep = 0;
                    } else {
                        front_ep++;
                    }
                    cout << "\nEnter vehicle number: ";
                    cin >> parking[park].vehicleno;
                    parking[park].entryTime = time(0);
                    vehicles++;
                    cout << "\nVehicle Parking Number: " << parking[park].parkingno;
                    cout << "\nVehicle Number: " << parking[park].vehicleno;
                    cout << "\nEntry Date and Time: " << ctime(&parking[park].entryTime);
                    
                }
            }
            break;
            case 3:{
                cout<<"Total vehicles inserted in parking:"<<vehicles<<"\n";
                break;
            }
            case 4:{
                cout<<"Successfully Exited.";
                break;
            }
            default:
                cout<<"Invalid Choice\nTry Again.";
                break;
        }
    } while (choice != 4);

    return 0;
}

