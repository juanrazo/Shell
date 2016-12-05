#include <stdlib.h>
#include <stdio.h>
#include "mytoc.h"
#include "unistd.h"
#include <sys/wait.h>
#include <sys/types.h>

void getLines();
int printDollar();
void changeDelim(char newDlim);
void checkCommand(char **vec);
int checkForPipe(char **vector);
void executeCommand(char **command);
void doPipe(char **pipeVect);

char **pathList;
char **pPathList;
char **vector;
char **pipeVector;
char **userInput;
char delimiter = ' ';
char **enviroment;
char **penvp;
char pipeFlag = 0;
int *pipeFds;


int main(int argc, char **argv, char**envp){
  int i;
  penvp = envp;
  for(i=0; envp[i] != (char *)0; i++){
    enviroment = mytoc(envp[i], '=');
    if(isEqual(enviroment[0], "PATH")){
      pathList = mytoc(enviroment[1], ':');
      pPathList = pathList;
      while(*pPathList != (char *)0){
	concat(*pPathList, "/");
	pPathList++;
      }
    }
  }
  //Read in from the keyboard
  getLines();

  freeVector(enviroment);
  freeVector(pathList);
  return 0;
}

void getLines(){
  int exitLoop = 0;
  char buffer[4096];

  printf("\n\n");
  puts("Sarting Shell:");
  
  
  //Print $ sign, get user input and check if the exit flag is on
  while(exitLoop ==0 /*&& printDollar()*/ && fgets(buffer, 4096 , stdin) != NULL){
    
    vector = mytoc(buffer, delimiter);
    pipeVector = mytoc(buffer, '|');
    //Check for exit
    if(*vector != NULL){
      if(exitLoop= isEqual(*vector, "exit"));
      else{
	//printTokens(vector);
	pipeFlag = checkForPipe(vector);
	// If pipeFlag is set then break the tokens
	if(pipeFlag)
	  printf("Found >\n");
	else{
	  pid_t forkVal = fork();
	  if(!forkVal){
	    doPipe(pipeVector);
	  }
	  else{
	    wait(NULL);
	  }
	}
      }
      freeVector(vector);
    }
  }
}

//Helper methods 
int printDollar(){
  printf("$ ");
  return 1;
}

void checkCommand(char **vec){
  char **pVec;
  pVec = vec;
  if(*pVec != NULL){
    if(isEqual(*pVec, "SET")){
      char del = *(pVec+1)[0];
      printf("%c\n", del);
      delimiter = del;
    }
  }
}

int checkForPipe(char **vector){
  char **pVector;
  int pipeLocation = 0;
  pVector = vector;
  if(pVector != NULL){
    while(*pVector != (char *)0){
      if(isEqual(*pVector, ">")){
	return pipeLocation;
      }
      pipeLocation++;
      pVector++;
    }
  }
  return 0;
}


void doPipe(char **pipeVect){
  char **recursiveToken;
  char **cmd;
  if(pipeVect[1] == (char *)0){
    cmd = mytoc(pipeVect[0], ' ');
    executeCommand(cmd);
  }
  else{
    pipeFds = (int *) calloc(2, sizeof(int));
    pipe(pipeFds);
    pid_t forkVal = fork();
    if(!forkVal){
      close(1);
      dup(pipeFds[1]);
      close(pipeFds[0]);
      close(pipeFds[1]);
      cmd = mytoc(pipeVect[0], ' ');
      executeCommand(cmd);
    }
    else{
      close(0);
      dup(pipeFds[0]);
      close(pipeFds[0]);
      close(pipeFds[1]);
      wait(NULL);
      doPipe(&pipeVect[1]);
    }
  }

}

void executeCommand(char **command){
  char **pList;
  pList = pathList;
  int retVal;
  retVal = execve(*command, &command[0], penvp);
  if(retVal==-1)
    while(*pList != (char *)0){
      char *path;
      path=strcopy(*pList);
      concat(path, *command);
      retVal = execve(path, &command[0], penvp);
      pList++;
    }
}
