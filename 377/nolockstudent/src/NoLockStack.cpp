#include "NoLockStack.h"

NoLockStack::NoLockStack(){
    head = NULL;
    count = 0;
}

NoLockStack::~NoLockStack(){
    // Iterate through all elements and free them.
    while(head != NULL){
        Node* temp = head;
        head = (*head).next; // std::atomic doesn't like -> opperators
        delete temp;
    }
}

/** Creates a new node from the value passed in and makes that new node the head
 *  of the stack. Also incrememnts count.
 * 
 *  @param data The int to be stored in the stack.
 */
void NoLockStack::push(int data){
    Node * add = new Node(data);

    (*add).next = head;
    while(!head.compare_exchange_weak((*add).next, add)) {
        (*add).next = head;
    }
}

/** Gets the head node, remove it, and return it's value. Also decrements count.
 * 
 *  @param t An int passed by reference, such that you can set it equal to the value 
 *           removed and it will update the variable passed in when calling.
 *  @returns true if there was an item to pop and it popped, false otherwise.
 */
bool NoLockStack::pop(int& t){

    // if(size() == 0) {
    //     return false;
    // }

    Node * to_re = head;

    while(!head.compare_exchange_weak(to_re, (*head).next)) {
        to_re = head;
        if(to_re == NULL) return false;
    }

    // if(to_re == NULL) return false;

    count--;
    t = to_re->data;

    delete to_re;

    return true;
}

/** Gets the number of elements in the stack.
 * 
 *  @returns An int representing the number of elements in the stack.
 */
int NoLockStack::size(){
    return count;
}