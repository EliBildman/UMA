#include "tsh.h"

using namespace std;

void simple_shell::parse_command(char* cmd, char** cmdTokens) {
  // TODO: tokenize the command string into arguments
  int i = 0;
  int token = 0;
  int tokenitt = 0;

  cmdTokens[token] = new char[50];

  while(cmd[i] != '\0') {

    if(cmd[i] != ' ' && cmd[i] != '\n') {
      cmdTokens[token][tokenitt] = cmd[i];
      tokenitt++;
    } else {
      cmdTokens[token][tokenitt] = '\0';
      token++;
      cmdTokens[token] = new char[50];
      tokenitt = 0;
    }
    i++;
  }

  cmdTokens[token] = nullptr;

}

void simple_shell::exec_command(char **argv)
{
  // TODO: fork a child process to execute the command.
  // parent process should wait for the child process to complete and reap it

  // int i = 0;
  // while(argv[i] != nullptr) {
  //   printf("%s\n", argv[i++]);
  // }

  int pid;
  if((pid = fork()) == 0) {
    execvp(argv[0], argv);
    exit(0);
  } else {
    waitpid(pid, NULL, 0);
  }

}

bool simple_shell::isQuit(char *cmd){
  // TODO: check for the command "quit" that terminates the shell
  return strcmp(cmd, "quit") == 0;
}
