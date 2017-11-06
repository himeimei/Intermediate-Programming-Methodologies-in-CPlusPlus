/***
 22B - PROGRAM 0B:
 ARRAYS and FUNCTIONS: SORTING using the SELECTION SORT function
 
 Find and fix errors. Run the program once and save the output as a comment at the end
 of the source file.
 
 
 <Huimei Wu>
 <Xcode>
 
 */

#include <iostream>

using namespace std;

void selectionSort(int array[], int size);

int main()
{
    int list[100] = {50, 30, 80, 10, 30, 40, 90, 30, 80, 30};
    int size = 10;
    
    for (int i = 0; i < size; i++)
    {
        cout << list[i] << " ";
    }
    cout << endl;
    
    
    selectionSort(list, size);
    for (int i = 0; i < size; i++)
    {
        cout << list[i] << " ";
    }
    cout << endl;
    
    return 0;
}

/***************************************************
 This function sorts an array in descending order
 using the selection sort algorithm
 */
void selectionSort(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        // look for largest
        int maxIndex = i;
        for(int k = i + 1; k < size; k++)
        {
            if (array[k] > array[maxIndex])
                maxIndex = k;
        }
        // swap
        int hold = array[maxIndex];
        array[maxIndex] = array[i];
        array[i] = hold;
    }
    
}

/****************** OUTPUT
 50 30 80 10 30 40 90 30 80 30
 90 80 80 50 40 30 30 30 30 10
 Program ended with exit code: 0
 */


