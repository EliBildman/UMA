#include "sallocator.h"

Sallocator::Sallocator(int size){
    //TODO
    starting_size = size;
    head = new memNode(0, size);
}

Sallocator::~Sallocator(){

    if(head != NULL) {

        memNode *front = head->next;
        memNode *behind = head;

        while(front != NULL) {
            delete behind;
            behind = front;
            front = front->next;
        }

        delete behind;

    }

}

bool Sallocator::allocate(int size) {
    bestAllocate(size);
}

bool Sallocator::bestAllocate(int size){
    //TODO
    coalesce();

    memNode* best = NULL;
    memNode* temp = head;

    while(temp != NULL){
        if(temp->len >= size){
            if(best == NULL || temp->len - size < best->len - size) {
                best = temp;
            }
        }
        temp = temp->next;
    }

    if(best != NULL) {
        best->len -= size;
        best->addr += size;
        return true;
    } else {
        return false;
    }
}

bool Sallocator::free(int start, int len){
    
    // If there is no memory to free, we're done.
    if(len == 0){
        return true;
    }

    memNode* temp = head;
    while(temp != NULL){

        // Adding a new free node to the beginning of the list.
        if(temp->addr > start){
            // Ensure there's enough room
            if(temp->addr < start + len){
                // Doubly-freeing memory
                cout << "Attempting to free memory which is at least partially already free. Aborted." << endl;
                return false;
            }
            // Important change here: we're adding this to the head.
            head = new memNode(start, len);
            head->next = temp;
            return true;
        }

        // Adding a new free node to the end of the list.
        if(temp->addr < start && temp->next == NULL){
            // Check if room is availible on the end.
            if(start+len > starting_size){
                // "segfault", but doesn't crash the program.
                cout << "Cannot free memory outside of memory bounds" << endl;
                return false;
            }
            temp->next = new memNode(start, len);
            return true;
        }

        // Adding a new free node between two nodes. Keep free nodes in order.
        if(temp->addr+temp->len <= start && temp->next->addr >= start){
            // Make sure all memory being freed is actually allocated.
            if(temp->next->addr < start + len){
                // Doubly-freeing memory.
                cout << "Attempting to free memory which is at least partially already free. Aborted." << endl;
                return false;
            }
            temp->next = new memNode(start, len);
            return true;
        }

        // Advance
        temp = temp->next;
    }

    // This line realistically never runs, but g++ doesn't know that and gives a warning without it.
    cout << "Address to free not in range: " << to_string(start) << endl;
    return false;
}

void Sallocator::coalesce(){
    memNode* temp = head;
    // While we're neither done nor at the final node
    while(temp != NULL && temp->next != NULL){
        // If there are two adjacent elements
        if(temp->addr + temp->len == temp->next->addr){
            // Combine free blocks
            temp->len += temp->next->len;
            temp->next = temp->next->next;
        }

        // Advance
        else{
            temp = temp->next;
        }
    }
}

void Sallocator::print(){
    memNode* temp = head;
    while(temp != NULL){
        cout << "Start: " << to_string(temp->addr) << ", len: " << to_string(temp->len) << endl;
        temp = temp->next;
    }
}