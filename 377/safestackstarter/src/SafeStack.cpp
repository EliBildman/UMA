#include "SafeStack.h"

SafeStack::SafeStack(){
    numbers = new stack<int>();
}
SafeStack::~SafeStack(){
    delete numbers;
    // free(this);
}
void SafeStack::push(int data){
    pthread_mutex_lock(&stack_lock);
    if(numbers->empty()) {
        pthread_cond_signal(&not_empty);
    }
    numbers->push(data);
    pthread_mutex_unlock(&stack_lock);
}
int SafeStack::pop(){
    int temp;
    // Lock
    pthread_mutex_lock(&stack_lock);
    // Wait for stuff to be in stack
    while((*numbers).size() == 0){
        pthread_cond_wait(&not_empty, &stack_lock);
    }
    // Get top
    temp = (*numbers).top();
    // Get rid of top
    (*numbers).pop();
    // Unlock (because we already have top)
    pthread_mutex_unlock(&stack_lock);
    // Return
    return temp;
}
int SafeStack::size(){
    pthread_mutex_lock(&stack_lock);
    return numbers->size();
    pthread_mutex_unlock(&stack_lock);
}