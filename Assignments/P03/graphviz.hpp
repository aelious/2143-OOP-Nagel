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
//graphviz.hpp

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include "defaultGraphConfig.hpp"
using namespace std;

/**
 * Node
 * 
 * Description:
 *      This struct provides the structure for a node in our linked list.
 * 
 * Public Methods:
 *                          Node(int x, int _id)    // Constructor
 * 
 * Private Methods:
 *                          N/A
 * 
 * Usage: 
 *      Node *newNode = Node(x);                    // Creates a new node with data x
 *      newNode->next = nextNode;                   // Singly links the node newNode
 *                                                  // to the node nextNode
 */

struct Node {
    int id;
    int data;
    Node *next;
    string shape;
    string color;
    Node(int x, int _id) {
        id = _id;
        data = x;
        next = nullptr;
    }
    
};

/**
 * Edge
 * 
 * Description:
 *      This struct provides the structure for an edge between nodes in our linked list.
 * 
 * Public Methods:
 *                          Node(int t)             // Constructor
 *      string              print()                 // Returns the edge attributes as a string
 * 
 * Private Methods:
 *                          N/A
 * 
 * Usage: 
 *      nodeMap[idFm].push_back(Edge(idTo));        // Creates an edge between 2 ids, saved in
 *                                                  // the vector value of our map of nodes in
 *                                                  // the Graphviz class below
 *      nodeMap[idFm][edgeIndex]->print();          // Returns the attributes in the edge
 */

struct Edge {
    int idTo;
    string arrowhead;
    string arrowtail;
    string direction;
    string color;
    Edge(int t) {
        idTo = t;
        direction = "none";
        arrowhead = "none";
        arrowtail = "dot";
        color = "mediumorchid1";
    }
    string print() {
        string result = "[arrowhead="+arrowhead+", arrowtail="+arrowtail+", dir="+direction;
        result.append(", color=\"" + color + "\", tailclip=true");
        if (direction == "none") {
            result.append(", style=dashed");
        }
        result.append("];");
        return result;
    }

};

/**
 * Graphviz
 * 
 * Description:
 *      This class provides the tools to create and add to a linked list and then convert the
 *      list into the DOT language for easy visualization in Graphviz compilation.
 * 
 * Public Methods:
 *                          Graphviz()              
 *      void                addNode(int data) 
 *      void                addEdge(int fm, int to)
 *      int                 findEdgeIndex(int fm, int to)
 *      void                removeEdge(int fm, int to)
 *      bool                foundEdge(int idFm, int idTo) 
 *      void                setMinMax(int data, int id) {
 *      void                setNodeAttributes(int id)
 *      string              printNodeAttributes(int id) 
 *      string              printEdgeAttributes(int id)
 *      void                printDOT()                 
 * 
 * Private Methods:
 *                          N/A
 * 
 * Usage: 
 *      Graphviz G;         // Initializes empty linked list
 *      G.addNode(4);       // Adds a new node with int data 4
 *      G.addNode(8);       // Adds a new node, linked to the previous node, with int data 8
 *      G.addNode(12);      // Adds a new node, linked to the previous node, with int data 12
 *      G.printDOT();       // Prints the DOT language for the linked list.
 * 
 */

class Graphviz {
    ofstream outfile;
    int curr_id;            // Holds the most recent id of the graphviz object
    int max;                // Max number in the node data set 
    int min;                // Min number in the node data set
    map<int, vector<Edge*>> nodeMap; //<ID, [vector<int>edgesFrom, vector<int>edgesTo]>
    Node *front;            // Holds the address of the start of our linked list.
    Node *tail;             // Holds the address of the end of our linked list.
public:
    /**
     * Public : Graphviz
     * 
     * Description:
     *      Default constructor, creates a linked list with nothing in it.
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      N/A
     */
    Graphviz() {
        outfile.open("test.out", ios::app);
        front = tail = nullptr;
        curr_id = 0;
    }

    void addNode(int data) {
        curr_id += 1;
        setMinMax(data, curr_id);
        Node *temp = new Node(data, curr_id);
        if (tail == nullptr) {
            front = tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
            if (curr_id - 1 != 0) {
                Edge *e = new Edge(curr_id);
                nodeMap[curr_id-1].push_back(e);
            }
        }
    }

