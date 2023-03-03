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

// Included libraries:
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Default background settings in DOT notation for our BST data structure.
string bgSettingsBST = "digraph BST {\n\tbgcolor=\"deeppink:cyan\"\n\tlabel=\"BST\"\n\t"
    "fontcolor=white\n\tnode [fontcolor=black, style=filled, tailclip=true, shape=record"
    ", fixedsize=true];\n\t";

/**
 * bstNode
 * 
 * Description:
 *      This struct gives clear structure to each node in our binary search tree. It contains
 *      the pointers to the data in the left and right child nodes of the parent node.
 * 
 * Public Methods:
 *                          bstNode()           
 *                          bstNode(int data, int _id)
 *      void                printLabels() 
 *      void                printConnections()
 * 
 * Private Methods:
 *                          N/A
 * 
 * Usage: 
 *      *note: This struct is not meant to be used on its own although it can be.*
 *      bstNode someNode(12, 1);    // Makes a new node with data 12 and ID 1
 *      bstNode leftNode(10, 2);    // Makes a new node with data 10 and ID 2
 *      bstNode rightNode(14, 3);   // Makes a new node with data 14 and ID 3
 *      someNode->right = rightNode;// Sets the right child of someNode to rightNode
 *      someNode->right = leftNode; // Sets the left child of someNode to leftNode
 *      someNode.printLabels();     // Logs and outfiles the label of the node in DOT notation
 *      someNode.printConnections();// Logs and outfiles the children of someNode
 *      
 */
struct bstNode {
    int data;               // integer data contained in the node
    int id;                 // ID of the node
    ofstream outfile;       // file to output our results to
    bstNode *left;          // left child node
    bstNode *right;         // right child node

    // Default constructor. Not meant to be used really, but designed to initialize left and
    // right to NULL to prevent potential errors upon usage.
    bstNode() {
        outfile.open("test.out", ios::app);
        left = right = NULL;
    }

    // Constructor for bstNode, takes parameter inputs of the int data and the id of the node
    bstNode(int d, int _id) {
        outfile.open("test.out", ios::app);
        data = d;
        id = _id;
    }

    // Prints the DOT data structure for a node, containing the ID and label with the node's
    // data. Splits the record shape into two halves at the bottom for easier visualization.
    void printLabels() {
        if (id != 1) {
            cout << "\n\t";
        }
        cout << id << " [label=\"{<data> " << data << " | {<left> | <right>}}\"];";
        outfile << id << " [label=\"{<data> " << data << " | {<left> | <right>}}\"];";
    }
    
    // Prints the connections between the parent node and its left and right children, if they
    // exist.
    void printConnections() {
        string result = "";
        if (left) {
            result.append("\n\t" + to_string(id) + ":left -> " + to_string(left->id) + ";");
        }
        if (right) {
            result.append("\n\t" + to_string(id) + ":right -> " + to_string(right->id) + ";");
        }
        cout << result;
        outfile << result;
    }
};

/**
 * BST
 * 
 * Description:
 *      This class provides the functionality of a bstNode to be sorted into the binary search
 *      tree data structure. It creates a root node upon creation and, after being fed 
 *      additional data, creates new nodes that are placed as either left or right children 
 *      from the root node onward. The basic design of a binary search tree is that an initial
 *      value is maintained as the root value. The subsequent values are compared to the root
 *      value. If they are smaller, they go left in the tree, down the line of other lower
 *      nodes. If they are larger go right. They follow the same pattern until they reach a
 *      position in the tree that has not been defined yet.
 * 
 * Public Methods:
 *                          BST()       // Constructor for our BST. Sets root to NULL and
 *                                      // current ID to 1 in preparation for the initial
 *                                      // node.
 *      void               insert(int data)    // Calls the private method insert
 *                                              // with different parameters.
 *      void                printDOT()  // Logs and outfiles the DOT notation of the nodes in
 *                                      // the tree
 * 
 * Private Methods:
 *      bstNode*            insert(bstNode *node, int data) // Overloaded method which inserts
 *                                      // a new node with int data upon finding the proper
 *                                      // placement for it.
 *      void                print(bstNode *node)    // Recursively prints the data in every
 *                                      // node in the BST. Calls two other print methods
 *                                      // which also call their own different print methods
 *      void                printNodeConnections()   // Recursively calls the bstNode method
 *                                      // printConnections() on each node
 *      void                printNodeLabels()        // Recursively calls the bstNode method
 *                                      // printLabels() on each node
 * 
 * Usage: 
 *      BST B;                  // Creates new BST called B, B's root is set to NULL and ID=1
 *      B.insert(6);            // Inserts 6 into the BST. Will end up as the root node
 *      B.insert(12);           // Traverses B, finding itself as the right child of root
 *      B.insert(13);           // Traverses B, finding itself as the right child of the
 *                              // previous node
 *      B.insert(4);            // Traverses B, finding itself as the left child of root
 *      B.insert(5);            // Traverses B, finding itself as the right child of the
 *                              // previous node
 *      B.insert(6);            // Traverses B, finding itself as the right child of the
 *                              // previous node
 *      B.printDOT();           // Prints the DOT notation for our BST data structure.
 *                              // Calls the private print method that calls the other print
 *                              // methods, both in BST and bstNode.
 *      
 */
class BST {
private:
    bstNode *root;      // The root of the BST. The starting node, found at the top
    int curr_id;        // ID of the most recently inserted node. Allows for incrementation.
    ofstream outfile;   // Output file for our results after computation

    // Binary search tree insertion method, with added functionality of maintaining and
    // assigning an ID to the node upon insertion.
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

    // Print calls the two recursive print methods with an intake of where to start.
    void print(bstNode *node) {
        printNodeLabels(node);
        printNodeConnections(node); 
    }

    // Recursively calls the method of bstNode printConnections() allowing for each node to
    // print both its own data and the data of its left and right children, if they exist.
    void printNodeConnections(bstNode *node) {
        if (node == NULL) return;
        node->printConnections();
        printNodeConnections(node->left);
        printNodeConnections(node->right);
    }

    // Recursively calls the method of bstNode printLabels() allowing for each node to print
    // both its own data and the data of its left and right children, if they exist.
    void printNodeLabels(bstNode *node) {
        if (node == NULL) return;
        node->printLabels();
        printNodeLabels(node->left);
        printNodeLabels(node->right);
    }

public:
    // Default constructor for our binary search tree. Initializes the root node to NULL and
    // the starting ID to 1
    BST() {
        outfile.open("test.out", ios::app);
        curr_id = 1;
        root = NULL; 
    }

    // Calls the private method of the same name (with different parameters) using the root of
    // the tree as the base case and the integer data as the new node to be inserted.
    void insert(int data) {
        root = insert(root, data); 
    }

    // Prints the background settings for the BST graphviz followed by calling the private
    // print method. And finally, adds proper formatting for DOT notation.
    void printDOT() {
        cout << bgSettingsBST;
        outfile << bgSettingsBST;
        print(root);
        cout << "\n}\n";
        outfile << "\n}\n";
    }
};