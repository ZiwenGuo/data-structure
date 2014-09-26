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

void printCmdSummary();

void parseCommandLine(const string &commandLine, string &name, int &score);

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
    char ch;
    bool keepgoing = true;
    string name;
    int  score;
    
    do {
        getline(cin, commandLine);
        ch = commandLine[0];
        switch (ch) {
            case 'i':
                parseCommandLine(commandLine, name, score);
                if (!grades->lookup(name)) {
                    grades->insert(name, score);
                } else {
                    cout << "the student already exists." << endl;
                }
                break;
            case 'c':
                parseCommandLine(commandLine, name, score);
                if (grades->remove(name)) {
                    grades->insert(name, score);
                } else {
                    cout << "cannot find the student." << endl;
                }
                break;
            case 'l':
            {
                name = commandLine.substr(2);
                int *s = grades->lookup(name);
                if (s) {
                    cout << *s << endl;
                } else {
                    cout << "cannot find the student." << endl;
                }
                break;
            }
            case 'r':
                name = commandLine.substr(2);
                if (!grades->remove(name)) {
                    cout << "cannot remove the student." << endl;
                }
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
                keepgoing = false;
                break;
            default:
                cout << "ERROR: invalid input. Please try h(help)." << endl;
                break;
        }
    } while (keepgoing);
    
    return 0;
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

