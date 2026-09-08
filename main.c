#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  // String to hold input buffer
  char buf[1024];

  // Prompt
  printf("$ ");

  // Get input from keyboard
  fgets(buf, 1024, stdin);

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
    execlp(buf, buf, NULL);

    printf("Child process ID: %d\n", pid);

    // somethins went wrong with exec
    fprintf(stderr, "Could not exec %s\n", buf);
    exit(1);
  }
}
