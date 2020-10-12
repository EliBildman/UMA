#include "challenge.h"

// goal: reads in message from read pipe; sends "hello from child." through write pipe
// para read_pipe: file descriptor for pipe to read from
// para write_pipe: file descriptor for pipe to write to
//
// TODO: complete the function
//   send the message "hello from child."
int child_task(int read_pipe, int write_pipe)
{
  int nr;
  char to_msg[25];
  
  if ((nr = read(read_pipe, to_msg, 25)) == -1)
  {
    perror("child failed to read from pipe");
    return 1;
  }
  
  printf("child received message from parent.\n");
  printf("message received: \"%s\"\n", to_msg);
  printf("bytes read: %d\n", nr);
  
  const char * msg = "hello from child.";
  if(write(write_pipe, msg, strlen(msg) + 1) == -1) {
    perror("child write failed");
    return 1;
  }
  printf("child write success\n");

  return 0;
}

// goal: sends "hello from parent." through write pipe; reads in message from read pipe
// para read_pipe: file descriptor for pipe to read from
// para write_pipe: file descriptor for pipe to write to
// return: 0 on success, 1 on error
//
// TODO: complete the function
//   read the message
int parent_task(int read_pipe, int write_pipe)
{
  int nw;
  char from_msg[] = "hello from parent.";
  
  if ((nw = write(write_pipe, from_msg, strlen(from_msg) + 1)) == -1)
  {
    perror("parent failed to write to pipe");
    exit(1);
  }
  
  printf("parent sent message to child.\n");
  printf("message sent: \"%s\"\n", from_msg);
  printf("bytes written: %d\n", nw);
  

  char msg[25];
  if(read(read_pipe, msg, 25) == -1) {
    perror("failed parent read");
    return 1;
  }

  printf("parent message recieved: %s\n", msg);


  return 0;
}

// goal: forks and runs parent_task and child_task
//
// TODO: complete to function so the child has a pipe to send a message to the parent with
void family_tasks()
{

  int parent_to_child_pipe[2];
  int child_to_parent_pipe[2];
  
  // Create the pipe
  if (pipe(parent_to_child_pipe) == -1 || pipe(child_to_parent_pipe) == -1)
  {
    perror("could not create pipe");
    exit(1);
  }

  
  
  pid_t pid;
  if ((pid = fork()) == 0)
  {
    // Child process...
    // First we close the write end of the pipe.
    close(parent_to_child_pipe[1]);
    close(child_to_parent_pipe[0]);
    int ret = child_task(parent_to_child_pipe[0], child_to_parent_pipe[1]);
    
    // Close read end in child and exit
    close(parent_to_child_pipe[0]);
    close(child_to_parent_pipe[1]);
    exit(ret);
  }
  else
  {
    // Parent process...
    // First, we close the read end of the pipe.
    close(parent_to_child_pipe[0]);
    close(child_to_parent_pipe[1]);
    parent_task(child_to_parent_pipe[0] ,parent_to_child_pipe[1]);
    
    // Wait on child process to complete
    wait(NULL);
    close(child_to_parent_pipe[0]);
    close(parent_to_child_pipe[1]);
    printf("parent process completing.\n");
  }

}

// goal: uses popen to pipe in and print the results of the command "ls -l -A"
void popen_read_example()
{
  printf("*** popen_read_example() BEGIN ***\n");
  FILE* stream = popen("ls -l -A", "r");
  
  if (stream == NULL)
  {
    perror("popen");
    exit(EXIT_FAILURE);
  }
  
  char c;
  while ((c = fgetc(stream)) != EOF)
  {
    printf("%c", c);
  }
  
  pclose(stream);
}

// goal: uses popen to pipe input string to the command "wc > output.txt"
//   (the command "wc > output.txt" runs wc an standard in (what you pipe in)
//    and prints output to output.txt)
// param str: string to pipe to "wc > output.txt"
//
// TODO: complete the function
//   popen the command (error check)
//   since you are using popen (which returns a FILE*), you can use fprintf to write to the pipe
//   pclose to send EOF through pipe, so wc stops reading and does its job
void popen_write_example(char* str)
{
  // printf("%s\n", str);
  FILE *f;
  if((f = popen("wc > output.txt", "w")) == NULL) {
    perror("Error on popen");
    exit(EXIT_FAILURE);
  }

  fprintf(f, "%s", str);

  if(pclose(f) != 0) {
    perror("Error on pclose");
    exit(EXIT_FAILURE);
  }
  // printf("%i\n", pclose(f));
}
