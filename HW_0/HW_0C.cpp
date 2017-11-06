/***
 22B - PROGRAM 0C: Exam Statistics
 ARRAYS, FUNCTIONS, DATA FILES, and SORTING
 
 The program prompts user to enter the input file containing scores of students along with their ids.
 It stores the data from input file into two parallel arrays.
 It then
 - writes the data to file "scoresOut1.txt" which is sorted in ascending order of student id
 - writes the data to file "scoresOut2.txt" which is sorted in descending order of student score
 - displays highest score followed by the ids of the students with that score
 - displays lowest score followed by the ids of the students with that score
 - total number of students
 - class average
 
 You have three tasks:
 1. Finish writing main() (provide the correct parameters in the calling statements)
 2. There are 3 or 4 minor errors - fix them
 3. Run the program and save the output as a commment at the end of the source file
 (under OUTPUT #3)
 
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
void readStuData(string idList[], double scoreList[], int &size, const int maxSize);
double calcAverage(const double scoreList[], int size);
void displayHighest(const string idList[], const double scoreList[], int size);
void displayLowest(const string idList[], const double scoreList[], int size);
void writeDataToFile(const string idList[], const double scoreList[], int size, string filename);
void sortIdAsc(string idList[], double scoreList[], int size);
void sortScoreDesc(string idList[], double scoreList[], int size);

int main()
{
    //const int SIZE = 5;               // maximum size of array
    const int SIZE = 50;               // maximum size of array
    double scoreList[SIZE],            // array of test scores
    average = 0.0;
    
    string idList[SIZE],                // array of student ids
    outfile1 = "scoresOut1.txt",
    outfile2 = "scoresOut2.txt";
    
    int size = 0; // actual size of array
    
    // show the welcome message
    welcome();
    
    // read students' data from input file into the arrays
    readStuData(idList, scoreList, size, SIZE); // <================= what are this function's arguments?
    
    //sort arrays in ascending order by ID and write the sorted arrays to a file
    sortIdAsc(idList, scoreList, size);        // <=================
    writeDataToFile(idList, scoreList, size, outfile1);  // <=================
    cout << "\n\nExams scores and IDs sorted in ascending order by the students' IDs are available in \""
    << outfile1 << "\"." << endl;
    
    //sort arrays in descending order by score and write the sorted arrays to a file
    sortScoreDesc(idList, scoreList, size);    // <=================
    writeDataToFile(idList, scoreList, size, outfile2);  // <=================
    cout << "\nExams scores and IDs sorted in descending order by the students' scores are available in file \""
    << outfile2 << "\"." << endl;
    
    // show highest & lowest scores & the matching IDs
    displayHighest(idList, scoreList, size);    // <=================
    displayLowest(idList, scoreList, size);     // <=================
    
    // display the number of students and the class average
    cout << fixed << showpoint << setprecision(2);
    cout << "\nTotal students in class: " << size << endl;
    average = calcAverage(scoreList, size);  // <=================
    cout << "Class average: " << average <<  endl;
    
    // show the end of the program message
    farewell();
    
    return 0;
}


/******************************************************
 This function displays the welcome message and the purpose of the program.
 */
