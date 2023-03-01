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
//list.hpp

// Included libraries:
#include <vector>
#include <string>                   
#include <map>
#include <iostream>
#include <fstream>
// Namespace for the program:
using namespace std;

// These are the default background settings for our linked list in DOT. The color and 
// direction of flow is set as well as some default attributes for null and our different 
// nodes.
string bgSettingsList = "digraph LinkedList {\n\trankdir=LR\n\tbgcolor=\"black:purple\"\n\t"
    "label=\"Linked List\"\n\tfontcolor=white\n\tnode [fontcolor=black, style=filled, "
    "tailclip=true, fixedsize=true];\n\tnull [shape=circle, style=filled, color=\"yellow:red"
    "\"];\n\t";

// These are our default null edge settings. They are used when an object points to null.
string nullEdgeSettings = "null [arrowhead=inv, arrowtail=inv, dir=forward,"
    " tailclip=true, style=dotted, color=blue4];";

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

struct listNode {
    int id;
    int data;
    listNode *next;
    string shape;
    string color;
    listNode(int x, int _id) {
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
 *      nodeEdgeMap[idFm].push_back(Edge(idTo));        // Creates an edge between 2 ids, saved in
 *                                                  // the vector value of our map of nodes in
 *                                                  // the Graphviz class below
 *      nodeEdgeMap[idFm][edgeIndex]->print();          // Returns the attributes in the edge
 */

struct listEdge {
    int idTo;
    map<string, string> attributes;

    listEdge(int to) {
        idTo = to;
        attributes["direction"] = "none";
        attributes["arrowhead"] = "none";
        attributes["arrowtail"] = "dot";
        attributes["color"] = "mediumorchid1";
    }

    string print() {
        string result = "[";
        for (auto a : attributes) {
            result.append(a.first + "=" + a.second + ", ");
        }
        if (attributes["direction"] == "none") {
            result.append("style=dashed];");
        } else {
            result.pop_back();
            result.pop_back();
            result.append("];");
        } 
        return result;
    }

};

/**
 * List
 * 
 * Description:
 *      This class provides the tools to create and add to a linked list and then convert the
 *      list into the DOT language for easy visualization in Graphviz compilation.
 * 
 * Public Methods:
 *                          List()           
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
 *      List G;             // Initializes empty linked list
 *      G.addNode(4);       // Adds a new node with int data 4
 *      G.addNode(8);       // Adds a new node, linked to the previous node, with int data 8
 *      G.addNode(12);      // Adds a new node, linked to the previous node, with int data 12
 *      G.addEdge(1, 2);    // Creates an explicit edge between the first node and second node
 *      G.printDOT();       // Prints the DOT language for the linked list.
 * 
 */

class List {
    ofstream outfile;
    int curr_id;            // Holds the most recent id of the graphviz object
    int max;                // Max number in the node data set 
    int min;                // Min number in the node data set
    map<int, vector<listEdge*>> nodeEdgeMap; //<ID, vector<int>edgesTo>
    listNode *front;            // Holds the address of the start of our linked list.
    listNode *tail;             // Holds the address of the end of our linked list.

public:

    /**
     * Public : Graphviz
     * 
     * Description:
     *      Default constructor, creates a linked list with nothing in it and opens our output
     *      file for appending new computations.
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      N/A
     */
    List() {
        outfile.open("test.out", ios::app);
        front = tail = nullptr;
        curr_id = 0;
    }

    /**
     * Public : addNode
     * 
     * Description:
     *      Adds a node to the linked list, lightly connecting it to the previous node
     *      (if one exists) with a dashed edge and assigning the node an id unique to the
     *      current object.
     * 
     * Params:
     *      int     : data to be saved in the node object
     * 
     * Returns:
     *      N/A
     */
    void addNode(int data) {
        curr_id += 1;
        setMinMax(data, curr_id);
        listNode *temp = new listNode(data, curr_id);
        if (tail == nullptr) {
            front = tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
            if (curr_id - 1 != 0) {
                listEdge *e = new listEdge(curr_id);
                nodeEdgeMap[curr_id-1].push_back(e);
            }
        }
    }

    /**
     * Public : addEdge
     * 
     * Description:
     *      Creates an explicit edge between two nodes. If the nodes are already linked
     *      one-way (the opposite direction), the smaller id of the two nodes will become
     *      a bidirectional edge and the other edge will be erased. If there is no preexisting
     *      connecton between the two nodes, an explicit edge with a forward direction to the
     *      other node will be created.
     * 
     * Params:
     *      int     : id of the node where the new edge will come from
     *      int     : id of the node where the new edge will point to
     * 
     * Returns:
     *      N/A
     */
    void addEdge(int fm, int to) {
        // If either node doesn't exist:
        listNode *travel = front;
        bool fmTest = false;
        bool toTest = false;
        while(travel) {
            if(travel->id == fm) {
                fmTest = true;
            }
            if(travel->id == to) {
                toTest = true;
            }
            travel = travel->next;
        }
        // Print a message stating that it can't be added
        if(!fmTest || !toTest) {
            cout << "One or both of these nodes does not exist, therefore a new edge cannot";
            cout << " be made." << endl;
            return;
        }
        // If edge already exists:
        if (foundEdge(fm, to)){
            int tempIndex = findEdgeIndex(fm, to);
            if (!foundEdge(to, fm)) {
                // If the found edge is the default edge and it's one-way:
                if (nodeEdgeMap[fm][tempIndex]->attributes["direction"] == "none") {
                    nodeEdgeMap[fm][tempIndex]->attributes["direction"] = "forward";
                    nodeEdgeMap[fm][tempIndex]->attributes["arrowhead"] = "vee";
                    if(fm > to) {
                        nodeEdgeMap[fm][tempIndex]->attributes["color"] = "deeppink";
                    } else {
                        nodeEdgeMap[fm][tempIndex]->attributes["color"] = "cyan";
                    }
                    return;
                } else {
                    cout << "Edge already exists!\n";
                    return;
                }
            } else {
                // If there is some connection between both nodes already:
                int otherIndex = findEdgeIndex(to, fm);
                // The lower id index keeps the edge and sets the direction to both
                // while the other edge of the higher id is deleted.
                if (fm < to) {
                    nodeEdgeMap[fm][tempIndex]->attributes["direction"] = "both";
                    nodeEdgeMap[fm][tempIndex]->attributes["arrowtail"] = "normal";
                    nodeEdgeMap[fm][tempIndex]->attributes["arrowhead"] = "normal";
                    nodeEdgeMap[fm][tempIndex]->attributes["color"] = "mediumspringgreen"
                    ":coral1";
                    removeEdge(to, fm);
                } else {
                    nodeEdgeMap[to][otherIndex]->attributes["direction"] = "both";
                    nodeEdgeMap[to][otherIndex]->attributes["arrowtail"] = "normal";
                    nodeEdgeMap[to][otherIndex]->attributes["arrowhead"] = "normal";
                    nodeEdgeMap[to][otherIndex]->attributes["color"] = "mediumspringgreen"
                    ":coral1";
                    removeEdge(fm, to);
                }
            }
            
        } else {
            // If no edge is found between either node:
            if (!foundEdge(to, fm)) {
                listEdge *e = new listEdge(to);
                e->attributes["direction"] = "forward";
                e->attributes["arrowhead"] = "vee";
                // Assign a different color based on if the node points forward or backward
                // in id (If 2 points to 1, the color will be deeppink, otherwise it's cyan)
                if (fm > to) {
                    e->attributes["color"] = "deeppink";
                } else e->attributes["color"] = "cyan";
                nodeEdgeMap[fm].push_back(e);
            } else {
                int otherIndex = findEdgeIndex(to, fm);
                if (nodeEdgeMap[to][otherIndex]->attributes["direction"] == "both") {
                    cout << "Edge already exists!\n";
                    return;
                } else if (nodeEdgeMap[to][otherIndex]->attributes["direction"] == "none") {
                    listEdge *e = new listEdge(to);
                    e->attributes["direction"] = "forward";
                    e->attributes["arrowtail"] = "vee";
                    e->attributes["arrowhead"] = "vee";
                    e->attributes["color"] = "deeppink";
                    nodeEdgeMap[fm].push_back(e);
                    removeEdge(to, fm);
                }
                else {
                    if (fm < to) {
                        listEdge *e = new listEdge(to);
                        e->attributes["direction"] = "both";
                        e->attributes["arrowhead"] = "normal";
                        e->attributes["arrowtail"] = "normal";
                        e->attributes["color"] = "mediumspringgreen:coral1";
                        removeEdge(to, fm);
                    } else {
                        nodeEdgeMap[to][otherIndex]->attributes["direction"] = "both";
                        nodeEdgeMap[to][otherIndex]->attributes["arrowtail"] = "normal";
                        nodeEdgeMap[to][otherIndex]->attributes["arrowhead"] = "normal";
                        nodeEdgeMap[to][otherIndex]->attributes["color"] = "mediumspringgreen"
                        ":coral1";
                    }
                }
            }
        }
    }

    int findEdgeIndex(int fm, int to) {
        int index = -1;
        for (int i = 0; i < nodeEdgeMap[fm].size(); i++) {
            if (nodeEdgeMap[fm][i]->idTo == to) {
                index = i;
                break;
            }
        }
        return index;
    }

    void removeEdge(int fm, int to) {
        int index = findEdgeIndex(fm, to);
        // If edge isn't found, print message and do nothing, otherwise delete the edge.
        if (index == -1) {
            cout << "Edge not found in the node so it cannot be removed.\n";
            return;
        } else {
            nodeEdgeMap[fm].erase(nodeEdgeMap[fm].begin()+index);
        }
    }
    
    bool foundEdge(int idFm, int idTo) {
        // Searches for the edge in the nodeEdgeMap
        for (int i = 0; i < nodeEdgeMap[idFm].size(); i++) {
            if (nodeEdgeMap[idFm][i]->idTo == idTo) {
                return true;
            }
        }
        return false;
    }
    
    void setMinMax(int data, int id) {
        // Set default min and max
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
        listNode *travel = front;
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
        string result = "";
        // Provides proper formatting:
        if (id != 1) {
            result.append("\n\t");
        }
        // Will look like: id [label=id->data, shape=id->shape, color=id->color];
        result.append(to_string(id) + " [label=\"");
        listNode *travel = front;
        while(travel->id != id && travel) travel = travel->next;
        result.append(to_string(travel->data) + "\", shape="+travel->shape+", color=");
        result.append(travel->color+"];");
        return result;
    }

    string printEdgeAttributes(int id) {
        // For formatting: If last id in the map and has no edges
        if (id == curr_id && nodeEdgeMap[id].empty()) {
            return ("\n\t" + to_string(id) + " -> " + nullEdgeSettings);
        }
        string result = "";
        for (int i = 0; i < nodeEdgeMap[id].size(); i++) {
            // idFrom -> idTo:data [edgeSettings];
            result.append("\n\t" + to_string(id) + ":e -> " + to_string(nodeEdgeMap[id][i]->idTo));
            result.append(":w " + nodeEdgeMap[id][i]->print());
            // If it's the last node, append null edge and settings at the end
            if (id == curr_id) {
                result.append(("\n\t" + to_string(id) + " -> " + nullEdgeSettings));
            }
        }
        return result;
    }

    void printDOT() {
        listNode *travel = front;
        if (!travel) {
            bgSettingsList.pop_back();
            cout << bgSettingsList <<"}" << endl;
            outfile << bgSettingsList << "}" << endl;
            return;
        }
        string result = "";
        result.append(bgSettingsList);
        while(travel) {
            setNodeAttributes(travel->id);
            result.append(printNodeAttributes(travel->id));
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
