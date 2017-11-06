/***
 22B - PROGRAM 0A:
 ARRAYS and FUNCTIONS: SEARCHING using the Linear Search function
 // also known as Sequential Search
 
 Find and fix errors. Run the program once and save the output as a comment at the end
 of the source file.
 
 
 <Huimei Wu>
 <Xcode>
 
 */
#include <iostream>

using namespace std;

int search_List(int array[], int size, int target);

int main()
{
    int list[100] = {40, 30, 50, 13, 35, 48, 14, 31, 18, 33};
    int length = 10;
    
    for (int i = 0; i < length; i++)
    {
        cout << list[i] << " ";
    }
    cout << endl;
    
    for (int i = 0; i < 2 * length; i++) // SEARCH 20 times
    {
        int target = rand() % 41 + 10;  // generate a random target within the range 10 to 50
        int location = search_List(list, length, target);
        if (location != -1)
            cout << target << " FOUND at location: " << location << endl;
        else
            cout << target << " NOT found!" << endl;
    }
    
    return 0;
}

/***************************************************
 This function searches a list of integers for a given target
 It returns -1 if not found.
 It returns the index of the first element in the array that is equal to
 the target value.
 */
int search_List(int array[], int size, int target)
{
    int index = 0;   // Used as a subscript to search array
    int pos = -1;  // To record position of search value: -1 means not found
    
    while (index < size && pos == -1)
    {
        if (array[index] == target) // If the value is found
        {
            pos = index; // Record the value's subscript
        }
        index++; // Go to the next element
    }
    return pos; // Return the position, or -1
}

/************** OUTPUT
 40 30 50 13 35 48 14 31 18 33
 48 FOUND at location: 5
 19 NOT found!
 12 NOT found!
 12 NOT found!
 45 NOT found!
 35 FOUND at location: 4
 28 NOT found!
 30 FOUND at location: 1
 24 NOT found!
 22 NOT found!
 33 FOUND at location: 9
 47 NOT found!
 10 NOT found!
 47 NOT found!
 43 NOT found!
 22 NOT found!
 30 FOUND at location: 1
 47 NOT found!
 40 FOUND at location: 0
 23 NOT found!
 Program ended with exit code: 0
 */
