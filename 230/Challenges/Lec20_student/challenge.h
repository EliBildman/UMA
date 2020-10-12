#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#ifndef CH_HEAD
#define CH_HEAD

// goal: reads in message from read pipe; sends "hello from child." through write pipe
// para read_pipe: file descriptor for pipe to read from
// para write_pipe: file descriptor for pipe to write to
int child_task(int read_pipe, int write_pipe);

// goal: sends "hello from parent." through write pipe; reads in message from read pipe
// para read_pipe: file descriptor for pipe to read from
// para write_pipe: file descriptor for pipe to write to
// return: 0 on success, 1 on error
int parent_task(int read_pipe, int write_pipe);

// goal: forks and runs parent_task and child_task
void family_tasks();

// goal: uses popen to pipe in and print the results of the command "ls -l -A"
void popen_read_example();

// goal: uses popen to pipe input string to the command "wc > output.txt"
//   (the command "wc > output.txt" runs wc an standard in (what you pipe in)
//    and prints output to output.txt)
// param str: string to pipe to "wc > output.txt"
void popen_write_example(char* str);

#endif