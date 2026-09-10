#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
  // String to hold input buffer
  char buf[1024];

  // Prompt
  printf("$ ");

  // Get input from keyboard
  fgets(buf, 1024, stdin);

  // Trim newline
  char *nl = strchr(buf, '\n');
  if (nl)
  {
    // replace newline '\n' with symbol for end of string '\0'
    *nl = '\0';
  }

  // Split buf into args
  // example: ls -lah
  char *args[20]; // TODO check args count correctly, remove magic number - 20
  int nargs = 0;
  
  args[nargs] = strtok(buf, " "); // first arg is the command
  while (args[nargs] != NULL)
  {
    args[++nargs] = strtok(NULL, " "); // next args are the arguments
  }

  // Run command
  // system(buf);

  // Fork and exec
  pid_t pid = fork();

  if (pid > 0)
  {
    // we are the parent
    // wait for the child - finished. Thats all.
    wait(NULL);
  }
  else
  {
    // we are the child
    // execlp(buf, buf, NULL);
    execvp(args[0], args);

    printf("Child process ID: %d\n", pid);

    // somethins went wrong with exec
    fprintf(stderr, "Could not exec %s\n", buf);
    exit(1);
  }
}
