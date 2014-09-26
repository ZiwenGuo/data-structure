// grades.cpp
// CSCI 455 PA5
// Name: Hefang Li
// Loginid: hefangli
//
/*
 * A program to test the Table class.
 * How to run it:
 *      grades [hashSize]
 *
 * the optional argument hashSize is the size of hash table to use.
 * if it's not given, the program uses default size (Table::HASH_SIZE)
 *
 */

#include "Table.h"

// cstdlib needed for call to atoi
#include <cstdlib>
#include <string>


bool switchCommandLine(Table *grades, const string &commandLine);

void parseCommandLine(const string &commandLine, string &name, int &score);

void insertGrades(Table *grades, const string &name, int score);

void changeGrades(Table *grades, const string &name, int score);

void lookupGrades(Table *grades, const string &name);

void removeGrades(Table *grades, const string &name);

void printCmdSummary();


int main(int argc, char * argv[]) {
    
    // gets the hash table size from the command line
    
    int hashSize = Table::HASH_SIZE;
    
    Table * grades;  // Table is dynamically allocated below, so we can call
    // different constructors depending on input from the user.
    
    if (argc > 1) {
        hashSize = atoi(argv[1]);  // atoi converts c-string to int
        
        if (hashSize < 1) {
            cout << "Command line argument (hashSize) must be a positive number"
            << endl;
            return 1;
        }
        
        grades = new Table(hashSize);
        
    }
    else {   // no command line args given -- use default table size
        grades = new Table();
    }
    
    grades->hashStats(cout);
    
    // add more code here
    // Reminder: use -> when calling Table methods, since grades is type Table*
    //
    // Once this start-up happens the program repeatedly reads and executes commands
    // from the user, printing out the command prompt (cmd>) after it finishes a command,
    // until the user enters the quit command (q).
    // There is no error-checking required for this program.
    
    string commandLine;

    do {
        getline(cin, commandLine);
    } while (switchCommandLine(grades, commandLine));
    
    return 0;
}

bool switchCommandLine(Table *grades, const string &commandLine) {
    char ch;
    string name;
    int  score;
    ch = commandLine[0];
    
    switch (ch) {
        case 'i':
            parseCommandLine(commandLine, name, score);
            insertGrades(grades, name, score);
            break;
        case 'c':
            parseCommandLine(commandLine, name, score);
            changeGrades(grades, name, score);
            break;
        case 'l':
            name = commandLine.substr(2);
            lookupGrades(grades, name);
            break;
        case 'r':
            name = commandLine.substr(2);
            removeGrades(grades, name);
            break;
        case 'p':
            grades->printAll();
            break;
        case 'n':
            cout << grades->getNumEntries() << endl;
            break;
        case 's':
            grades->hashStats(cout);
            break;
        case 'h':
            printCmdSummary();
            break;
        case 'q':
            return false;
        default:
            cout << "ERROR: invalid input. Please try h(help)." << endl;
            break;
    }
    
    return true;
}

void insertGrades(Table *grades, const string &name, int score) {
    if (!grades->lookup(name)) {
        grades->insert(name, score);
    } else {
        cout << "the student already exists." << endl;
    }
}

void changeGrades(Table *grades, const string &name, int score) {
    if (grades->remove(name)) {
        grades->insert(name, score);
    } else {
        cout << "cannot find the student." << endl;
    }
}

void lookupGrades(Table *grades, const string &name) {
    int *s = grades->lookup(name);
    if (s) {
        cout << *s << endl;
    } else {
        cout << "cannot find the student." << endl;
    }
}

void removeGrades(Table *grades, const string &name) {
    if (!grades->remove(name)) {
        cout << "cannot remove the student." << endl;
    }
}

void printCmdSummary() {
    cout << "Valid commands are i name score(insert), c name newscore(change), "
    << endl;
    cout << "         l name(lookup), r name(remove), p(print), n(number of "
    << endl;
    cout << "         entries), h(help), s(statistics), h(help), q(quit)." 
    << endl;
}

void parseCommandLine(const string &commandLine, string &name, int &score) {
    string subCmdLine = commandLine.substr(2);
    int pos = subCmdLine.find(" ");
    name = subCmdLine.substr(0, pos);
    score = atoi(subCmdLine.substr(pos+1).c_str());
}


