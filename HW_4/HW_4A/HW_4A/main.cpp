/**
 CIS 22B: Homework 4A
 c-strings manipulation functions
 
 Using string manipulation functions: Write a function that given a string of words
 removes the last word and inserts it in the beginning of the string. All words are
 separated by spaces. You may assume that there is only one space between two words.
 Strings that are either empty or consists of only one word will not be changed.
 // HINT: Use a temp string
 
 Example:            "Two Three Four Five One"
 After processing: "One Two Three Four Five"
 
 Save the output as a comment at the end of the program.
 
 NAME: Huimei Wu
 ============================================================================================= */
#include <iostream>
#include <cstring>
using namespace std;


bool moveFront( char s[] );

int main( void )
{
    char sList[5][100] = {"Two Three Four Five One", "Two One Three", "Second First", "", "OnlyOne!"};
    bool change;
    
    // test the function with 5 strings
    for (int i = 0; i < 5; i++)
    {
        cout << "Before: [" << sList[i] << "]\n";
        change = moveFront(sList[i]);
        cout << " After: [" << sList[i] << "]\n";
        if (!change)
            cout << "\t\t The string is either empty or it has only one word!\n";
    }
    return 0;
}

/* ============================================= */
bool moveFront( char s[] )
{
    char tmp[100];
    char * ptr = nullptr;

    // Try to find the last occurence of " " in s
    ptr = strrchr(s, ' ');
    
    // If s doesn't have " ", return false
    if (ptr == nullptr) {
        return false;
    }

    // Copy the last word (from pty+1 to the end of s)
    // to tmp
    strcpy(tmp, ptr+1);
    // Append " " in the end of tmp
    strcat(tmp, " ");
    // Replace " " before the last word of s to "\0"
    *ptr = '\0';

    // Append s to tmp
    strcat(tmp, s);
    
    // Copy the modified string back to s
    strcpy(s, tmp);

    return true;
}


/***************************************************************
 Before: [Two Three Four Five One]
 After: [One Two Three Four Five]
 Before: [Two One Three]
 After: [Three Two One]
 Before: [Second First]
 After: [First Second]
 Before: []
 After: []
 The string is either empty or it has only one word!
 Before: [OnlyOne!]
 After: [OnlyOne!]
 The string is either empty or it has only one word!
 Program ended with exit code: 0
 
 */