    void addEdge(int fm, int to) {
        // If edge already exists
        if (foundEdge(fm, to)){
            int tempIndex = findEdgeIndex(fm, to);
            if (!foundEdge(to, fm)) {
                if (nodeMap[fm][tempIndex]->direction == "none") {
                    nodeMap[fm][tempIndex]->direction = "forward";
                    nodeMap[fm][tempIndex]->arrowhead = "vee";
                    nodeMap[fm][tempIndex]->color = "deeppink";
                    return;
                } else {
                    cout << "Edge already exists!\n";
                    return;
                }
            } else {
                int otherIndex = findEdgeIndex(to, fm);
                if (fm < to) {
                    nodeMap[fm][tempIndex]->direction = "both";
                    nodeMap[fm][tempIndex]->arrowtail = "normal";
                    nodeMap[fm][tempIndex]->arrowhead = "normal";
                    nodeMap[fm][tempIndex]->color = "mediumspringgreen:skyblue1";
                    removeEdge(to, fm);
                } else {
                    nodeMap[to][otherIndex]->direction = "both";
                    nodeMap[to][otherIndex]->arrowtail = "normal";
                    nodeMap[to][otherIndex]->arrowhead = "normal";
                    nodeMap[to][otherIndex]->color = "mediumspringgreen:skyblue1";
                    removeEdge(fm, to);
                }
            }
            
        } else {
            if (!foundEdge(to, fm)) {
                Edge *e = new Edge(to);
                e->direction = "forward";
                e->arrowhead = "vee";
                if (fm > to) {
                    e->color = "deeppink";
                } else e->color = "cyan";
                nodeMap[fm].push_back(e);
            } else {
                int otherIndex = findEdgeIndex(to, fm);
                if (nodeMap[to][otherIndex]->direction == "both") {
                    cout << "Edge already exists!\n";
                    return;
                } else if (nodeMap[to][otherIndex]->direction == "none") {
                    Edge *e = new Edge(to);
                    e->direction = "forward";
                    e->arrowtail = "vee";
                    e->arrowhead = "vee";
                    e->color = "skyblue1";
                    nodeMap[fm].push_back(e);
                    removeEdge(to, fm);
                }
                else {
                    if (fm < to) {
                        Edge *e = new Edge(to);
                        e->direction = "both";
                        e->arrowhead = "normal";
                        e->arrowtail = "normal";
                        e->color = "mediumspringgreen:skyblue1";
                        removeEdge(to, fm);
                    } else {
                        nodeMap[to][otherIndex]->direction = "both";
                        nodeMap[to][otherIndex]->arrowtail = "normal";
                        nodeMap[to][otherIndex]->arrowhead = "normal";
                        nodeMap[to][otherIndex]->color = "mediumspringgreen:skyblue1";
                    }
                }
            }
        }
    }

    int findEdgeIndex(int fm, int to) {
        int index = -1;
        for (int i = 0; i < nodeMap[fm].size(); i++) {
            if (nodeMap[fm][i]->idTo == to) {
                index = i;
                break;
            }
        }
        return index;
    }

    void removeEdge(int fm, int to) {
        int index = findEdgeIndex(fm, to);
        if (index == -1) {
            cout << "Edge not found in the node so it cannot be removed.\n";
            return;
        } else {
            nodeMap[fm].erase(nodeMap[fm].begin()+index);
        }
    }
    
    bool foundEdge(int idFm, int idTo) {
        for (int i = 0; i < nodeMap[idFm].size(); i++) {
            if (nodeMap[idFm][i]->idTo == idTo) {
                return true;
            }
        }
        return false;
    }
    
    void setMinMax(int data, int id) {
        if (id == 1) {
            min = max = data;
            return;
        }
        if (data < min) {
            min = data;
            return;
        }
        if (data > max) {
            max = data;
        }
    }

    void setNodeAttributes(int id) {
        int mid = (min+max)/2;
        int variance = ((mid - min)/2);
        Node *travel = front;
        while(travel->id != id && travel) travel = travel->next;
        // Gives variance to node attributes based on the data in the node
        if (travel->data >= min && travel->data < mid - ((mid - min)/2)) {
            travel->color = "\"cornflowerblue:blue4\"";
            travel->shape = "record";
        } else if (travel->data >= mid - variance && travel->data < mid + variance) {
            travel->color = "\"deeppink3:pink\"";
            travel->shape = "doublecircle";
        } else {
            travel->color = "\"darkgoldenrod3:gold\"";
            travel->shape = "star";
        }
    }

    string printNodeAttributes(int id) {
        string result = to_string(id) + " [label=\"";
        Node *travel = front;
        while(travel->id != id && travel) travel = travel->next;
        result.append(to_string(travel->data) + "\", shape="+travel->shape+", color=");
        result.append(travel->color+"];");
        return result;
    }

    string printEdgeAttributes(int id) {
        // For formatting: If last id in the map and not the first id
        if (id == curr_id && id != 1) {
            return ("\n\t" + to_string(id) + " -> " + nullEdgeSettings);
        } else if (id == curr_id && id == 1) { // If it's the last and first id (Only 1 node):
            return (to_string(id) + " -> " + nullEdgeSettings);
        }
        string result = "";
        for (int i = 0; i < nodeMap[id].size(); i++) {
            if (id != 1) {
                result.append("\n\t");
            }
            result.append(to_string(id) + " -> " + to_string(nodeMap[id][i]->idTo)+":data ");
            result.append(nodeMap[id][i]->print());
        }
        return result;
    }

    void printDOT() {
        Node *travel = front;
        if (!travel) {
            bgSettings.pop_back();
            cout << bgSettings <<"}" << endl;
            outfile << bgSettings << "}" << endl;
            return;
        }
        string result = "";
        result.append(bgSettings);
        while(travel) {
            setNodeAttributes(travel->id);
            result.append(printNodeAttributes(travel->id) + "\n\t");
            travel = travel->next;
        }
        travel = front;
        while(travel) {
            result.append(printEdgeAttributes(travel->id));
            travel = travel->next;
        }
        result.append("\n}\n");
        outfile << result << endl;
        cout << result << endl;
    }
        
};


