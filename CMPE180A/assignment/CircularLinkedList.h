#ifndef __CIRCULAR_LINKED_LIST_H__
#define __CIRCULAR_LINKED_LIST_H__
#include <iostream>
using namespace std;

enum ClockDirection {ClockWise, CounterClockWise}; // two dir

struct Node {
    int val;
    Node* next;
    Node* prev;

    Node(int v) : val(v), next(nullptr), prev(nullptr) {}      
};

class CircularLinkedList {
public:
    CircularLinkedList();
    ~CircularLinkedList();
    void push(int i, ClockDirection d); // this will insert a new node containing the
    // integer provided in the d direction from the head
    int pop(ClockDirection d); // remove the head node, return its value, and set
    // the head in the direciton specified in d.
    int peek() const; // return the integer in the head of the circular list
    void rotate(unsigned int n, ClockDirection d); // will rotate the head pointer
    // n spaces in the dir specified d.

    // print CLL in clockwise dir: next, nextnext
    friend ostream& operator<<(ostream& os, const CircularLinkedList& other);

    int _get_size() const {
        return size;
    }
private:
    Node* head;
    int size;

};

#endif