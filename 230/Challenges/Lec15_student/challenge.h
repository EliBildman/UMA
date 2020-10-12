#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#ifndef CH_HEAD
#define CH_HEAD

// goal: fork the process and have the child execute a process
// param argv: the argument vector for the process to be executed
// assumptions:
//   the first argument of argv is the file name of the executable
//   argv is null terminated
void fork_exec(char** argv);

#endif