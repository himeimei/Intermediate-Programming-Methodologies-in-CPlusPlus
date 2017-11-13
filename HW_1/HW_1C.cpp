/***
 22B - PROGRAM 1C: Search a Sorted List of Strings
 BINARY SEARCH
 
 
 <Huimei Wu>
 <Xcode>
 
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

// Function prototypes
void welcome(void);
void farewell(void);
void readStuData(double GPAList[], string nameList[],
                 int &size, const int SIZE);
int binarySearch(string nameList[], int size, string target);
string getStuName(const string nameList[], int size,
                  string missingNameList[], int &missingSize, int maxSize);
void searchManager(const double GPAList[], const string nameList[], int size,
                   string missingNameList[], int &missingSize, int maxSize);
void writeDataToFile(const string missingNameList[], int size,
                     string filename);

int main()
{
    // maximum size of array
    const int SIZE = 100;

    double GPAList[SIZE];
    string nameList[SIZE];
    string missingNameList[SIZE];

    int size = 0;
    int missingSize = 0;
    
    // show the welcome message
    welcome();
    
    // read students' data from input file into the arrays
    readStuData(GPAList, nameList, size, SIZE);
    
    // get target name from user input and search it by using binary search
    searchManager(GPAList, nameList, size, missingNameList, missingSize, SIZE);

    // write missing names to a file
    writeDataToFile(missingNameList, missingSize, "missingNames.txt");
   
    farewell();

    return 0;
}

/******************************************************
 This function displays the welcome message and the purpose of the program.
 */
void welcome(void)
{
    cout << "\n\n\t\t *~~*~~* WELCOME *~~*~~*\n\n"
    << "\tto the GPA Searcher!\n\n"
    << "\t\tThis program will: \n"
    << "\t\t - obtain the students' GPA and names from an input file \n"
    << "\t\t - the names in the file are in alphabetical order,\n "
    << "\t\t - search names in the namelist, and \n"
    << "\t\t - write the missing names to an output file, \n\n";
}

/******************************************************
 This function displays the end-of-the-program message.
 */
void farewell(void)
{
    cout << "\n\n\t\t *~~*~~* THE END *~~*~~*\n"
    << "\t     Thank you for using my program! \n\n";
}

/******************************************************
 This function prompts the user to enter the name of the input file. It then
 read the data from input file into two parallel arrays, one storing student
 GPAs, other storing their names.
 INPUT: double GPAList[], string nameList[], int &size, const int SIZE
 OUTPUT: void
 */
void readStuData(double GPAList[], string nameList[], int &size, const int SIZE)
{
    string inputFileName;
    ifstream inputFile;
    int readAttempts = 1, idx = 0;
    
    // prompt user for filename
    cout << "\nPlease enter the name of the file that holds the students' "
         << "GPAs and names: \n";
    cin >> inputFileName;
    
    // open the input file
    inputFile.open(inputFileName.c_str());
    // try up to 3 times to open the input file
    while (inputFile.fail() && readAttempts < 3)
    {
        cout << "ERROR: Could not open file: \"" << inputFileName << "\". "
        << "Please verify the filename." << endl << endl;
        
        readAttempts++;
        cout << "Please re-enter (attempt: "
             << readAttempts << ") the filename : \n";
        cin >> inputFileName;
        inputFile.open(inputFileName.c_str());
    }
    
    if (inputFile.fail())
    {
        cout << "\n\tPlease check the name of the input file"
             << "and \n\ttry again later!\n";
        farewell();
        exit(EXIT_FAILURE);
    }
    else
    {
        // reading data from the input file into arrays
        while (idx < SIZE && inputFile >> GPAList[idx] >> nameList[idx])
        {
            idx++;
        }
        size = idx;
        if ( size == SIZE && !inputFile.eof())
        {
            cout << "\n\tThe input file  \"" << inputFileName
            << "\" is too big: \n\tit has more than "
            << SIZE << " items!\n";
            farewell();
            exit(EXIT_FAILURE);
        }
        // close the input file
        inputFile.close();
    }
}

/******************************************************
 This function prompts the user to enter a student name. This function
 also checks the validation of user's input.
 INPUT: const string nameList[], int size,
        string missingNameList[], int &missingSize, int maxSize
 OUTPUT: string
 */
