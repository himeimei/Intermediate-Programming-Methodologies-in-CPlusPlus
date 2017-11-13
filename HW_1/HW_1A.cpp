/***
 22B - PROGRAM 1A:
 Binary Search
 
 Find and fix errors. Run the program once and save the output as a comment at the end
 of the source file.
 
 
 <Huimei Wu>
 <Xcode>
 
 */
#include <iostream>

using namespace std;

int binarySearch(const int array[], int numElems, int value);

int main()
{
    int list[100] = {5, 5, 8, 8, 8, 8, 8, 9, 9, 10};
    int length = 10;
    
    for (int i = 0; i < length; i++)
    {
        cout << list[i] << " ";
    }
    cout << endl;
    
    for (int i = 0; i < 2 * length; i++) // SEARCH 20 times
    {
        int target = rand() % 6 + 5;  // generate a random target within the range 5 to 10
        int location = binarySearch(list, length, target);
        if (location == - 1)
            cout << target << " NOT found!" << endl;
        else
        {
            // print a range: from index A to Z, inclusive!
            int z = location + 1;
            while( z < length && list[z] == list[location] )
                z++;
            z--;
            
            int a = location - 1;
            while( a >= 0 && list[a] == list[location] )
                a--;
            a++;
            
            if ( a != z )
            {
                cout << target << " found from index "
                << a << " to " << z << endl;
            }
            else
                cout << target << " found at location " << location << endl;
        }
        
    }
    
    return 0;
}

/***************************************************************
 Definition of binarySearch function
 The binarySearch function performs a binary search on an
 integer array. array, which has a maximum of numElems
 elements, is searched for the number stored in value. If the
 number is found, its array subscript is returned. Otherwise,
 -1 is returned indicating the value was not in the array.
 */

int binarySearch(const int array[], int numElems, int value)
{
    int first = 0,         // First array element
    last = numElems - 1, // Last array element
    middle,                 // Midpoint of search
    position = -1;         // Position of search value
    // Assume not found
    
    while (position == -1 && first <= last)
    {
        middle = (first + last) / 2;  // Calculate midpoint
        if (array[middle] == value)      // If value is found at mid
        {
            position = middle;
        }
        else if (array[middle] > value) // If value is in lower half
            last = middle - 1;
        else
            first = middle + 1;            // If value is in upper half
    }
    return position;
}

/************** OUTPUT
 5 5 8 8 8 8 8 9 9 10
 6 NOT found!
 6 NOT found!
 10 found at location 9
 7 NOT found!
 9 found from index 7 to 8
 7 NOT found!
 5 found from index 0 to 1
 7 NOT found!
 10 found at location 9
 6 NOT found!
 5 found from index 0 to 1
 10 found at location 9
 5 found from index 0 to 1
 7 NOT found!
 8 found from index 2 to 6
 10 found at location 9
 6 NOT found!
 6 NOT found!
 9 found from index 7 to 8
 9 found from index 7 to 8
 Program ended with exit code: 0
 */

