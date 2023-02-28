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
*       This program creates a linked list with edge adding functionality. The linked list can
*       be rendered digitally by generating the "DOT" language syntax for the linked list. 
*       It can then be visualized via Graphviz compilers. The nodes and edges change
*       attributes based on the value of the data in the node and the direction of the arrows
*       in the edge.
*
*  Usage:
*       N/A
* 
*  Files:            
*       main.cpp                : driver program
*       graphviz.hpp            : header file with node, edge, and graphviz definitions
*       defaultGraphConfig.hpp  : header file with default settings for the DOT graph
*       
********************************************************************************************/
//main.cpp

#include "graphviz.hpp"
#include <iostream>
#include <fstream>


int main() {
    ofstream outfile;
    outfile.open("test.out");
    outfile << "Stephanie Nagel\nFebruary 27, 2023\nSpring 2143\n" << endl;

    Graphviz L;
    L.addNode(5);
    L.addNode(7);
    L.addNode(9);
    L.addNode(2);
    L.addEdge(1, 2);
    L.addEdge(2, 3);
    L.addEdge(3, 2);
    L.printDOT();

    Graphviz N;
    N.addNode(5);
    N.addNode(29);
    N.addNode(20);
    N.addNode(15);
    N.addEdge(2, 3);
    N.printDOT();
    return 0;
}