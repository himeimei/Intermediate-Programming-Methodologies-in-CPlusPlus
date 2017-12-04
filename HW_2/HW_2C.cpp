/**
 CIS 22B: Homework 2C
 2D Arrays
 
 Project: Airports
 
 NAME: Huimei Wu
 */

#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

// Global constants
const int MAX_NUM = 50;


// Function prototypes
void readTable(int relations[][MAX_NUM], string memberNames[], int &numMember);
void printTable(int relations[][MAX_NUM], string memberNames[], int numMember);
void friendList(int relations[][MAX_NUM], string memberNames[], int numMember);
void friendGroup(int relations[][MAX_NUM], string memberNames[], int numMember);
void findLongestFriendship(int relations[][MAX_NUM], string memberNames[],
                           int numMember);

int main( void )
{
    int relations[MAX_NUM][MAX_NUM];
    string memberNames[MAX_NUM];
    int numMember = 0;
   
    // read the members' information from thr input file to a table
    readTable(relations, memberNames, numMember);
    
    // display the members' information by table
    printTable(relations, memberNames, numMember);
    
    // Show the friends list for each member
    friendList(relations, memberNames, numMember);
    
    // show all groups of two friends
    friendGroup(relations, memberNames, numMember);
    
    // show the longest friendship for each member
    findLongestFriendship(relations, memberNames, numMember);

    return 0;
}   // main

/******************************************************
 This function prompts the user to enter the name of the input file. It then
 read the data from input file into a table with the name of the members and
 their relationship (years) information.
 INPUT: int relations[][MAX_NUM], string memberNames[], int &numMember
 OUTPUT: void
 */
void readTable(int relations[][MAX_NUM], string memberNames[], int &numMember)
{
    string inputFileName;
    ifstream inputFile;
    int read_attempts = 1;
    // prompt user for filename
    cout << "Please enter the name of the file that holds the"
    "information of the students: \n";
    cin >> inputFileName;
    // open the input file
    inputFile.open(inputFileName.c_str());
    // try up yo 3 times to open the input file
    while (inputFile.fail() && read_attempts < 3)
    {
        cout << "Error: Could not open file: \"" <<inputFileName << "\". "
        << "Please re-enter (attempt: " << read_attempts
        << ")the filename: \n";
        cin >> inputFileName;
        inputFile.open(inputFileName.c_str());
    }
    if (inputFile.fail())
    {
        cout << "\n\tPlease check the name of the input file and"
             << "try again later!\n";
        exit(EXIT_FAILURE);
    }
    else
    {
        // Part 1: read the number of members form input file
        inputFile >> numMember;
        if (numMember > MAX_NUM)
        {
            cout << "\n\tThe input file \n" << inputFileName << " is too big"
            << " it has more than " << MAX_NUM << "items!\n";
            exit (EXIT_FAILURE);
        }
        // Part 2: read all the members' names
        for (int i = 0; i < numMember; i++)
        {
            inputFile >> memberNames[i];
        }
        // Part 3: read members' relationship information
        for (int i = 0; i < numMember; i++)
        {
            for (int j = 0; j < numMember; j++)
                inputFile >> relations[i][j];
        }
        // close the input file
        inputFile.close();
    }
}

/******************************************************
 This function displays the table with the members' names and their relationships
 (years) information, include the number of friends too.
 INPUT: int relations[][MAX_NUM], string memberNames[], int numMember
 OUTPUT: void
 */
void printTable(int relations[][MAX_NUM], string memberNames[], int numMember)
{
    cout << "\nAll the members' names and their relationships (years)   informations"
         << "show in the table: \n\n";
    cout << "   " << " |";
    for (int i = 0; i < numMember; i++) {
        cout << " " << memberNames[i] << " ";
    }
    cout << endl;
    
    cout << "---  ";
    for (int i = 0; i < numMember; i++) {
        cout << " " << "---" << " ";
    }
    cout << endl;
    for (int i = 0; i < numMember; i++)
    {
        cout << memberNames[i] << " |";
        for (int j = 0; j < numMember; j++)
            cout << setw(3) << relations[i][j] << "  ";
        cout << endl;
    }
    cout << "\n\n";
}

/******************************************************
 This function displays the list of friends for each student in the club with
 their names and their friends' names as well as how many years they have been
 friends with each other.
 INPUT: int relations[][MAX_NUM], string memberNames[], int numMember
 OUTPUT: void
 */
void friendList(int relations[][MAX_NUM], string memberNames[], int numMember)
{
    cout << "The list of friends for each student shows below, include the "
         << "number of friends too.\n\n";
    for(int i = 0; i < numMember; i++)
    {
        int count = 0;
        string friends = "";
    
        for (int j = 0; j < numMember; j++)
        {
            if (relations[i][j] != 0)
            {
                count++;
                if (count == 1)
                {
                    friends = friends + " " + memberNames[j];
                }
                else
                {
                    friends = friends + ", " + memberNames[j];
                }
            }
        }
        cout << memberNames[i] << " (" << count << "):" << friends << endl;
    }
    cout << "\n\n";
}