void welcome(void)
{
    cout << "\n\n\t\t *~~*~~* WELCOME *~~*~~*\n\n"
    << "\tto the Exam Score Calculator and Sorter!\n\n"
    << "\t\tThis program will: \n"
    << "\t\t - obtain the students' scores and IDs from an input file \n"
    << "\t\t - calculate the class average,\n "
    << "\t\t - sort in ascending order by student ID, \n"
    << "\t\t - write the sorted scores and IDs to an output file\n"
    << "\t\t - sort in descending order by score, \n"
    << "\t\t - write the sorted scores and IDs to another output file, and \n"
    << "\t\t - show the highest and lowest scores and the matching IDs \n\n";
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
 This function prompts the user to enter the name of the input file. It then read the data
 from input file into two parallel arrays, one storing student ids, other storing their scores.
 INPUT: string [], double [], int size
 OUTPUT: void
 */
void readStuData(string idList[], double scoreList[], int &size, const int maxSize)
{
    string inputfilename;
    ifstream inputFile;
    int read_attempts = 1, idx = 0;
    
    // prompt user for filename
    cout << "\nPlease enter the name of the file that holds the students' scores and IDs: \n";
    cin >> inputfilename;
    
    // open the input file
    inputFile.open(inputfilename.c_str());
    // try up to 3 times to open the input file
    while (inputFile.fail() && read_attempts < 3)
    {
        cout << "ERROR: Could not open file: \"" << inputfilename << "\". "
        << "Please verify the filename." << endl << endl;
        
        read_attempts++;
        cout << "Please re-enter (attempt: " << read_attempts << ") the filename : \n";
        cin >> inputfilename;
        inputFile.open(inputfilename.c_str());
    }
    
    if (inputFile.fail())
    {
        cout << "\n\tPlease check the name of the input file and \n\ttry again later!\n";
        farewell();
        exit(EXIT_FAILURE);
    }
    else
    {
        // reading data from the input file into arrays
        while (idx < maxSize && inputFile >> idList[idx] >> scoreList[idx])
        {
            idx++;
        }
        size = idx;
        if ( size == maxSize && !inputFile.eof())
        {
            cout << "\n\tThe input file  \"" << inputfilename << "\" is too big: \n\tit has more than "
            << maxSize << " items!\n";
            farewell();
            exit(EXIT_FAILURE);
        }
        // close the input file
        inputFile.close();
    }
    
}

/******************************************************
 This function calculates and returns the average of the values present in the input array
 INPUT: const double [], int size
 OUTPUT: double
 */
double calcAverage(const double scoreList[], int size)
{
    double sum = 0;
    
    for (int i = 0; i < size ; i++)
        sum += scoreList[i];
    
    return sum / size;
}


/******************************************************
 This function displays the ids from the first input array that corresponds to the highest
 score from the second input array. NOTE: The second array is sorted in descending order.
 Thus 0th element holds highest value
 INPUT: const string [], const double [], int size
 OUTPUT: void
 */
void displayHighest(const string idList[], const double scoreList[], int size)
{
    double highest = scoreList[0];
    cout << "\nHighest score: \t" << highest << endl
    << "Students:" << endl;
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        if (scoreList[i] == highest)
        {
            cout << "\t\t" << idList[i] << endl;
            sum++;
        }
    }
    cout << "\n\t\t" << sum << " students got the same [highest] score!\n\n";
}


/******************************************************
 This function displays the ids from the first input array that corresponds to the lowest
 score from the second input array. NOTE: The second array is sorted in descending order.
 Thus (size-1)th element holds lowest value
 INPUT: const string [], const double [], int size
 OUTPUT: void
 */
void displayLowest(const string idList[], const double scoreList[], int size)
{
    double lowest = scoreList[size - 1];
    cout << "\nLowest score: \t" << lowest << endl
    << "Students:" << endl;
    int sum = 0;
    for (int i = size - 1; i >= 0; i--)
    {
        if (scoreList[i] == lowest)
        {
            cout << "\t\t" << idList[i] << endl;
            sum++;
        }
    }
    cout << "\n\t\t" << sum << " students got the same [lowest] score!\n\n";
}

/******************************************************
 This function writes data from two parallel arrays to a file. the size of the array and
 the name of the file are provided as parameters
 INPUT: const string [], const double [], int size, string filename
 OUTPUT: void
 */
void writeDataToFile(const string idList[], const double scoreList[], int size, string filename)
{
    ofstream outputFile;
    
    //open the output file
    outputFile.open(filename.c_str());
    
    // display ids and scores
    for (int i = 0; i < size ; i++)
    {
        outputFile << idList[i]
        << fixed << showpoint << setprecision(2) << setw(8)<< scoreList[i]
        << endl;
    }
    
    //close the output file
    outputFile.close();
}

/******************************************************
 This function accepts two parallel arrays, sorts them in ascending order of the first array
 INPUT: const string [], const double [], int size
 OUTPUT: void
 */
