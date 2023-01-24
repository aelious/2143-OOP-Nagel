/*****************************************************************************
*                    
*  Author:           Stephanie Nagel
*  Email:            aeliousx@gmail.com
*  Label:            A03
*  Title:            Commenting Code
*  Course:           CMPS 2143
*  Semester:         Spring 2023
* 
*  Description:
*       Assignment to ensure proper commenting and README creation. :-) This program
*       creates and manipulates a queue.
* 
*  Usage:
*       CircularArrayQue C(15);                // Create Instance of CircularArrayQue
*                                              // with size of 15.
*
*       C.Pop();                               // Removes the first index in C
*
*       C.Push(11);                            // Appends 11 to the end of the queue.
*
*       C.Push(12);                            // Attempts to append 12 after the rear,
*                                              // but is unable to as the queue is full.
*                                              // Prints "FULL!!!!" to the console.
*
*       cout << C << endl;                     // Prints the entire queue C out, separated
*                                              // by a space.
* 
*  Files:            
*       main.cpp    : driver program
*****************************************************************************/


#include <iostream>

using namespace std;

/**
 * CircularArrayQue
 * 
 * Description:
 *      This class can create and manipulate a queue.
 * 
 * Public Methods:
 *                  CircularArrayQue()
 *                  CircularArrayQue(int size)
 *      void        Push(int item)
 *      int         Pop()
 *      QUESTION(Are we supposed to include ostream and if so, how would we write that here?)
 * 
 * Private Methods:
 *      void        init(int size = 0)
 *      bool        Full()
 * 
 * Usage: 
 * 
 *      - examples of how
 *      - to use your class 
 *      
 */

class CircularArrayQue {

private:
    int *Container;     // Pointer variable where queue will be stored
    int Front;          // Front of the queue
    int Rear;           // Rear of the queue
    int QueSize;        // Items in the queue
    int CurrentSize;    // Keeps track of the dynamic size of the queue post creation

    /**
     * Private : init
     * 
     * Description:
     *      Initializes the front, rear, and size of the queue with the
     *      default size being 0.
     * 
     * Params:
     *      int    :  size of the queue, default 0
     * 
     * Returns:
     *      None
     */
    void init(int size = 0) {
        Front = Rear = CurrentSize = 0;
        QueSize = size;
    }

    /**
     * Private : Full
     * 
     * Description:
     *      Tests whether or not a queue is at max capacity.
     * 
     * Params:
     *      None
     * 
     * Returns:
     *      bool:   truth value for whether or not the queue is full.
     */
    bool Full() {
        return CurrentSize == QueSize;
    }

public:
    /**
     * Public : CircularArrayQue
     * 
     * Description:
     *      Default constructor for our class
     *      Creates a queue of size 10
     * 
     * Params:
     *      None
     * Returns
     *      N/A
     */
    CircularArrayQue() {
        Container = new int[10];
        init(10);
    }

    /**
     * Public : CircularArrayQue
     * 
     * Description:
     *      Overloaded constructor for our class.
     *      Creates a queue of a specified size.
     * 
     * Params:
     *      int:    queue size 
     * Returns
     *      N/A
     */
    CircularArrayQue(int size) {
        Container = new int[size];
        init(size);
    }

    /**
     * Public : Push
     * 
     * Description:
     *      Tests if a queue is full and appends an integer to the end if not.
     * 
     * Params:
     *      int:    item to be appended to the end of the queue.
     * 
     * Returns:
     *      None
     */
    void Push(int item) {
        if (!Full()) {
            Container[Rear] = item;
            Rear = (Rear + 1) % QueSize;
            CurrentSize++;
        } else {
            cout << "FULL!!!!" << endl;
        }
    }

    /**
    * Public : Pop
    * 
    * Description:
    *      Removes and returns the first integer in the queue.
    * 
    * Params:
    *      None
    * 
    * Returns:
    *      int:    first integer in the queue
    */
    int Pop() {
        int temp = Container[Front];
        Front = (Front + 1) % QueSize;
        CurrentSize--;
        return temp;
    }

    // Includes the overloaded insertion operator defined outside the class so it can 
    // access private variables.
    friend ostream &operator<<(ostream &os, const CircularArrayQue &other);
};

// Overloads the insertion operator allowing for easy printing to the console.
ostream &operator<<(ostream &os, const CircularArrayQue &other) {

    for (int i = other.Front; i < other.CurrentSize; i = (i + 1) % other.QueSize) {
        os << other.Container[i] << " ";
    }
    os << endl;
    return os;
}

/**
 * Main Driver
 * 
 * For this program, the main driver was used to test the CircularArrayQue class
 * 
 */
int main() {
    CircularArrayQue C1(5);

    // C1.Push(34);
    // C1.Push(38);
    // C1.Push(44);
    // C1.Push(22);
    // C1.Push(99);
    // C1.Push(100);

    C1.Push(1);
    C1.Push(2);
    C1.Push(3);
    // C1.Push(6);
    // C1.Push(7);
    cout << C1 << endl;

    // C1.Push(1);
    // C1.Push(2);
    // C1.Push(3);

    cout << C1 << endl;
}
