//// Please don't change this file, thanks. You don't need to, I promise. ////

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <iostream>

using namespace std;

struct memNode{
    int addr;
    int len;
    memNode* next;
    /**
     * The constructor for the memNode struct, which is a linked list node.
     * 
     * @param start The address of the start of the free space
     * @param size The length of the free block 
    */
    memNode(int start, int size){
        len = size;
        addr = start;
    }
};

class Sallocator {
    public:
        Sallocator(int size);  // constructor to initialize list
        ~Sallocator(); // destructor
        bool allocate(int size);
        bool bestAllocate(int size);
        bool free(int start, int len);
        void coalesce();
        void print();

    private:
        memNode* head;
        int starting_size;
};