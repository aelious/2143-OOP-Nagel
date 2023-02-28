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
//defaultGraphConfig.hpp

#include <string>

std::string bgSettings = "digraph Graphviz {\n\trankdir=LR\n\tbgcolor=\"black:purple\"\n\t"
    "label=\"Linked List\"\n\tfontcolor=white\n\tnode [fontcolor=black, style=filled, "
    "tailclip=true, fixedsize=true];\n\tnull [shape=circle, style=filled, color=\"yellow:red"
    "\"];\n\t";
std::string nullEdgeSettings = "null [arrowhead=inv, arrowtail=inv, dir=forward,"
    " tailclip=true, style=dotted, color=blue4];";