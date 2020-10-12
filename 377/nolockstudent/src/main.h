#include "NoLockStack.h"

// Global variable so it can be used in all threads
NoLockStack my_stack;

int main(int argc, char** argv);
void* producer(void* param);
void* consumer(void* param);