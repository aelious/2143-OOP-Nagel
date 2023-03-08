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

// Driver of the program
int main() {
    // Open output file
    ofstream outfile;
    outfile.open("test.out");
    
    // Print header for solution
    outfile << "Stephanie Nagel\nFebruary 27, 2023\nSpring 2143\n" << endl;

    List L;             // Creates a new linked list called L
    L.addNode(5);       // Adds a node to the linked list with data of 5.
    L.addNode(7);
    L.addNode(9);
    L.addNode(2);
    L.addNode(12);
    L.addNode(4);
    L.addEdge(1, 2);    // Adds an explicit edge between the first and second node.
    L.addEdge(4, 3);        
    L.addEdge(3, 4);
    L.addEdge(6, 2);
    L.printDOT();       // Prints the DOT notation of L to be visualized in graphviz

    BST B;              // Creates a new BST called B
    B.insert(8);        // Adds a new node to the BST at the root location.
    B.insert(3);        // Adds a new node to the BST at its appropriately sorted location.
    B.insert(10);
    B.insert(1);
    B.insert(6);
    B.insert(4);
    B.insert(7);
    B.insert(14);
    B.insert(13);
    B.printDOT();       // Prints the DOT notation of B to be visualized in graphviz
    return 0;   
}