/******************************************************
This function displays all groups of two friends in the club with both their
names as well as how many years they have been friends with each other
INPUT: int relations[][MAX_NUM], string memberNames[], int numMember
OUTPUT: void
*/
void friendGroup(int relations[][MAX_NUM], string memberNames[], int numMember)
{
    cout << "All groups of two friends show on below: \n\n";
    for(int i = 0; i < numMember; i++)
    {
        for (int j = i; j < numMember; j++)
        {
            if (relations[i][j] != 0)
            {
                cout << memberNames[i] << " - " << memberNames[j] << " ("
                << relations[i][j] << "years)" << endl;
            }
        }
    }
    cout << "\n\n";
}

/******************************************************
 This function displays the longest friendship relationship for each student
 with both their names as well as how many years they have been friends with
 each other
 INPUT: int relations[][MAX_NUM], string memberNames[], int numMember
 OUTPUT: void
 */
void findLongestFriendship(int relations[][MAX_NUM], string memberNames[],
                           int numMember)
{
    cout << "The longest friendship relationships for each student show on below: \n\n";
    int max = 0, i = 0, j = 0, count = 0;
    string result = "";
    for (i = 0; i < numMember; i++)
    {
        max = relations[i][0];
        for (j = 0; j < numMember; j++)
        {
            if (relations[i][j] > max)
            {
                max = relations[i][j];
            }
        }

        result = "";
        count = 0;

        for (j = 0; j < numMember; j++)
        {
            if (relations[i][j] == max)
            {
                count++;
                if (count == 1)
                {
                    result = " " + memberNames[j];
                }
                else
                {
                    result += ", " + memberNames[j];
                }
            }
        }
        cout << memberNames[i] << " (" << max << "years):" << result << endl;
    }
    cout << "\n";
}



/** Save the correct output below
 Please enter the name of the file that holds theinformation of the students:
 3club.txt
 
 All the members' names and their relationships (years)   informationsshow in the table:
 
     | Ami  Ann  Ben  Dan  Emy  Ira  Guy  Leo  Luc  Meg  Sue  Tom
 ---   ---  ---  ---  ---  ---  ---  ---  ---  ---  ---  ---  ---
 Ami |  0    0    0    0    1    0    0    0    0    0    3    0
 Ann |  0    0    1    0    0    0    0    0    2    4    0    0
 Ben |  0    1    0    3    0    0    0    0    3    0    0    3
 Dan |  0    0    3    0    0    5    0    0    1    0    5    0
 Emy |  1    0    0    0    0    2    0    0    0    0    0    9
 Ira |  0    0    0    5    2    0    0    1    0    0    0    0
 Guy |  0    0    0    0    0    0    0    1    0    0    2    0
 Leo |  0    0    0    0    0    1    1    0    0    0    0    0
 Luc |  0    2    3    1    0    0    0    0    0   13    0    0
 Meg |  0    4    0    0    0    0    0    0   13    0    0    0
 Sue |  3    0    0    5    0    0    2    0    0    0    0   10
 Tom |  0    0    3    0    9    0    0    0    0    0   10    0
 
 
 The list of friends for each student shows below, include the number of friends too.
 
 Ami (2): Emy, Sue
 Ann (3): Ben, Luc, Meg
 Ben (4): Ann, Dan, Luc, Tom
 Dan (4): Ben, Ira, Luc, Sue
 Emy (3): Ami, Ira, Tom
 Ira (3): Dan, Emy, Leo
 Guy (2): Leo, Sue
 Leo (2): Ira, Guy
 Luc (4): Ann, Ben, Dan, Meg
 Meg (2): Ann, Luc
 Sue (4): Ami, Dan, Guy, Tom
 Tom (3): Ben, Emy, Sue
 
 
 All groups of two friends show on below:
 
 Ami - Emy (1years)
 Ami - Sue (3years)
 Ann - Ben (1years)
 Ann - Luc (2years)
 Ann - Meg (4years)
 Ben - Dan (3years)
 Ben - Luc (3years)
 Ben - Tom (3years)
 Dan - Ira (5years)
 Dan - Luc (1years)
 Dan - Sue (5years)
 Emy - Ira (2years)
 Emy - Tom (9years)
 Ira - Leo (1years)
 Guy - Leo (1years)
 Guy - Sue (2years)
 Luc - Meg (13years)
 Sue - Tom (10years)
 
 
 The longest friendship relationships for each student show on below:
 
 Ami (3years): Sue
 Ann (4years): Meg
 Ben (3years): Dan, Luc, Tom
 Dan (5years): Ira, Sue
 Emy (9years): Tom
 Ira (5years): Dan
 Guy (2years): Sue
 Leo (1years): Ira, Guy
 Luc (13years): Meg
 Meg (13years): Luc
 Sue (10years): Tom
 Tom (10years): Sue
 
 Program ended with exit code: 0
 */


