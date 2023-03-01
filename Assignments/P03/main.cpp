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
//main.cpp

#include "list.hpp"
#include "bst.hpp"
#include <iostream>
#include <fstream>


int main() {
    ofstream outfile;
    outfile.open("test.out");
    outfile << "Stephanie Nagel\nFebruary 27, 2023\nSpring 2143\n" << endl;

    List L;
    L.addNode(5);
    L.addNode(7);
    L.addNode(9);
    L.addNode(2);
    L.addNode(13);
    L.addNode(8);
    L.addNode(12);
    L.addNode(4);
    L.addEdge(1, 2);
    L.addEdge(1, 3);
    L.addEdge(2, 4);
    L.addEdge(2, 5);
    L.addEdge(3, 6);
    L.addEdge(3, 7);

    L.printDOT();

    List N;
    N.addNode(5);
    N.addNode(29);
    N.addNode(20);
    N.addNode(15);
    N.addEdge(2, 3);
    N.printDOT();

    BST G;
    G.insert(2);
    G.insert(12);
    G.insert(5);
    G.insert(4);
    G.insert(3);
    G.print();
    return 0;
}