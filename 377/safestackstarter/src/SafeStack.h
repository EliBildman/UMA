//// Please don't change this file, thanks. You don't need to, I promise. ////

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <iostream>

using namespace std;

class SafeStack {
  public:
    SafeStack();  // constructor to initialize lock and internal data structure
    ~SafeStack(); // destructor
    void push(int data);
    int pop();
    int size();

  private:
    pthread_mutex_t stack_lock;  // lock
    pthread_cond_t not_empty;  // lock
    stack<int>* numbers;
};