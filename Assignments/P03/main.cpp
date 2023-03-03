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
    L.addNode(4);
    L.addEdge(1, 2);
    L.addEdge(4, 3);
    L.addEdge(3, 4);
    L.addEdge(6, 2);
    L.printDOT();

    BST B;
    B.insert(8);
    B.insert(3);
    B.insert(10);
    B.insert(1);
    B.insert(6);
    B.insert(4);
    B.insert(7);
    B.insert(14);
    B.insert(13);
    B.printDOT();
    return 0;
}