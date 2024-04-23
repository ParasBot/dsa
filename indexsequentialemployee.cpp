#include<iostream>
#include<fstream>
using namespace std;

class Employee {
private:
    int id;
    int salary;
    char name[20];
    char designation[20];
public:
    void setdata() {
        cout << "\nEnter Employee ID :- ";
        cin >> id;
        cin.ignore(); // Clear input buffer
        cout << "Enter Employee Name :- ";
        cin.getline(name, 20);
        cout << "Enter Employee Designation :- ";
        cin.getline(designation, 20);
        cout << "Enter Employee Salary :- ";
        cin >> salary;
    }

    void display() {
        cout << "\nEmployee ID :- " << id << endl;
        cout << "Employee Name :- " << name << endl;
        cout << "Employee Designation :- " << designation << endl;
        cout << "Employee Salary :- " << salary << endl;
    }

    int get_id() {
        return id;
    }

    void serialize(ofstream& file) {
        file.write(reinterpret_cast<char*>(this), sizeof(*this));
    }

    void deserialize(ifstream& file) {
        file.read(reinterpret_cast<char*>(this), sizeof(*this));
    }
};

void write_file() {
    Employee e;
    ofstream file1("index_file.txt", ios::binary | ios::app);
    ofstream file2("Employee.txt", ios::binary | ios::app);
    e.setdata();
    e.serialize(file1);
    e.serialize(file2);
}

void read_file() {
    ifstream file1("Employee.txt", ios::binary);
    ifstream file2("index_file.txt", ios::binary);
    Employee e;
    cout << "\n\nEmployee file---->" << endl;
    while (!file1.eof()) {
        e.deserialize(file1);
        e.display();
    }
    cout << "\n\nIndex file---->" << endl;
    int num;
    while (file2.read(reinterpret_cast<char*>(&num), sizeof(num))) {
        cout << num << endl;
    }
    cout << endl << endl;
}

void search(int num, int record) {
    ifstream file1("index_file.txt", ios::binary);
    ifstream file2("Employee.txt", ios::binary);
    int id;
    bool found = false;
    Employee e;
    while (!file1.eof()) {
        file1.read(reinterpret_cast<char*>(&id), sizeof(id));
        if (id == num) {
            found = true;
            break;
        }
    }
    if (found) {
        int position = (record - 1) * sizeof(e);
        file2.seekg(position, ios::beg);
        e.deserialize(file2);
        e.display();
    }
    else {
        cout << "Employee not present in file..." << endl;
    }
}

void delete_record(int num) {
    ifstream file1("index_file.txt", ios::binary);
    ifstream file2("Employee.txt", ios::binary);
    ofstream file3("temp_index_file.txt", ios::binary | ios::app);
    ofstream file4("temp_Employee.txt", ios::binary | ios::app);
    int id;
    Employee e;
    while (!file1.eof()) {
        file1.read(reinterpret_cast<char*>(&id), sizeof(id));
        if (id != num) {
            file3.write(reinterpret_cast<char*>(&id), sizeof(id));
        }
    }
    while (!file2.eof()) {
        e.deserialize(file2);
        if (e.get_id() != num) {
            e.serialize(file4);
        }
    }
    file1.close();
    file2.close();
    file3.close();
    file4.close();
    remove("index_file.txt");
    remove("Employee.txt");
    rename("temp_index_file.txt", "index_file.txt");
    rename("temp_Employee.txt", "Employee.txt");
}

int main() {
    int ch;
    int i;
    int rec = 0;
    cout << "1.Add Employee." << endl;
    cout << "2.Display all Employee." << endl;
    cout << "3.Search Employee." << endl;
    cout << "4.Delete Employee." << endl;
    cout << "5.Exit." << endl;
    while (true) {
        cout << "\nEnter Choice:- ";
        cin >> ch;
        switch (ch) {
        case 1:
            rec++;
            write_file();
            break;
        case 2:
            read_file();
            break;
        case 3:
            cout << "\nEnter ID No.:- ";
            cin >> i;
            search(i, rec);
            break;
        case 4:
            cout << "\nEnter ID No. for Deletion :- ";
            cin >> i;
            delete_record(i);
            break;
        case 5:
            exit(0);
        default:
            break;
        }
    }
    return 0;
}
