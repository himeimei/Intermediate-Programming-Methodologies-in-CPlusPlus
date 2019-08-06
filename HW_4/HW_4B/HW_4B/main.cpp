/**
 CIS 22B: Homework 4B
 Arrays of c-strings.
 
 This program uses a selection sort to sort an array of c-strings.
 It has some errors. Fix the errors and run the program.
 Save the output as a comment at the end of the program.
 
 NAME: Huimei Wu
 */

#include <iostream>
#include <cstring>
using namespace std;


void selectionSort( const char *list[],  int size );

int main( void )
{
    const char *list[10] = {"Mary", "John", "Peter", "Anne",
        "Paul",  "Andrew", "Linda",  "Diane"};
    int size = 8;  // 8 names in the list
    
    selectionSort( list, size );
    
    for (int i = 0; i < size; i++)
    {
        cout << list[i] << " ";
    }
    cout << endl;
    
    return 0;
}

/** ============================================================== */
/** This function sorts a list of strings using a selection sort
 algorithm.
 Given: ary  - a list of strings
 size   - its actual size
 */
void selectionSort( const char *list[],  int size )
{
    const char *hold;
    int last;
    int small;
    int curr;
    int walk;
    
    last = size - 1;
    for(curr = 0; curr < last; curr++ )
    {
        small = curr;
        for( walk = curr + 1; walk < size; walk++ )
        {
            // Error: need use strcmp function to compare
            // char array
            // if( list[walk] < list[small] )
            if (strcmp(list[walk], list[small]) < 0)
            {
                small = walk;
            }
        }
        
        hold = list[small];
        list[small] = list[curr];
        list[curr] = hold;
    }
    return;
}
/***************************************************************
 Save the OUTPUT below
 
 Andrew Anne Diane John Linda Mary Paul Peter
 Program ended with exit code: 0

 */

