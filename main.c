#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  char buf[1024];

  printf("$ ");
  fgets(buf, 1024, stdin);
  system(buf);
}

