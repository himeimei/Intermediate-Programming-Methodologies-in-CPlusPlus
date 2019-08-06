/**
 CIS 22B: Homework 3A
 
 This program uses the INSERTION sort algorithm to sort an
 array of integers in ascending order.
 
 Modify the insertion sort function to sort an array of doubles in descending order:
 1. Sort an array of doubles (instead of integers)
 2. Sort it in descending order
 
 NAME:Huimei Wu
 */
#include <iostream>
using namespace std;

// Function prototypes
void insertionSort(double *, double *);
void showArray(double *, double *);

int main()
{
    // Define and initialize an array with unsorted values
    const int SIZE = 100;
    double list[SIZE] = {50, 70, 20, 80, 90, 10};
    int length = 6;
    
    // Display the array.
    cout << "The unsorted values are\n";
    showArray(list, list + length - 1);
    
    // Sort the array.
    insertionSort(list, list + length - 1);
    
    // Display the array again.
    cout << "The sorted values are\n";
    showArray(list, list + length - 1);
    return 0;
}

/***************************************************************
 Definition of function insertionSort.
 This function performs an descending order insertion sort on
 array.
 pList - points to the first element in the list
 pLast - points to the last element in the list
 ****************************************************************/
void insertionSort(double *pList, double *pLast)
{
    for (double *curr = pList + 1; curr <= pLast; curr++)
    {
        double hold = *curr;                       // copy current element to hold
        double *back = curr - 1;
        while (back >= pList && hold > *back)   // search where to insert the current element
        {
            *(back + 1) = *back;                // shift to the right
            back--;
        }
        *(back + 1) = hold;                     // put hold back to the array
    }
}

/***************************************************************
 Definition of function showArray.
 This function displays the contents of array.
 pList - points to the first element in the list
 pLast - points to the last element in the list
 ****************************************************************/
void showArray(double *pList, double *pLast)
{
    for (double *ptr = pList; ptr <= pLast; ptr++)
        cout << *ptr << " ";
    cout << endl;
}
/***************************************************************
 Save the new OUTPUT below
 
 The unsorted values are
 50 70 20 80 90 10
 The sorted values are
 90 80 70 50 20 10
 Program ended with exit code: 0
 
 */

