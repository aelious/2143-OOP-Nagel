/*****************************************************************************
*                    
*  Author:           Stephanie Nagel
*  Email:            aeliousx@gmail.com
*  Label:            P01
*  Title:            Vector Class
*  Course:           CMPS 2143
*  Semester:         Spring 2023
* 
*  Description:
*       This program implements a class that allows a singly-linked list to be used similarly
*       to a vector. The linked list can add and remove nodes with data values, search
*       existing nodes' values for a specific value, and it can be sorted in ascending
*       numerical order.  It also has print functionality to display the linked list similarly
*       to an array.
*
*  Usage:
*       N/A
* 
*  Files:            
*       main.cpp    : driver program
*       vector.hpp  : header file with vector and node definitions
*       input.dat   : input file with values to test output
*****************************************************************************/
// main.cpp

#include <iostream>
#include <fstream>
#include "vector.hpp"
using namespace std;

// Main driver of the program
int main() {
    ofstream outfile;
    outfile.open("test.out");    
    outfile << "Stephanie Nagel\nFebruary 5, 2023\nSpring 2143\n" << endl;
    outfile.close();
    outfile.open("test.out", fstream::app);   
    int x = 0;

    Vector v1;
    v1.pushFront(18);
    v1.pushFront(20);
    v1.pushFront(25);
    v1.pushRear(18);
    v1.pushRear(20);
    v1.pushRear(25);
    v1.print();

    int A[] = {11,25,33,47,51};
    Vector v2(A,5);
    v2.print();

    v2.pushFront(9);
    v2.inOrderPush(27);
    v2.pushRear(63);
    v2.print();

    v1.pushRear(v2);
    v1.print();

    x = v1.popFront();
    x = v1.popFront();
    x = v1.popFront();
    v1.print();
    outfile << x << endl;
    cout << x << endl;

    x = v1.popRear();
    x = v1.popRear();
    x = v1.popRear();
    v1.print();
    outfile << x << endl;
    cout << x << endl;

    x = v2.popAt(3);
    v2.print();
    outfile << x << endl;
    cout << x << endl;

    x = v2.find(51);
    outfile << x << endl;
    cout << x << endl;

    x = v2.find(99);
    outfile << x << endl;
    cout << x << endl;

    Vector v3(v1);
    v3.print();

    v3.pushFront(v2);
    v3.print();

    Vector v4("input.dat");
    v4.pushRear(v3);
    v4.print();

    outfile.close();
    return 0;
}   
