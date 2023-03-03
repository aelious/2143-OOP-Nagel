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
// bst.hpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string bgSettingsBST = "digraph BST {\n\tbgcolor=\"deeppink:cyan\"\n\tlabel=\"BST\"\n\t"
    "fontcolor=white\n\tnode [fontcolor=black, style=filled, tailclip=true, shape=record"
    ", fixedsize=true];\n\t";

struct bstNode {
    int data;
    int id;
    bstNode *left;
    bstNode *right;
    bstNode() {
        left = right = NULL;
    }
    bstNode(int d, int _id) {
        data = d;
        id = _id;
    }
    void printLabels() {
        if (id != 1) {
            cout << "\n\t";
        }
        cout << id << " [label=\"{<data> " << data << " | {<left> | <right>}}\"];";
        //cout << id << " [label=\"" << data << "\"];";
    }
    void printConnections() {
        string result = "";
        if (left) {
            result.append("\n\t" + to_string(id) + ":left -> " + to_string(left->id) + ";");
        }
        if (right) {
            result.append("\n\t" + to_string(id) + ":right -> " + to_string(right->id) + ";");
        }
        cout << result;
    }
};

struct bstEdge {

};

class BST {
private:
    bstNode *root;
    int curr_id;

    bstNode *insert(bstNode *node, int data) {
        if (node == NULL) {
            node = new bstNode();
            node->data = data;
            node->id = curr_id;
            curr_id += 1;
            node->left = NULL;
            node->right = NULL;
        } else if (data <= node->data) {
            node->left = insert(node->left, data);
        } else {
            node->right = insert(node->right, data);
        }
        return node;
    }

    void print(bstNode *node) {
        printNodeLabels(node);
        printNodeConnections(node); 
    }

    void printNodeConnections(bstNode *node) {
        if (node == NULL) return;
        node->printConnections();
        printNodeConnections(node->left);
        printNodeConnections(node->right);
    }

    void printNodeLabels(bstNode *node) {
        if (node == NULL) return;
        node->printLabels();
        printNodeLabels(node->left);
        printNodeLabels(node->right);
    }

/*     string printNodeData(bstNode *node) {
        
    } */

public:
    BST() {
        curr_id = 1;
        root = NULL; 
    }

    void insert(int data) {
        root = insert(root, data); 
    }

    void printDOT() {
        cout << bgSettingsBST;
        print(root);
        cout << "\n}\n";
    }
};