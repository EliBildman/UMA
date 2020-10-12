#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int run(int argc, char* argv[]);

void split_and_merge(int argc, char* argv[], char* name);

void fork_and_wait(char** argv1, char** argv2, char* name, int* pid1, int* pid2);

void sort(int count, char* argv[]);

vector<int> read_vector_from_file(int pid);

vector<int> combine_sorted(vector<int>& one, vector<int>& two);