string getStuName(const string nameList[], int size,
                  string missingNameList[], int &missingSize, int maxSize)
{
    string stuName;
    cout << "Enter a student's name: ";
    cin >> stuName;
    while (stuName.compare(nameList[0]) < 0 ||
           stuName.compare(nameList[size - 1]) > 0)
    {
        missingNameList[missingSize] = stuName;
        missingSize++;
        if (missingSize >= maxSize)
        {
            break;
        }

        cout << "Enter a name in the range of " << nameList[0]
             << " through " << nameList[size - 1] << ".\n";
        cout << "Enter a student's name: ";
        cin >> stuName;
    }
    return stuName;
}

/******************************************************
 This function search a given name by using binary search. If the given
 name can be found in nameList, it returns position of the given name in
 nameList. Otherwise, it returns -1.
 INPUT: const string nameList[], int size, string target
 OUTPUT: int
 */
int binarySearch(const string nameList[], int size, string target)
{
    int first = 0,
        last = size - 1,
        middle,
        position = -1;
    bool found = false;
    
    while (!found && first <= last)
    {
        middle = (first + last) / 2;
        if(nameList[middle] == target)
        {
            found = true;
            position = middle;
        }
        else if(nameList[middle] > target)
            last = middle - 1;
        else
            first = middle + 1;
    }
    return position;
}

/******************************************************
 This function gets target name from user input and searches the target
 by using binary search. If target name can be found, this function
 displays target name's GPA and name. Otherwise, it stores missing
 names into missingNameList array.
 INPUT: const double GPAList[], const string nameList[], int size,
        string missingNameList[], int &missingSize, int maxSize
 OUTPUT: void
 */
void searchManager(const double GPAList[], const string nameList[], int size,
                   string missingNameList[], int &missingSize, int maxSize)
{
    string target;
    int position;
    char again;

    do
    {
        target = getStuName(nameList, size, missingNameList, missingSize, maxSize);
        position = binarySearch(nameList, size, target);
        if (position == -1) {
            cout << "That student's name [" << target << "] was not found.\n";
            if (missingSize >= maxSize)
            {
                break;
            }
            missingNameList[missingSize] = target;
            missingSize++;
            if (missingSize >= maxSize)
            {
                break;
            }
        }
        else {
            cout << fixed << showpoint << setprecision(1) << setw(6)
                 << GPAList[position] << "\t" << nameList[position] << endl;
        }
        cout << "Enter y or Y to continue searching: ";
        cin >> again;
    } while (again == 'y' || again == 'Y');
}

/******************************************************
 This function writes missing names to a file. the size of the array and
 the name of the file are provided as parameters
 INPUT: const string missingNameList[], int size, string filename
 OUTPUT: void
 */
void writeDataToFile(const string missingNameList[], int size,
                     string filename)
{
    ofstream outputFile;
    
    // open the output file
    outputFile.open(filename.c_str());
    
    // write missing names to the file
    for (int i = 0; i < size ; i++)
    {
        outputFile << missingNameList[i] << endl;
    }

    // close the output file
    outputFile.close();
}

/****************** OUTPUT ******************
 

 *~~*~~* WELCOME *~~*~~*
 
 to the GPA Searcher!
 
 This program will:
 - obtain the students' GPA and names from an input file
 - the names in the file are in alphabetical order,
 - search names in the namelist, and
 - write the missing names to an output file,
 
 
 Please enter the name of the file that holds the students' GPAs and names:
 gpa.txt
 Enter a student's name: Ada
 3.0    Ada
 Enter y or Y to continue searching: y
 Enter a student's name: Zubin
 4.0    Zubin
 Enter y or Y to continue searching: y
 Enter a student's name: Ian
 3.9    Ian
 Enter y or Y to continue searching: y
 Enter a student's name: Sam
 3.9    Sam
 Enter y or Y to continue searching: y
 Enter a student's name: Erik
 2.3    Erik
 Enter y or Y to continue searching: y
 Enter a student's name: Xun
 3.3    Xun
 Enter y or Y to continue searching: y
 Enter a student's name: Abc
 Enter a name in the range of Ada through Zubin.
 Enter a student's name: Zyx
 Enter a name in the range of Ada through Zubin.
 Enter a student's name: Cindy
 That student's name [Cindy] was not found.
 Enter y or Y to continue searching: y
 Enter a student's name: Kate
 That student's name [Kate] was not found.
 Enter y or Y to continue searching: y
 Enter a student's name: Lily
 That student's name [Lily] was not found.
 Enter y or Y to continue searching: y
 Enter a student's name: Sun
 That student's name [Sun] was not found.
 Enter y or Y to continue searching: y
 Enter a student's name: Wu
 That student's name [Wu] was not found.
 Enter y or Y to continue searching: n
 
 
 *~~*~~* THE END *~~*~~*
 Thank you for using my program!
 
 Program ended with exit code: 0
 */
