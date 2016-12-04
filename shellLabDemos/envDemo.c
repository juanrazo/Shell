#include "mytoc.h"
#include "stdio.h"
#include "unistd.h"
int main(int argc, char **argv, char**envp) 
{
  char **tokens;
  char *path;
  char **listofPaths;
  int i;
 
  for (i=0; envp[i] != (char*)0; i++) {
    //printf("envp[%d] = \"%s\"\n", i, envp[i]);
    tokens = mytoc(envp[i], '=');
    if(isEqual(tokens[0],"PATH")){
      printf("Path found\n");
      listofPaths = mytoc(tokens[1], ':');
      while(*listofPaths != (char *)0){
	char *prog = "/ls";
	concat(*listofPaths, prog);
	printf("Trying path: %s\n", *listofPaths);
	char *param = "-l";
	char *arg[] = {*listofPaths, "-a", 0};
	int retVal = execve(arg[0], &arg[0], envp);
	listofPaths++;
	fprintf(stderr, "%s: exec returned %d\n", prog, retVal);
      }
    }
    freeVector(tokens);
  }
  return 0;
}
