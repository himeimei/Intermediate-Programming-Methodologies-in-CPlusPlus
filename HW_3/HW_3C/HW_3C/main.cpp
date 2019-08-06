/**
 CIS 22B: Homework 3C
 
 Movie Statistics
 
 NAME: Huimei
 */
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

// Function prototypes
int *readSurveyData(string filename, int &n);
void insertionSort(int *pAry, int *pLast);
void writeArray(string filename, int *pAry, int *pLast);
double calcAvg(int *pAry, int *pLast);
double calcMedian(int *pAry, int *pLast);
int calcMode(int *pAry, int *pLast);
void displayStats(int n, double avg, double median, int mode);

int main()
{
    //string inputfilename = "moviesurvey.txt";
    //string outputfilename = "sortedmoviesurvey.txt";
    string inputfilename = "moviesurvey_2.txt";
    string outputfilename = "sortedmoviesurvey_2.txt";
    int n, mode;
    int *pAry;
    double avg, median;
    
    pAry = readSurveyData(inputfilename, n);
    int *pLast = pAry + n - 1;
    insertionSort(pAry, pLast);
    writeArray(outputfilename, pAry, pLast);
    avg = calcAvg(pAry, pLast);
    median = calcMedian(pAry, pLast);
    mode = calcMode(pAry, pLast);
    displayStats(n, avg, median, mode);

    // release memory
    delete [] pAry;

#ifdef _MSC_VER
    cout << _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n";
#endif
    
    return 0;
}

/***************************************************************
 This function reads data from an input file into a dynamically
 allocated array
 filename - the name of the input file
 n - the array size (an output parameter)
 Return - the dynamically allocated array
 */
int *readSurveyData(string filename, int &n)
{
    ifstream inputFile;
    int idx = 0;
    int *pAry = nullptr;
    
    // open the input file
    inputFile.open(filename.c_str());
    
    if (inputFile.fail())
    {
        cout << "\n\tPlease check the name of the input file"
        << "and \n\ttry again later!\n";
        exit(EXIT_FAILURE);
    }
    else
    {
        // read number of students that were surveyed
        inputFile >> n;
        
        // allocate memory for array with size n
        pAry = new int[n];
        
        // reading data from the input file into arrays
        for (idx = 0; idx < n; idx++) {
            inputFile >> pAry[idx];
        }
        
        // close the input file
        inputFile.close();
    }
    return pAry;
}
    

/***************************************************************
 This function performs an ascending order insertion sort on
 array.
 pList - points to the first element in array
 pLast - points to the last element in array
 */
void insertionSort(int *pAry, int *pLast)
{
    for (int *curr = pAry + 1; curr <= pLast; curr++)
    {
        int hold = *curr;                       // copy current element to hold
        int *back = curr - 1;
        while (back >= pAry && hold < *back)   // search where to insert the current element
        {
            *(back + 1) = *back;                // shift to the right
            back--;
        }
        *(back + 1) = hold;                     // put hold back to the array
    }
}

/***************************************************************
 This function writes the contents of array to a file
 filename - name of the output file
 pList - points to the first element in array
 pLast - points to the last element in array
 */
void writeArray(string filename, int *pAry, int *pLast)
{
    ofstream outputFile;
    
    // open the output file
    outputFile.open(filename.c_str());
    
    // write the number of students
    outputFile << (pLast - pAry + 1) << endl;
    
    for (int *pWalk = pAry; pWalk <= pLast; pWalk++)
    {
        outputFile << *pWalk << endl;
    }
    
    // close the output file
    outputFile.close();
}

/***************************************************************
 This function calculates and returns the average of the numbers
 in array
 pList - points to the first element in the array
 pLast - points to the last element in the array
 */
double calcAvg(int *pAry, int *pLast)
{
    double avg = 0;
    double sum = 0;
    int *pWalk;
    for (pWalk = pAry; pWalk <= pLast; pWalk++)
    {
        sum += *pWalk;
    }
    avg = sum / (pLast-pAry+1);
    return avg;
}

/***************************************************************
 This function calculates and returns the median of the numbers
 in array
 pList - points to the first element in the array
 pLast - points to the last element in the array
 */
double calcMedian(int *pAry, int *pLast)
{
    double median = 0;
    long size = pLast - pAry + 1;
    long mid = (pLast - pAry) / 2;
    if (size % 2 == 0)
    {
        median = (double)(*(pAry + mid) + *(pAry +(mid+1))) / 2;
    }
    else
    {
        median = *(pAry +mid);
    }
    return median;
}

/***************************************************************
 This function calculates and returns the mode of the numbers
 in array
 pList - points to the first element in the array
 pLast - points to the last element in the array
 */
int calcMode(int *pAry, int *pLast)
{
    int count = 0;
    int maxCount = 0;
    int mode = 0;

    int *pWalk;

    for (pWalk = pAry; pWalk <= pLast; pWalk++)
    {
        count++;

        if (*pWalk < *(pWalk + 1))
        {
            if (count > maxCount)
            {
                mode = *pWalk;
                maxCount = count;
            }
            count = 0;
        }
    }

    return mode;
}

/***************************************************************
 This function displays the movie statistics
 n - number of surveyed students
 avg - average numeber of movies each student saw in a month
 median - the median number of input
 mode - the mode number of input
 */
void displayStats(int n, double avg, double median, int mode)
{
    cout << "There are " << n << " surveyed students." << endl;
    cout << "The average numeber of movies each student saw in a month is: "
         << avg << endl;
    cout << "The median of the number is: " << median << endl;
    cout << "The mode of the number is: " << mode << endl;
}


/***************************************************************
 Save the OUTPUT below
 
 For moviesurvey.txt, the output is:
 There are 5 surveyed students.
 The average numeber of movies each student saw in a month is: 7.2
 The median of the number is: 7
 The mode of the number is: 5
 Program ended with exit code: 0
 
 ===============================================================
 
 For moviesurvey_2.txt, the output is:
 There are 26 surveyed students.
 The average numeber of movies each student saw in a month is: 12
 The median of the number is: 10
 The mode of the number is: 8
 Program ended with exit code: 0
 */


