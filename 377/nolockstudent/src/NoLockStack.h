//// Please don't change this file, thanks. You don't need to, I promise. ////

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <atomic>

using namespace std;

struct Node{
    Node* next;
    int data;
    Node(int num){
        data = num;
    }
};

class NoLockStack {
    public:
        NoLockStack();  // constructor to initialize lock and internal data structure
        ~NoLockStack(); // destructor
        void push(int data);
        bool pop(int& ret);
        int size();

    private:
        std::atomic<Node*> head;
        std::atomic<int> count;
};