/*****************************************************************************
*                    
*  Author:           Stephanie Nagel
*  Email:            aeliousx@gmail.com
*  Label:            P01
*  Title:            Vector Class
*  Course:           CMPS 2143
*  Semester:         Spring 2023
* 
*  Description:
*       This program implements a class that allows a singly-linked list to be used similarly
*       to a vector. The linked list can add and remove nodes with data values, search
*       existing nodes' values for a specific value, and it can be sorted in ascending
*       numerical order.  It also has print functionality to display the linked list similarly
*       to an array.
*
*  Usage:
*       N/A
* 
*  Files:            
*       main.cpp    : driver program
*       vector.hpp  : header file with vector and node definitions
*       input.dat   : input file with values to test output
*****************************************************************************/
// vector.hpp

#include <iostream>
#include <fstream>
using namespace std;

/**
 * Node
 * 
 * Description:
 *      This struct provides the structure for a node in our linked list.
 * 
 * Public Methods:
 *                          Node(int x)             // Constructor
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
  int data;
  Node *next;
  Node(int x) {
    data = x;
    next = nullptr;
  }
};

/**
 * Vector
 * 
 * Description:
 *      This class provides the tools to link together Node objects and create structured
 *      linked lists. The data contained in each Node will always be a single int. The data
 *      set may be read in via file name, direct placement, or as a deep copy of a preexisting
 *      linked list. The class provides functionality to print, modify (add or remove nodes),
 *      search, and sort the linked list. 
 * 
 * Public Methods:
 *                          Vector()
 *                          Vector(int *A, int size)
 *                          Vector(string file)
 *                          Vector(&V2)
 *      void                inOrderPush(int x)
 *      void                pushFront(int x)
 *      void                pushFront(Vector V2)
 *      void                pushRear(int x)
 *      void                pushRear(Vector V2)
 *      int                 popFront()
 *      int                 popRear()
 *      int                 popAt(int loc)
 *      int                 find(int valToFind)
 *      void                print()
 *      void                sortList()
 *      void                deleteList()
 * 
 * Private Methods:
 *                          N/A
 * 
 * Usage: 
 *      int someArray[] = {3, 2, 1}; 
 *      Vector myVector(someArray, 3);              // Creates a new linked list using the
 *                                                  // data in someArray and its size, 3
 *      
 *      Vector myCopiedVector(myVector);            // Creates a new linked list using the
 *                                                  // data in myVector. It's a deep copy.
 * 
 *      myVector.pushRear(myCopiedVector);          // Appends the values in myCopiedVector
 *                                                  // to the end of myVector, these are
 *                                                  // deep copies of the nodes.
 * 
 *      myVector.pushFront(4);                      // Pushes a node with data 4 to the
 *                                                  // front of the linked list. Does NOT
 *                                                  // change myCopiedVector due to it
 *                                                  // being a deep copy.
 *      
 *      myVector.sortList();                        // Sorts the nodes in the linked list.
 *      myVector.print();                           // Logs & outfiles[1, 1, 2, 2, 3, 3, 4]
 *      myCopiedVector.print();                     // Logs & outfiles [1, 2, 3]
 */

class Vector {
    Node *front;            // Holds the address of the start of our linked list.
    Node *tail;             // Holds the address of the end of our linked list.
    ifstream infile;        
    ofstream outfile;
    bool sorted = false;    // Whether or not the linked list is sorted.

public:

     /**
     * Public : Vector
     * 
     * Description:
     *      Default constructor, creates a linked list with nothing in it. Also opens output 
     *      file and sets it to append mode.
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      N/A
     */

    Vector() {
        outfile.open("test.out", fstream::app);
        front = tail = nullptr;
    }

     /**
     * Public : Vector
     * 
     * Description:
     *      Overloaded constructor used for creating nodes in the linked list from array data.
     *      Also opens output file and sets it to append mode.
     * 
     * Params:
     *      int*    : array of integers
     *      int     : array size
     * 
     * Returns:
     *      N/A
     */

    Vector(int *A, int size){
        outfile.open("test.out", fstream::app);   
        front = tail = nullptr;
        for (int i = 0; i < size; i++) {
            pushRear(A[i]);
        }
    }

