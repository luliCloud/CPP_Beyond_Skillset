#include <stdexcept>
#include "CircularLinkedList.h"

// constructor
CircularLinkedList::CircularLinkedList() {
    head = nullptr;
    size = 0;
}

// destructor
CircularLinkedList::~CircularLinkedList() {
    while (size > 0) {
        pop(ClockDirection::ClockWise); // size will auto decrease in pop method
    }
}

// print out the content in CDLL
ostream& operator<<(ostream& os, const CircularLinkedList& other) {
    if (other.head == nullptr) {
        os << "{}" << endl;
        return os;
    }

    Node* curr = other.head;
    os << "{ ";
    while (true) {
        os << curr->val;
        curr = curr->next;
        if (curr != other.head) {
            os << ", ";
        } else {
            os << " }" << endl;
            break;
        }
    }
    return os;
}

// push method
void CircularLinkedList::push(int i, ClockDirection d) {
    Node* curr = new Node(i);

    if (head == nullptr) {
        head = curr;
        head->next = head; // next is clockwise
        head->prev = head; // prev is counterClockwise
        size++;
        return;
    }

    if (d == ClockWise) {
        Node* nextNode = head->next;
        curr->next = nextNode;
        nextNode->prev = curr;
        head->next = curr;
        curr->prev = head;
    } else {  // counter clockwise
        Node* tail = head->prev;
        tail->next = curr;
        curr->prev = tail;
        curr->next = head;
        head->prev = curr;
    }
    size++;
}

// pop method
int CircularLinkedList::pop(ClockDirection d) {
    if (head == nullptr) {
        throw runtime_error("List is empty. Cannot pop any node from the current list.");
    }
    int val = head->val;
    if (head->next == head) {
        delete head;
        head = nullptr;
        size--;
        return val;
    }

    Node* currHead = head;
    Node* tail = head->prev;
    Node* headNext = head->next;
    tail->next = headNext;
    headNext->prev = tail;
    delete currHead; // release the mem head point

    if (d == ClockDirection::ClockWise) {
        head = headNext;
    } else {
        head = tail;
    }
    size--;
    return val;
}

// peek: return integer in the head
int CircularLinkedList::peek() const {
    if (head == nullptr) {
        throw runtime_error("List is empty. Cannot peek in the current list.");
    }

    return head->val;
}

// rotate
void CircularLinkedList::rotate(unsigned int n, ClockDirection d) {
    if (head == nullptr || size == 0) {
        return;
    }

    n %= size; // mode to get the min rotate
    for (unsigned i = 0; i < n; i++) {
        if (d == ClockDirection::ClockWise) {
            head = head->next;
        } else {
            head = head->prev;
        }
    }
}
