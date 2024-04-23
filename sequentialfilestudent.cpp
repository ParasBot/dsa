#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

void addStudent() {
    ofstream outFile("students.txt", ios::app);
    if (!outFile) {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    int rollNumber;
    char name[50];
    char division;
    char address[100];

    cout << "Enter Roll Number: ";
    cin >> rollNumber;
    cout << "Enter Name: ";
    cin.ignore(); // Ignore newline character left in the input buffer
    cin.getline(name, 50);
    cout << "Enter Division: ";
    cin >> division;
    cout << "Enter Address: ";
    cin.ignore(); // Ignore newline character left in the input buffer
    cin.getline(address, 100);
    
    outFile << rollNumber << endl;
    outFile << name << endl;
    outFile << division << endl;
    outFile << address << endl;
    outFile.close();
    cout << "Student record added successfully." << endl;
}

void deleteStudent() {
    // To be implemented
}

void displayStudent() {
    ifstream inFile("students.txt");
    if (!inFile) {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    int rollNumber;
    char name[50];
    char division;
    char address[100];

    while (inFile >> rollNumber) {
        inFile.ignore(); // Ignore newline character left in the input buffer
        inFile.getline(name, 50);
        inFile >> division;
        inFile.ignore(); // Ignore newline character left in the input buffer
        inFile.getline(address, 100);

        cout << "Roll Number: " << rollNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Division: " << division << endl;
        cout << "Address: " << address << endl;
        cout << "------------------------" << endl;
    }

    inFile.close();
}

void searchStudent() {
    ifstream inFile("students.txt");
    if (!inFile) {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    int rollNumber;
    cout << "Enter Roll Number to search: ";
    cin >> rollNumber;

    int foundRollNumber;
    char name[50];
    char division;
    char address[100];
    bool found = false;

    while (inFile >> foundRollNumber) {
        inFile.ignore(); // Ignore newline character left in the input buffer
        inFile.getline(name, 50);
        inFile >> division;
        inFile.ignore(); // Ignore newline character left in the input buffer
        inFile.getline(address, 100);

        if (foundRollNumber == rollNumber) {
            cout << "Roll Number: " << foundRollNumber << endl;
            cout << "Name: " << name << endl;
            cout << "Division: " << division << endl;
            cout << "Address: " << address << endl;
            cout << "------------------------" << endl;
            found = true;
            break; 
        }
    }

    if (!found) {
        cout << "Student with Roll Number " << rollNumber << " not found." << endl;
    }

    inFile.close();
}

int main() {
    int choice;
    do {
        cout << "\n***** MENU *****" << endl;
        cout << "1. Add Student Record" << endl;
        cout << "2. Delete Student Record" << endl;
        cout << "3. Display Student Record" << endl;
        cout << "4. Search Student Record" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                displayStudent();
                break;
            case 4:
                searchStudent();
                break;
            case 5:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    } while (choice != 5);

    return 0;
}
