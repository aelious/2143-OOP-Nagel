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
 *                          bstNode(int d, int _id)
 *      void                printLabels(ofstream& outfile) 
 *      void                printConnections(ofstream& outfile)
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
 *      someNode->left = leftNode;  // Sets the left child of someNode to leftNode
 *      someNode.printLabels();     // Logs and outfiles the label of the node in DOT notation
 *      someNode.printConnections();// Logs and outfiles the children of someNode
 *      
 */
struct bstNode {
    int data;               // integer data contained in the node
    int id;                 // ID of the node
    bstNode *left;          // left child node
    bstNode *right;         // right child node

    /**
     * Public : bstNode
     * 
     * Description:
     *      Default constructor. Not meant to be used really, but designed to initialize 
     *      left and right to NULL to prevent potential errors upon usage.
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      N/A
     */
    bstNode() {
        left = right = NULL;
    }

    /**
     * Public : bstNode
     * 
     * Description:
     *      Overloaded constructor for bstNode, takes parameter inputs of the int data and 
     *      the id of the node
     * Params:
     *      int         : data to be included in the new node
     *      int         : id given to the new node (for proper printing)
     * 
     * Returns:
     *      bstNode *   : the root of the new tree (recursively)
     */
    bstNode(int d, int _id) {
        data = d;
        id = _id;
    }

    /**
     * Public : printLabels
     * 
     * Description:
     *      Prints the DOT data structure for a node, containing the ID and label with the 
     *      node's data. Splits the record shape into two halves at the bottom for easier 
     *      visualization.
     * 
     * Params:
     *      ofstream &  : where to print the data to
     * 
     * Returns:
     *      N/A
     */
    void printLabels(ofstream &outfile) {
        if (id != 1) {
            cout << "\n\t";
            outfile << "\n\t";
        }
        cout << id << " [label=\"{<data> " << data << " | {<left> | <right>}}\"];";
        outfile << id << " [label=\"{<data> " << data << " | {<left> | <right>}}\"];";
    }
    
    /**
     * Public : printConnections
     * 
     * Description:
     *      Prints the connections between the parent node and its left and right children, 
     *      if they exist. Uses proper DOT syntax
     * 
     * Params:
     *      ofstream &  : where to print the data to
     * 
     * Returns:
     *      N/A
     */
    void printConnections(ofstream &outfile) {
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
 *                          BST()
 *      void                insert(int data)
 *      void                printDOT()
 * 
 * Private Methods:
 *      bstNode*            insert(bstNode *node, int data)
 *      void                print(bstNode *node)
 *      void                printNodeConnections()
 *      void                printNodeLabels()
 *      void                randomBST()
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

    /**
     * Private : insert
     * 
     * Description:
     *      Binary search tree insertion method, with added functionality of maintaining and
     *      assigning an ID to the node upon insertion.
     * 
     * Params:
     *      bstNode *   : node whose data is to be compared with the data of the new node
     *      int         : data to be included in the new node
     * 
     * Returns:
     *      bstNode *   : the root of the new tree (recursively)
     */
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

    /**
     * Private : print
     * 
     * Description:
     *      Print calls the two recursive print methods with an intake of where to start.
     * 
     * Params:
     *      bstNode *   : Node of where to begin the print process.
     * 
     * Returns:
     *      N/A
     */
    void print(bstNode *node) {
        printNodeLabels(node);
        printNodeConnections(node); 
    }

    /**
     * Private : printNodeConnections
     * 
     * Description:
     *      Recursively calls the method of bstNode printConnections() allowing for each node to
     *      print both its own data and the data of its left and right children, if they exist.
     * 
     * Params:
     *      bstNode *   : Node of where to begin the print process.
     * 
     * Returns:
     *      N/A
     */
    void printNodeConnections(bstNode *node) {
        if (node == NULL) return;
        node->printConnections(outfile);
        printNodeConnections(node->left);
        printNodeConnections(node->right);
    }

    /**
     * Private : BST
     * 
     * Description:
     *      Recursively calls the method of bstNode printLabels() allowing for each node to print
     *      both its own data and the data of its left and right children, if they exist.
     * 
     * Params:
     *      bstNode *   : Node of where to begin the print process.
     * 
     * Returns:
     *      N/A
     */
    void printNodeLabels(bstNode *node) {
        if (node == NULL) return;
        node->printLabels(outfile);
        printNodeLabels(node->left);
        printNodeLabels(node->right);
    }

public:
    /**
     * Public : BST
     * 
     * Description:
     *      Default constructor for the binary search tree class. Sets the current id to 1
     *      and the root node to null. Also opens the output file in append mode.
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      N/A
     */
    BST() {
        outfile.open("test.out", ios::app);
        curr_id = 1;
        root = NULL; 
    }

    /**
     * Public : insert
     * 
     * Description:
     *      Sets the root to the node containing the new info by calling the private insert
     *      method of the same name. Essentially finds the correct position of the new node
     *      and then sends that complete linked node collection back to root. 
     * 
     * Params:
     *      int     : data to be saved in the newly inserted node object
     * 
     * Returns:
     *      N/A
     */
    void insert(int data) {
        root = insert(root, data); 
    }

    /**
     * Public : printDOT
     * 
     * Description:
     *      Prints the background settings for our graphviz visualization followed by calling
     *      the private method print using root as the starting point. Finally, adds a closing
     *      bracket to the output for proper DOT syntax.
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      N/A
     */
    void printDOT() {
        // Prevents errors when printDOT is run twice on the same BST
        if (!outfile.is_open()) {
            outfile.open("test.out", ios::app);
        };
        cout << bgSettingsBST;
        outfile << bgSettingsBST;
        print(root);
        outfile << "\n}\n\n";
        cout << "\n}\n\n";
        outfile.close();
    }

    /**
     * Public : randomizeBST
     * 
     * Description:
     *      Creates 20 nodes with random integers between 1 & 20. Used to check for accuracy
     *      in code.
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      N/A
     */
    void randomizeBST() {
        srand((unsigned) time(NULL));
        // Create 20 nodes with random integers 1 - 20
        for (int i = 0; i < 20; i++) {
            this->insert(rand() % 20 + 1);
        }
    }
};