void sortIdAsc(string idList[], double scoreList[], int size)
{
    string tempId;
    double tempScore;
    int lowIdx;
    
    for (int i = 0; i < size - 1; i++)
    {
        // find index of the lowest ID
        lowIdx = i;
        for (int j = i + 1; j < size; j++)
        {
            if (idList[lowIdx] > idList[j])
                lowIdx = j;
        }
        // swap IDs
        tempId = idList[i];
        idList[i] = idList[lowIdx];
        idList[lowIdx] = tempId;
        
        // swap scores
        tempScore = scoreList[i];
        scoreList[i] = scoreList[lowIdx];
        scoreList[lowIdx] = tempScore;
    }
}

/******************************************************
 This function accepts two parallel arrays, sorts them in descending order of the second array
 INPUT: const string [], const double [], int size
 OUTPUT: void
 */
void sortScoreDesc(string idList[], double scoreList[], int size)
{
    string tempId;
    double tempScore;
    int highIdx;
    
    for (int i = 0; i < size - 1; i++)
    {
        // find index of the smallest score
        highIdx = i;
        for (int j = i + 1; j < size; j++)
        {
            if (scoreList[highIdx] < scoreList[j])
                highIdx = j;
        }
        // swap IDs
        tempId = idList[i];
        idList[i] = idList[highIdx];
        idList[highIdx] = tempId;
        
        // swap scores
        tempScore = scoreList[i];
        scoreList[i] = scoreList[highIdx];
        scoreList[highIdx] = tempScore;
    }
}


/****************** OUTPUT #1 ******************
 
 *~~*~~* WELCOME *~~*~~*
 
 to the Exam Score Calculator and Sorter!
 
 This program will:
 - obtain the students' scores and IDs from an input file
 - calculate the class average,
 - sort in ascending order by student ID,
 - write the sorted scores and IDs to an output file
 - sort in desecending order by score,
 - write the sorted scores and IDs to another output file, and
 - show the highest and lowest scores and the matching IDs
 
 
 Please enter the name of the file that holds the students' scores and IDs:
 scores.txt
 
 The input file  "scores.txt" is too big:
 it has more than 5 items!
 
 
 *~~*~~* THE END *~~*~~*
 Thank you for using my program!
 */

/****************** OUTPUT #2 ******************
 
 *~~*~~* WELCOME *~~*~~*
 
 to the Exam Score Calculator and Sorter!
 
 This program will:
 - obtain the students' scores and IDs from an input file
 - calculate the class average,
 - sort in ascending order by student ID,
 - write the sorted scores and IDs to an output file
 - sort in desecending order by score,
 - write the sorted scores and IDs to another output file, and
 - show the highest and lowest scores and the matching IDs
 
 
 Please enter the name of the file that holds the student's scores:
 score.txt
 ERROR: Could not open file: "score.txt". Please verify the filename.
 
 Please re-enter (attempt: 2) the filename :
 ids.txt
 ERROR: Could not open file: "ids.txt". Please verify the filename.
 
 Please re-enter (attempt: 3) the filename :
 stuData.txt
 
 Please check the name of the input file and
 try again later!
 
 
 *~~*~~* THE END *~~*~~*
 Thank you for using my program!
 */

/**********************************************
 ****************** OUTPUT #3 ******************
 
 
 *~~*~~* WELCOME *~~*~~*
 
 to the Exam Score Calculator and Sorter!
 
 This program will:
 - obtain the students' scores and IDs from an input file
 - calculate the class average,
 - sort in ascending order by student ID,
 - write the sorted scores and IDs to an output file
 - sort in descending order by score,
 - write the sorted scores and IDs to another output file, and
 - show the highest and lowest scores and the matching IDs
 
 
 Please enter the name of the file that holds the students' scores and IDs:
 scores.txt
 
 
 Exams scores and IDs sorted in ascending order by the students' IDs are available in "scoresOut1.txt".
 
 Exams scores and IDs sorted in descending order by the students' scores are available in file "scoresOut2.txt".
 
 Highest score:     100
 Students:
 2ABCD
 AK323
 DR123
 
 3 students got the same [highest] score!
 
 
 Lowest score:     45
 Students:
 TY4XZ
 SW111
 9QWE9
 
 3 students got the same [lowest] score!
 
 
 Total students in class: 13
 Class average: 81.69
 
 
 *~~*~~* THE END *~~*~~*
 Thank you for using my program!
 
 Program ended with exit code: 0
 */