     /**
     * Public : Vector
     * 
     * Description:
     *      Overloaded constructor used for creating a linked list with nodes using data in an
     *      external input file. Opens the input file and reads in the node data. closes the 
     *      input file when it is done reading in the data from it. Also opens output file and 
     *      sets it to append mode.
     * 
     * Params:
     *      string    : name of input file
     * 
     * Returns:
     *      N/A
     */

    Vector(string file){
        outfile.open("test.out", fstream::app);   
        front = tail = nullptr;
        infile.open(file);
        while (!infile.eof()) {
            int tempVal;
            infile >> tempVal;
            pushRear(tempVal);
        }
        infile.close();
    }

    /**
     * Public : Vector
     * 
     * Description:
     *      Overloaded constructor used for creating nodes in the linked list from data in an
     *      already existing linked list. Creates a deep copy of the nodes. Also opens the
     *      output file and sets it to append mode.
     * 
     * Params:
     *      Vector    : address of the object to be copied.
     * 
     * Returns:
     *      N/A
     */

    Vector(Vector &V2){
        outfile.open("test.out", fstream::app);   
        front = tail = nullptr;
        // Does nothing if V2 is empty
        if (V2.front != nullptr) {
            Node *travel = V2.front;
            while (travel) {
                pushRear(travel->data);
                travel = travel->next;
            }
            if (V2.sorted == true) {
                sorted = true;
            }
        }
        
    }

    /**
     * Public : inOrderPush
     * 
     * Description:
     *      This method inserts a new node with data x into the linked list. If the list is
     *      already sorted, it traverses the list until it finds the appropriate placement,
     *      otherwise it inserts the node at the front of the list and then sorts it, which
     *      provides equivalent functionality.
     * 
     * Params:
     *      int    : data to be appended to the list via a node
     * 
     * Returns:
     *      N/A
     */

    void inOrderPush(int x) {
        if (!sorted) { 
            pushFront(x);
            sortList();
        } else {
            if (x <= front->data) {
                pushFront(x);
            } else if (x >= tail->data) {
                pushRear(x);
            } else {
                bool foundSpot = false;
                Node *travel = front->next;
                Node *temp;
                // Traverse sorted linked list to find appropriate spot for a node with data x
                while (travel && !foundSpot) {
                    // if new data > current data and less than or equal to next data, push
                    // after current data
                    if (x > travel->data && x <= travel->next->data) {
                        temp = travel->next;
                        travel->next = new Node(x);
                        travel->next->next = temp;
                        foundSpot = true;
                    }
                    travel = travel->next;
                }
            }
        }
    }

    /**
     * Public : pushFront
     * 
     * Description:
     *      Pushes a new node with data x onto the front of a linked list. Sets sorted to
     *      false, changing any potential true flags as we cannot guarantee that a previously
     *      sorted list is still in proper order.
     * 
     * Params:
     *      int    : data to be appended to the list via a node
     * 
     * Returns:
     *      N/A
     */

    void pushFront(int x){
        Node *temp = new Node(x);
        if (tail == nullptr) {
            front = tail = temp;
        } else {
            temp->next = front;
            front = temp;
        }
        sorted = false;
    }

    /**
     * Public : pushFront
     * 
     * Description:
     *      Overloaded function, pushes an entire preexisting linked list to the front of the
     *      list via a deep copy. Sets sorted to false,changing any potential true flags as we 
     *      cannot guarantee that a previously sorted list is still in proper order.
     * 
     * Params:
     *      Vector    : linked list to be appended to the front of the list
     * 
     * Returns:
     *      N/A
     */

    void pushFront(Vector V2) {
        // Does nothing if V2 is an empty linked list
        if (V2.front != nullptr) {
            Node *travel = V2.front->next;
            Node *newFront = new Node(V2.front->data);
            Node *addToNewList = newFront;
            // Traverses the passed in list to be pushed to the front and pushes each node  
            // onto a new list
            while(travel) {
                Node *temp = new Node(travel->data);
                addToNewList->next = temp;
                addToNewList = addToNewList->next;
                travel = travel->next;
            }
            travel = front;
            // Traverses the current list to push each node to the new list after the 
            // parameter nodes
            while(travel) {
                Node *temp = new Node(travel->data);
                addToNewList->next = temp;
                addToNewList = addToNewList->next;
                tail = travel;
                travel = travel->next;
                
            }
            deleteList(front);
            // Set the linked list head to the head of the new linked list, replacing the
            // current list with the new list
            front = newFront;
            sorted = false;
        }
        
    }

