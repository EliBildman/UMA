#include "sallocator.h"

// Global variable so it can be used in all threads
Sallocator my_alloc(100);

int main(int argc, char** argv);
void* producer(void* param);
void* consumer(void* param);