/********************************************************************************************
*                    
*  Author:           Stephanie Nagel
*  Email:            aeliousx@gmail.com
*  Label:            P03
*  Title:            Graphviz Class
*  Course:           CMPS 2143
*  Semester:         Spring 2023
* 
*  Description:
*       This program can create a linked list or a binary search tree. Both data structures
*       can accept new nodes and can be rendered digitally by generating the "DOT" language 
*       syntax. It can then be visualized via Graphviz compilers. The nodes and edges change
*       attributes based on the value of the data in the node and the direction of the arrows
*       in the edge. 
*
*  Usage:
*       N/A
* 
*  Files:            
*       main.cpp                : driver program
*       list.hpp                : header file with linked list & helper struct definitions
*       bst.hpp                 : header file with binary search tree & helper struct defns
*       
********************************************************************************************/
// main.cpp

// Included libraries:
#include "list.hpp"
#include "bst.hpp"
#include <iostream>
#include <fstream>

// Driver of the program
int main() {
    vector<int> linkedListData = {5, 7, 9, 2, 12, 4};
    vector<int> bstData = {8, 3, 10, 1, 6, 4, 7, 14, 13};
    // Open output file
    ofstream outfile;
    outfile.open("test.out");
    
    // Print header for solution
    outfile << "Stephanie Nagel\nFebruary 27, 2023\nSpring 2143\n" << endl;

    List L(linkedListData); // Creates new linked list L with nodes containing the vector data
    L.addEdge(1, 2);        // Adds an explicit edge between the first and second node
    L.addEdge(4, 3);        
    L.addEdge(3, 4);
    L.addEdge(6, 2);
    L.printDOT();           // Prints the DOT notation of L to be visualized in graphviz

    BST B(bstData);         // Creates a new binary search tree B with the data in the vector.
    B.printDOT();           // Prints the DOT notation of B to be visualized in graphviz
    return 0;   
}