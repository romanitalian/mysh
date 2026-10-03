#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int handle_redirect(char *args[]);

int main(int argc, char *argv[])
{

  int interactive = 1;

  // read from file and execute commands from file
  if (argc > 1)
  {
    // First arg is the name of the script file
    if (freopen(argv[1], "r", stdin) == NULL)
    {
      fprintf(stderr, "Can't read from script file %s\n", argv[1]);
      fprintf(stderr, "Exiting...\n");
      exit(1);
    }
    interactive = 0;
  }

  while(1)
  {
    // String to hold input buffer
    char buf[1024];

    // Prompt
    if (interactive)
    {
      printf("$ ");
    }

    // Get input from keyboard
    // fgets(buf, 1024, stdin);
    if (fgets(buf, 1024, stdin) == NULL)
    {
      break;
    }

    // Trim newline
    char *nl = strchr(buf, '\n');
    if (nl)
    {
      // replace newline '\n' with symbol for end of string '\0'
      *nl = '\0';
    }

    // Remove comments
    char *hash = strchr(buf, '#');
    if (hash)
    {
      *hash = '\0';
    }

    // Split buf into args
    // example: ls -lah
    char *args[20]; // TODO check args count correctly, remove magic number: 20!
    int nargs = 0;

    args[nargs] = strtok(buf, " "); // first arg is the command
    while (args[nargs] != NULL)
    {
      args[++nargs] = strtok(NULL, " "); // next args are the arguments
    }

    if (args[0] == NULL)
    {
        continue;
    }
    if (strcmp(args[0], "exit") == 0) {
      exit(0);
    }

    // Run command
    // system(buf);

    // Fork and exec
    pid_t pid = fork();

    if (pid > 0)
    {
      // we are the parent!
      // wait for the child - finished. Thats all.
      wait(NULL);
    }
    else
    {
      handle_redirect(args);
      // we are the child!
      // execlp(buf, buf, NULL);
      execvp(args[0], args);

      printf("Child process ID: %d\n", pid);

      // somethins went wrong with exec
      fprintf(stderr, "Could not exec %s\n", buf);
      exit(1);
    }
  }
}

// Handle redirect stdout
// Return 1 if successful
// Return 0 is no redirect was needed
// Return -1 if something broke
int handle_redirect(char *args[])
{
  for (int i = 0; args[i] != NULL; i++)
  {
    if (strcmp(args[i], ">") == 0)
    {
      // Assume next args is the file to write to
      // stdout = fopen(args[i + 1], "w");
      if (freopen(args[i + 1], "w", stdout) == NULL)
      {
        return -1;
      }

      // Terminate args at the ">" symbol
      args[i] = NULL;
      args[i + 1] = NULL;

      return 1;
    }
  }

  return 0;
}
