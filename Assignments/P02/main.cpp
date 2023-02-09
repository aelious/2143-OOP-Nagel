/*****************************************************************************
*                    
*  Author:           Stephanie Nagel
*  Email:            aeliousx@gmail.com
*  Label:            P02
*  Title:            Vector Class Part 2 - Overloading Operators
*  Course:           CMPS 2143
*  Semester:         Spring 2023
* 
*  Description:
*       This program implements a class that allows a singly-linked list to be used similarly
*       to a vector. The linked list can add and remove nodes with data values, search
*       existing nodes' values for a specific value, and it can be sorted in ascending
*       numerical order.  It also has print functionality to display the linked list similarly
*       to an array. Extending upon program 1, this program is capable of utilizing C++
*       operators to perform easy operations on our linked lists. This includes adding,
*       subtracting, multiplying, and dividing our lists, as well as concise printing and
*       easy indexing using bracket notation to access and modify the data of specific nodes.
*
*  Usage:
*       N/A
* 
*  Files:            
*       main.cpp    : driver program
*       vector.hpp  : header file with vector and node definitions
*****************************************************************************/
// main.cpp

#include <iostream>
#include <fstream>
#include "vector.hpp"
using namespace std;

// Main driver of the program
int main() {
    int a1[] = { 1, 2, 3, 4, 5 };
    int a2[] = { 10, 20, 30 };

    Vector v1(a1,5);
    Vector v2(a2,3);

    ofstream outfile;
    outfile.open("output.txt");
    outfile << "Stephanie Nagel\nFebruary 9, 2023\nSpring 2143\n" << endl;

    cout << v1[2] << endl;
    outfile << v1[2] << endl;

    v1[4] = 9;

    cout << v1 << endl;
    outfile << v1 << endl;

    Vector v3 = v1 + v2;
    cout << v3 << endl;
    outfile << v3 << endl;

    v3 = v2 - v1;
    cout << v3 << endl;
    outfile << v3 << endl;

    v3 = v1 * v2;
    cout << v3 << endl;
    outfile << v3 << endl;

    v3 = v1 / v2;
    cout << v3 << endl;
    outfile << v3 << endl;

    cout << (v2 == v1) << endl;
    outfile << (v2 == v1) << endl;

    Vector v4 = v1;
    cout << (v4 == v1) << endl;
    outfile << (v4 == v1) << endl;

    return 0;
}   
