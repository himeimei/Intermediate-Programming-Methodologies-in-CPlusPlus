/**
 CIS 22B: Homework 5A
 This program creates a Rectangle object, then displyas the length, with, and area of the rectangle.
 Change this program to calculate and display the perimeter of the rectangle. Run the program once and
 save the output as a comment at the end of this source file.
 NAME: Huimei Wu
 ============================================================================================= */
// This program calls the Rectangle class constructor.
#include <iostream>
#include <iomanip>
#include "Rectangle.h"
using namespace std;

int main()
{
    double houseWidth,   // To hold the room width
    houseLength;  // To hold the room length
    
    // Get the width of the house.
    cout << "In feet, how wide is your house? ";
    cin >> houseWidth;
    
    // Get the length of the house.
    cout << "In feet, how long is your house? ";
    cin >> houseLength;
    
    // Create a Rectangle object.
    Rectangle house(houseWidth, houseLength );
    
    // Display the house's width, length, and area.
    cout << setprecision(2) << fixed;
    cout << "The house is " << house.getWidth()
    << " feet wide.\n";
    cout << "The house is " << house.getLength()
    << " feet long.\n";
//    cout << "The house has " << house.getArea()
//    << " square feet of area.\n";
    // Display the perimeter below
    cout << "The house has " << house.getPerimeter()
    << " feet of perimeter.\n";
    return 0;
}
/***************************************************************
 Save the OUTPUT below
 In feet, how wide is your house? 5
 In feet, how long is your house? 10
 The house is 5.00 feet wide.
 The house is 10.00 feet long.
 The house has 30.00 feet of perimeter.
 Program ended with exit code: 0 */