    /**
     * Public : pushRear
     * 
     * Description:
     *      Pushes a new node with data x onto the end of a linked list. Sets sorted to false,
     *      changing any potential true flags as we cannot guarantee that a previously sorted
     *      list is still in proper order.
     * 
     * Params:
     *      int    : data to be appended to the list via a node
     * 
     * Returns:
     *      N/A
     */

    void pushRear(int x) {
        Node *temp = new Node(x);
        if (tail == nullptr) {
            front = tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
        sorted = false;
    }

    /**
     * Public : pushRear
     * 
     * Description:
     *      Overloaded function, pushes an entire preexisting linked list to the end of the
     *      list via a deep copy. Sets sorted to false,changing any potential true flags as we
     *      cannot guarantee that a previously sorted list is still in proper order.
     * 
     * Params:
     *      Vector  : linked list to be appended to the end of the list
     * 
     * Returns:
     *      N/A
     */

    void pushRear(Vector V2) {
        // Does nothing if V2 is an empty linked list
        if (V2.front != nullptr) {
            Node *travel = front->next;
            Node *newFront = new Node(front->data);
            Node *addToNewList = newFront;
            // Traverses the current list to push the current nodes to the new list
            while(travel) {
                Node *temp = new Node(travel->data);
                addToNewList->next = temp;
                addToNewList = addToNewList->next;
                travel = travel->next;
            }
            travel = V2.front;
            // Traverses the param list to push the nodes to the new list after the current
            // nodes
            while(travel) {
                Node *temp = new Node(travel->data);
                addToNewList->next = temp;
                addToNewList = addToNewList->next;
                tail = travel;
                travel = travel->next;
            }
            deleteList(front);
            // Set the linked list head to the head of the new linked list, replacing the
            // current list with the new list
            front = newFront;
            sorted = false;
        }
        
    }

    /**
     * Public : popFront
     * 
     * Description:
     *      Removes the first node in a linked list and returns the value of data in the node.
     *      Returns -1 if the list is empty.
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      int     : data value of the removed node or -1 if the list is empty.
     */

    int popFront() {
        if (front == nullptr) {     // If the list is empty, return -1
            return -1;
        }
        int removedData = front->data;
        front = front->next;
        return removedData;         // Otherwise return the popped node's data.
    }

    /**
     * Public : popRear
     * 
     * Description:
     *      Removes and returns the last node in a linked list. Returns -1 if the list is
     *      empty.
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      int     : data value of the removed node or -1 if the list is empty
     */

    int popRear() {
        int removedData = -1;
        // Skips this if the list is empty
        if (tail != nullptr) {
            removedData = tail->data;
            Node *travel = front;
            Node *checkNext = travel->next;
            int removedData;
            while (checkNext->next != nullptr) {
                travel = travel->next;
                checkNext = checkNext->next;
                if (checkNext->next == nullptr) {
                    tail = travel;
                    delete checkNext;
                    tail->next = nullptr;
                }
            }
        }
        return removedData;
    }

    /**
     * Public : popAt
     * 
     * Description:
     *      Removes a node at the specified location in a linked list. Returns -1 if there 
     *      is not a node at the specified location. 
     * 
     * Params:
     *      int     : location of the node to remove
     * 
     * Returns:
     *      int     : data value of the removed node or -1 if there is either no node at that
     *                location or if the list is empty.
     */

    int popAt(int loc) {
        int removedData;
        int count = 0;
        Node *travel = front;
        Node *temp;
        // If the location is the first node and it's not empty, pop the first node
        if (loc == 0 && front != nullptr) {
            return popFront();
        }
        // If the list is empty return -1
        if (loc == 0 && front == nullptr) {
            return -1;
        }
        // Loop through nodes until you reach the location
        for (int i = 0; i < loc-1; i++) {
            if(travel) {
                count++;
                travel = travel->next;
            }
        }
        // If the location doesn't match the count (the list isn't that big), return -1
        if (count != loc-1) {
            return -1;
        } else if (count == loc-1 && travel == tail) { // if the location is the last node,
            return popRear();                          // pop the tail
        } else {    // Pop the node at the passed in location and return the value of data
            temp = travel->next;
            removedData = temp->data;
            travel->next = temp->next;
            delete temp;
            return removedData;
        }
    }

    /**
     * Public : find
     * 
     * Description:
     *      Attempts to retrieve the location of a node that has the specified data value
     *      passed in by the parameter.
     * 
     * Params:
     *      int     : value to search for
     * 
     * Returns:
     *      int     : location of the node where data is the value being searched for, or
     *                -1 if there is no node where the value is equal to the node data
     */

    int find(int valToFind){
        // If list is empty, return -1
        if (front == nullptr) {
            return -1;
        }
        Node *travel = front;
        int index = 0;
        while(travel) {
            if(travel->data == valToFind) {
                // If the value matches the current node's data, return the node index
                return index;
            } else {
                travel = travel->next;
                index++;
            }
        }
        // If value was not found in the linked list, return -1
        return -1;
    }

    /**
     * Public : print
     * 
     * Description:
     *      Traverses the linked list and logs the data of each node to the console and the
     *      specified output file. Presents as an array with square brackets around the linked
     *      list's node data with commas separating the data. An empty linked list will print
     *      as [].
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      N/A
     * 
     */

    void print() {
        Node *travel = front;
        outfile << "[";
        cout << "[";
        while(travel) {
            if(travel->next){
                cout << travel->data << ", ";
                outfile << travel->data << ", ";
            } else {
                cout << travel->data;
                outfile << travel->data;
            }
            travel = travel->next;
        }
        cout << "]" << endl;
        outfile << "]" << endl;
    }

    /**
     * Public : sortList
     * 
     * Description:
     *      I am so unbelievably ashamed of this monster... But it does work. And merge sorts
     *      hurt my brain. This function sorts the linked list in order of ascending node 
     *      data. It creates a new list and places each node in its correct position before
     *      changing the head to the head of the sorted list. It then changes sorted to true,
     *      as the list is now sorted.
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      N/A
     * 
     */
    
    void sortList() {
        // Set the first value of the new list
        Node *newFront = new Node(front->data);    
        // Travel starts at the node after front since newFront has front's data
        Node *travel = front->next;                 
        Node *temp;
        // Set the second value of the new list
        if (travel->data > newFront->data) {
            newFront->next = new Node(travel->data);
        } else {
            temp = newFront;
            newFront = new Node(travel->data);
            newFront->next = temp;
        }
        travel = travel->next;
        // Nested while loops loop through current list's nodes 1 at a time, and steps through
        // the new list to find the appropriate spot for each node. It's disgusting. I know.
        while (travel) {
            Node *innerTravel = newFront;
            Node *checkNext = innerTravel->next;
            int current = travel->data; // Current is the current data int of the travel node
            Node *newNode = new Node(current);
            bool foundSpot = false;     // Allows us to break out of the while loop when we 
                                        // have found the location where the node goes.
            while(innerTravel && !foundSpot) {
                if (innerTravel == newFront && innerTravel->data > current) {
                    newNode->next = newFront;
                    newFront = newNode;
                    foundSpot = true;
                } else if (current > innerTravel->data && !checkNext) {
                    innerTravel->next = newNode;
                    innerTravel = innerTravel->next;
                    foundSpot = true;
                } else if (current > innerTravel->data && current <= innerTravel->next->data){
                    temp = innerTravel->next;
                    innerTravel->next = newNode;
                    innerTravel=innerTravel->next;
                    innerTravel->next = temp;
                    foundSpot = true;
                } else {
                    checkNext = checkNext->next;
                    innerTravel = innerTravel->next;
                }
            }
            travel = travel->next;
        }
        travel = newFront;
        // Set new tail value
        while(travel) {
            tail = travel;
            travel = travel->next;
        }
        deleteList(front);
        sorted = true;
        // Switch the head of our linked list to our new sorted linked list
        front = newFront;
    }

    /**
     * Public : deleteList
     * 
     * Description:
     *      Deletes a list and deallocates memory. Padding to the spaghetti code. Utilized
     *      only when a new list is set to overwrite the current list.
     * 
     * Params:
     *      Node    : The head of the linked list to be deleted
     * 
     * Returns:
     *      N/A
     * 
     */

    void deleteList(Node *start) {
        Node *travel = start;
        Node *temp;
        while(travel != nullptr) {
            temp = travel;
            travel = travel->next;
            delete temp;
        }
    }

};
