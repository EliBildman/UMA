// PRIVATE BEGIN
#include <stdio.h>
#include <unistd.h>

extern char** environ;
// PRIVATE END

// goal: print the environment variables to the file "env.txt", one per line
// (If envp is NULL, the file should be empty, opening in write mode will do that.)
// example:
//   inputs:
//     envp/environ = {"E1=2","E2=7",NULL}
//   outputs:
//     env.txt as a string would be "E1=2\nE2=7\n"
// example:
//   inputs:
//     envp/environ = {NULL} or NULL
//   outputs:
//     env.txt as a string would be ""
//
// TODO: write and complete the main function

int strLen(char *str) {
  int i = 0;
  while(str[i++] != '\0');
  return i;
}

int main(int argc, char *argv[], char *envp[])
{
  int i = 0;
  FILE *f = fopen("env.txt", "w");
  while(envp[i] != NULL) {
    fwrite(envp[i], sizeof(char) * strLen(envp[i]) - 1, 1, f);
    fputs("\n", f);
    i++;
  }
  fclose(f);
  return 0;
}

