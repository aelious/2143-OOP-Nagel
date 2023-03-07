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
// list.hpp

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
 * listNode
 * 
 * Description:
 *      This struct provides the structure for a node in our linked list.
 * 
 * Public Methods:
 *                          listNode(int x, int _id)// Constructor
 * 
 * Private Methods:
 *                          N/A
 * 
 * Usage: 
 *      listNode newNode(x, _id);           // Creates a new node with data x and id of _id
 *      newNode->next = nextNode;           // Singly links the node newNode to nextNode
 *                                          
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
 * listEdge
 * 
 * Description:
 *      This struct provides the structure for an edge between nodes in our linked list.
 * 
 * Public Methods:
 *                          listEdge(int t)         // Constructor for an edge. Sets default
 *                                                  // attributes and the ID that it's 
 *                                                  // pointing to.
 *      string              print()                 // Returns the edge attributes as a string
 *                                                  // in DOT notation.
 * 
 * Private Methods:
 *                          N/A
 * 
 * Usage: 
 *      nodeEdgeMap[idFm].push_back(Edge(idTo));    // Creates an edge between 2 ids, saved in
 *                                                  // the vector value of our map of nodes in
 *                                                  // the Graphviz class below
 *      nodeEdgeMap[idFm][edgeIndex]->print();      // Returns the attributes in the edge
 */
struct listEdge {
    int idTo;                       // ID that the edge is pointing to
    map<string, string> attributes; // Map of edge attributes in DOT format.
    listEdge(int to) {
        idTo = to;
        attributes["dir"] = "none";
        attributes["arrowhead"] = "none";
        attributes["arrowtail"] = "dot";
        attributes["color"] = "mediumorchid1";
    }

