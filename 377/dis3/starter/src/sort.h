#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int run(int argc, char* argv[]);

vector<int> load(int count, char* argv[]);

void* sort(void* nums);
