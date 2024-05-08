#include <iostream>
#include <fstream>
using namespace std;

void addStudent()
{
    ofstream f("paras.txt", ios::app);
    string rn, name, div, add;
    cout << "Enter Roll No:" << endl;
    cin >> rn;
    cout << "Enter Name:" << endl;
    cin >> name;
    cout << "Enter Division:" << endl;
    cin >> div;
    cout << "Enter Address" << endl;
    cin >> add;

    f << rn << "\n"
      << name << "\n"
      << div << "\n"
      << add << endl;
    f.close();
    cout << "Data added succesfully!";
}

void deleteStudent()
{
    ifstream fin("paras.txt");
    ofstream fout("temp.txt");

    string rollNumberToDelete;
    cout << "Enter Roll No to Delete:" << endl;
    cin >> rollNumberToDelete;

    bool found = false;
    string line;
    while (getline(fin, line))
    {
        if (line.find(rollNumberToDelete) != string::npos)
        {
            // Skip the lines corresponding to the student to be deleted
            for (int i = 0; i < 3; ++i) {
                if (!getline(fin, line)) break; // In case the file ends unexpectedly
            }
            cout << "Student with Roll No " << rollNumberToDelete << " deleted successfully!" << endl;
            found = true;
            continue;
        }
        fout << line << endl;
    }

    fin.close();
    fout.close();

    if (!found)
    {
        cout << "Student with Roll No " << rollNumberToDelete << " not found!" << endl;
    }
    else
    {
        remove("paras.txt"); // Delete the original file
        rename("temp.txt", "paras.txt"); // Rename the temporary file to original
    }
}
void searchStudent()
{
    ifstream f("paras.txt");
    string line;
    string rn;
    cout << "Enter Roll No to Search:" << endl;
    cin >> rn;

    bool found = false;
    while (getline(f, line))
        if (line.find(rn) != string::npos)
        {
            cout << "Search Found!" << endl;
            cout << "Student Details:" << endl;
            cout << "Roll No: " << line << endl;
            getline(f, line);
            cout << "Name: " << line << endl;
            found = true;
            break;
        }
    f.close();

    if (!found)
    {
        cout << "student doesn't Exist!" << endl;
    }
}

void printStudent()
{
    ifstream f("paras.txt");
    string line;
    cout << "\nPrinting File Data.." << endl;
    while (getline(f, line))
    {
        cout << line << endl;
    }
    cout << "print Complete\n";
    f.close();
}

int main()
{
    int ip = 0;
    while (ip != 5)
    {
        cout << "\nEnter your choice\n1. Add student\n2. Delete Student\n3. Search Student\n4. Print Data\n5. Exit\n---->";
        cin >> ip;
        switch (ip)
        {
        case 1:
            addStudent();
            break;
        case 2:
            deleteStudent();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            printStudent();
            break;
        case 5:
            return 0;
            break;
        default:
            cout << "Re Enter your choice!!";
            break;
        }
    }
    return 0;
}