    // Returns the edge attributes as a string in DOT notation:
    // after "1 -> 2" format declaration: [edgeAttribute1=value, edgeAttribute2=value, etc];
    string print() {
        string result = "[";
        for (auto a : attributes) {
            result.append(a.first + "=" + a.second + ", ");
        }
        // Adds a dashed style to the edge if it is a default edge.
        if (attributes["dir"] == "none") {
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
 *      void                setMinMax(int data, int id)
 *      string              printNodeAttributes() 
 *      string              printEdgeAttributes()
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
    int variance;           // Holds 1/3 of the max - min so it can assign nodes different
                            // attributes depending on their held data
    map<int, vector<listEdge*>> nodeEdgeMap; //<ID, vector<pointer to list edge>>
    listNode *front;            // Holds the address of the start of our linked list.
    listNode *tail;             // Holds the address of the end of our linked list.

public:

    /**
     * Public : List
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
     *      other node will be created. I debated making this a nested switch controller but
     *      I think it's plenty complicated already haha.
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
                if (nodeEdgeMap[fm][tempIndex]->attributes["dir"] == "none") {
                    nodeEdgeMap[fm][tempIndex]->attributes["dir"] = "forward";
                    nodeEdgeMap[fm][tempIndex]->attributes["arrowhead"] = "vee";
                    nodeEdgeMap[fm][tempIndex]->attributes["color"] = "cyan";
                    return;
                }
                // If the found edge is the edge of a higher id pointing to the lower id,
                // make the edge bidirectional.
                else if (nodeEdgeMap[fm][tempIndex]->attributes["dir"] == "back"){
                    nodeEdgeMap[fm][tempIndex]->attributes["dir"] = "both";
                    nodeEdgeMap[fm][tempIndex]->attributes["arrowtail"] = "normal";
                    nodeEdgeMap[fm][tempIndex]->attributes["arrowhead"] = "normal";
                    nodeEdgeMap[fm][tempIndex]->attributes["color"] = "\"mediumspringgreen"
                    ":coral1\"";
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
                    nodeEdgeMap[fm][tempIndex]->attributes["dir"] = "both";
                    nodeEdgeMap[fm][tempIndex]->attributes["arrowtail"] = "normal";
                    nodeEdgeMap[fm][tempIndex]->attributes["arrowhead"] = "normal";
                    nodeEdgeMap[fm][tempIndex]->attributes["color"] = "\"mediumspringgreen"
                    ":coral1\"";
                    removeEdge(to, fm);
                } else {
                    nodeEdgeMap[to][otherIndex]->attributes["dir"] = "both";
                    nodeEdgeMap[to][otherIndex]->attributes["arrowtail"] = "normal";
                    nodeEdgeMap[to][otherIndex]->attributes["arrowhead"] = "normal";
                    nodeEdgeMap[to][otherIndex]->attributes["color"] = "\"mediumspringgreen"
                    ":coral1\"";
                    removeEdge(fm, to);
                }
            }
            
        } else {
            // If no edge is found between either node:
            if (!foundEdge(to, fm)) {
                // Assign a different color based on if the node points forward or backward
                // in id (If 2 points to 1, the color will be deeppink, otherwise it's cyan)
                if (fm > to) {
                    listEdge *e = new listEdge(fm);
                    e->attributes["color"] = "deeppink";
                    e->attributes["dir"] = "back";
                    e->attributes["arrowtail"] = "vee";
                    nodeEdgeMap[to].push_back(e);
                } else {
                    listEdge *e = new listEdge(to);
                    e->attributes["arrowhead"] = "vee";
                    e->attributes["color"] = "cyan";
                    e->attributes["dir"] = "forward";
                    nodeEdgeMap[fm].push_back(e);
                }
            } 
            // If an edge is found one way from the node with id 'to' to the node with id 'fm'
            else {
                int otherIndex = findEdgeIndex(to, fm);
                if (nodeEdgeMap[to][otherIndex]->attributes["dir"] == "both") {
                    cout << "Edge already exists!\n";
                    return;
                }
                // If the found edge between the node with id 'to' is the default edge, it can 
                // be assumed that it is the smaller ID of the two, so the values are set
                // accordingly.
                else if (nodeEdgeMap[to][otherIndex]->attributes["dir"] == "none") {
                    nodeEdgeMap[to][otherIndex]->attributes["dir"] = "back";
                    nodeEdgeMap[to][otherIndex]->attributes["arrowtail"] = "vee";
                    nodeEdgeMap[to][otherIndex]->attributes["arrowhead"] = "vee";
                    nodeEdgeMap[to][otherIndex]->attributes["color"] = "deeppink"; 
                }
                // If the edge to be created doesn't exist, but the other node has an edge
                // to the fm ID
                else {
                    if (fm < to) {
                        listEdge *e = new listEdge(to);
                        e->attributes["dir"] = "both";
                        e->attributes["arrowhead"] = "normal";
                        e->attributes["arrowtail"] = "normal";
                        e->attributes["color"] = "\"mediumspringgreen:coral1\"";
                        removeEdge(to, fm);
                    } else {
                        nodeEdgeMap[to][otherIndex]->attributes["dir"] = "both";
                        nodeEdgeMap[to][otherIndex]->attributes["arrowtail"] = "normal";
                        nodeEdgeMap[to][otherIndex]->attributes["arrowhead"] = "normal";
                        nodeEdgeMap[to][otherIndex]->attributes["color"] = "\"mediumspring"
                        "green:coral1\"";
                    }
                }
            }
        }
    }

    /**
     * Public : findEdgeIndex
     * 
     * Description:
     *      Checks for an edge between two nodes. 
     * 
     * Params:
     *      int     : id of the node to check if the edge from it exists
     *      int     : id of the node to check if the edge to it exists
     * 
     * Returns:
     *      The index of the edge in the map or -1 if the edge doesn't exist.
     */
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

    /**
     * Public : removeEdge
     * 
     * Description:
     *      Removes the edge between two nodes. Used only when an edge is going to be
     *      overwritten. Logs an error message and returns if the edge doesn't exist.
     * 
     * Params:
     *      int     : id of the node that the edge comes from
     *      int     : id of the node that the edge goes to
     * 
     * Returns:
     *      N/A
     */
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
    
    /**
     * Public : foundEdge
     * 
     * Description:
     *      Determines whether or not an edge exists between two nodes.
     * 
     * Params:
     *      int     : id of the node that the edge comes from
     *      int     : id of the node that the edge goes to
     * 
     * Returns:
     *      Bool indicating whether or not there is an edge from the first id's node to the
     *      second id's node
     */
    bool foundEdge(int idFm, int idTo) {
        // Searches for the edge in the nodeEdgeMap
        for (int i = 0; i < nodeEdgeMap[idFm].size(); i++) {
            if (nodeEdgeMap[idFm][i]->idTo == idTo) {
                return true;
            }
        }
        return false;
    }
    
    /**
     * Public : setMinMax
     * 
     * Description:
     *      Sets the minimum data and the maximum data. Used for creating variance in the node
     *      attributes of our DOT syntax.
     * 
     * Params:
     *      int     : data to be compared to current min and max values
     *      int     : id of the node, used for preventing errors from previous class instances
     * 
     * Returns:
     *      N/A
     */
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

    /**
     * Public : printNodeAttributes
     * 
     * Description:
     *      Traverses the linked list and assigns each node their proper attributes based on
     *      the data they contain and appends the DOT notation of a node to the result to be
     *      returned
     * Params:
     *      N/A
     * 
     * Returns:
     *      String containing the entirety of the DOT notation for the node attribute assignment
     *      portion of our final output.
     */
    string printNodeAttributes() {
        int variance = ((max - min)/3);
        string result = "";
        listNode *travel = front;
        // Traverses the linked list and assigns attributes to each node based on its data
        while(travel) {
            // Lower 1/3 gets a shape of record and a color of cornflowerblue:blue4
            if (travel->data >= min && travel->data < min + variance) {
                travel->color = "\"cornflowerblue:blue4\"";
                travel->shape = "record";
            } 
            // Middle 1/3 gets a shape of doublecircle and a color of deeppink3:pink
            else if (travel->data >= min + variance && travel->data < max - variance) {
                travel->color = "\"deeppink3:pink\"";
                travel->shape = "doublecircle";
            } 
            // Upper 1/3 gets a shape of star and a color of darkgoldenrod3:gold
            else {
                travel->color = "\"darkgoldenrod3:gold\"";
                travel->shape = "star";
            }
            // For proper DOT formatting:
            if (travel->id != 1) {
            result.append("\n\t");
            }
            // Will look like: id [label=id->data, shape=id->shape, color=id->color];
            result.append(to_string(travel->id) + " [label=\"");
            result.append(to_string(travel->data) + "\", shape="+travel->shape+", color=");
            result.append(travel->color+"];");
            travel = travel->next;
        }
        return result;
    }

    /**
     * Public : printEdgeAttributes
     * 
     * Description:
     *      Traverses our linked list and appends result with the edges of each node in DOT 
     *      notation. 
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      String containing the entirety of the DOT notation for the edges contained in our
     *      linked list for the edge assignment portion of our final output.
     */
    string printEdgeAttributes() {
        string result = "";
        listNode *travel = front;
        while(travel) {
            if (travel->id == curr_id && nodeEdgeMap[travel->id].empty()) {
                result.append("\n\t" + to_string(travel->id) + " -> " + nullEdgeSettings);
            }
            for (int i = 0; i < nodeEdgeMap[travel->id].size(); i++) {
                // idFrom:e -> idTo:w [edgeSettings]; * DOT Notation
                result.append("\n\t" + to_string(travel->id) + ":e -> ");
                result.append(to_string(nodeEdgeMap[travel->id][i]->idTo) + ":w ");
                result.append(nodeEdgeMap[travel->id][i]->print());
                // If it's the last node, append null edge and settings at the end
                if (travel->id == curr_id) {
                    result.append(("\n\t" + to_string(travel->id) + " -> " + nullEdgeSettings));
                }
            }
            travel = travel->next;
        }
        return result;
    }

    

    /**
     * Public : printDOT
     * 
     * Description:
     *      Logs the DOT notation of the linked list to the console and prints it to an output
     *      file. Can be pasted into a graphviz compiler to visualize the data structure.
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      N/A
     */
    void printDOT() {
        listNode *travel = front;
        // If the list is empty, return the empty list in DOT notation.
        if (!travel) {
            bgSettingsList.pop_back();
            cout << bgSettingsList <<"}" << endl;
            outfile << bgSettingsList << "}" << endl;
            return;
        }
        string result = "";
        // Append the background settings for our linked list to the top of the output.
        result.append(bgSettingsList);
        result.append(printNodeAttributes());
        result.append(printEdgeAttributes());
        // Formatting for the DOT language
        result.append("\n}\n");
        // Print and log DOT notation
        cout << result << endl;
        outfile << result << endl;
    }
        
};
