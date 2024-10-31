#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <climits>

using namespace std;

//Identifies the user's OS and clears the screen to make it neater.
void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#elif defined(__linux__) || defined(__APPLE__)
    system("clear");
#endif
}

//Reads and displays the contents of database.txt.
void readDB() {

    string line;
    ifstream db;
    db.open("database.txt");

    clearScreen();

    if (db.is_open()) {
        int i = 0;
        while (getline(db, line)) {
            i++;
            cout << i << " " << line << endl;
        }
        db.close();
    }
    else {
        cerr << "Error: File coulnd't be opened." << endl;
    }

    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();

    clearScreen();

}

//Adds one entry to database.txt
void writeDB(string name, long long int value) {

    ofstream db;
    db.open("database.txt", ios::app);

    if (db.is_open()) {
        db << name << " " << value << endl;
        db.close();
    }
    else {
        cerr << "Error: File coulnd't be opened." << endl;
    }

    clearScreen();

}

//Deletes one entry, need to improve
void deleteEntry(string name) {

    ifstream db;

    string line, entry, temp;

    db.open("database.txt");

    //Finds the line the user wants to delete
    if (db.is_open()) {

        while (getline(db, line)) {
            //Necessary to avoid creating multiple empty lines
            if (line.empty()) continue;
            //Used to read first word of a line
            istringstream iss(line);
            iss >> entry;
            if (entry != name) {
                temp += line;
                temp += "\n";
            }
        }
        cout << temp << endl;
        db.close();

    }
    else {
        cerr << "Error: File coulnd't be opened." << endl;
    }


    ofstream newdb;

    newdb.open("database.txt");

    if (newdb.is_open()) {

        newdb << temp << endl;

        newdb.close();

    }
    else {
        cerr << "Error: File coulnd't be opened." << endl;
    }

}

//Removes all the empty lines found in database.txt
void removeEmptyLine();

int main() {

    //Variables
    string entryName;
    long long int entryValue;
    char command;
    bool running = true;

    do {
        
        //Commands are displayed and input is read by the program
        cout << "Enter command\n\n"
             << "[Q] - Quit | "
             << "[N] - New Entry | "
             << "[R] - Read Entries | "
             << "[D] - Delete Entry\n" << endl;

        cin >> command;

        //Reading user input using switch case
        //User input for reading commands is just a character,
        //making it switch case convenient.
        switch (command) {

        //Quits the program
        case 'Q':
        case 'q':
            running = false;
            clearScreen();
            break;

        //Reads a string and an int and adds a new entry to db.txt
        case 'N':
        case 'n':
            cout << "Entry name: ";
            cin >> entryName;
            do {
                cout << "Entry value: ";
                cin >> entryValue;
                if (entryValue <= LLONG_MAX && entryValue >= LLONG_MIN) break;
                else cout << "Please enter a valid value." << endl;
            } while (true);
            writeDB(entryName, entryValue);
            break;

        //Reads the contents of db.txt
        case 'R':
        case 'r':
            readDB();
            break;

        //Deletes one entry 
        case 'D':
        case 'd':
            cin >> entryName;
            deleteEntry(entryName);
            break;

        //Used for wrong input
        default:
            cout << "There was an error reading your input\n" << endl;
        }

    } while (running);

    return 0;
}