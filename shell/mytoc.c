#include "mytoc.h"
#include "stdlib.h"
#include "stdio.h"

char ** mytoc(char *str, char delim){
  //Two pointers to scan the sting twice
  char *pStr, *tokStr;

  //Keep count of size and current token or character location
  int vectorSize = 0, charLocation = 0;
  int tokenSize = 0, token = 0;

  pStr = str;
  tokStr = str;
  //Check what the end of a file is because fgets adds the return key
  char endOfFile = '\0';
  int length = strlength(str);
  if(*(str + (length-1)) == '\n')
    endOfFile = '\n';

  //Scan the string to get the vector size
  while(*pStr != endOfFile){
    if( *pStr != delim && (*(pStr+1) == delim || *(pStr+1) == endOfFile ) )
      vectorSize++;
    pStr++;
  }
 
  char **vector= (char **)calloc(vectorSize+1, sizeof(char *));

  //printf("%d tokens found \n", vectorSize);

  //These variables are used to get the first character of a token
  // and a flag for when the first character is found.
  int firstChar = 0, beginingChar = 0;
  
  while(*tokStr != endOfFile){
    //look for the first character of a token. This is done as long as
    //the current char is not a delim and the firstChar flag is not set
    if(!firstChar && *tokStr != delim){
      firstChar =1;
      beginingChar = charLocation;
    }
    //look to see if the current char is not a delimiter and check the
    //next char to see if its a delimiter or end of file to copy the token
    if((firstChar && *tokStr != delim) && ( *(tokStr+1) == delim || *(tokStr+1) == endOfFile)){
      tokenSize = charLocation - beginingChar + 1;
      //printf("------------Token SIZE %d\n", tokenSize);
      *(vector + token) = (char *)malloc(tokenSize+1);
      *(vector + token) = copyToken(beginingChar, tokenSize+1, str);
      firstChar = 0;
      token++;
    }
    charLocation++;
    tokStr++;
  }
  //Add Null to last vector
  *(vector + vectorSize) = (char *)0;
  return vector;
}

//Helper functions

//Code provided by Dr. Freudenthal
char *strcopy(char *inStr){ /* like strdup */
  char *pStr, *copy, *pCopy;
  size_t len;
  for (pStr = inStr; *pStr; pStr++) // count # chars in str
    ;
  len = pStr - inStr + 1;
  copy = pCopy = (char *)malloc(len); //allocate memory to hold copy
  for(pStr = inStr; *pStr; pStr++) // duplicate
    *(pCopy++) = *pStr;
  *pCopy = 0;
  return copy;
}

//Function to copy the token based on starting point and size
char *copyToken(int start, int size, char *str){
  char *pStr, *copy, *pCopy;
  copy = pCopy = (char *)malloc(size * sizeof(char));
  pStr = str;
  int end = size+start-1;
  while(start < end){
    *pCopy = *(pStr+start);
    pCopy++;
    start++;
  }
  *pCopy = '\0';
  return copy;
}

//Find the size of a string
int strlength(char *str){
  int size = 0;
  char *pStr;
  pStr = str;
  while(*pStr != '\0'){
    size++;
    pStr++;
  }
  return size;
}

//Compare two strings
int isEqual(char *comp, char *to){
  int compSize, toSize;
  compSize = strlength(comp);
  toSize = strlength(to);
  if(compSize != toSize)
    return 0;
  else{
    for(int i =0; i<compSize;i++)
      if(*(comp+i) != *(to+i))
	return 0;
      }
  return 1;
}

//Function to print methods
void printTokens(char **vector){
  char **pVector;
  pVector = vector;
  
  while(*pVector != (char *)0){
    printf("%s\n", *pVector);
    pVector++;
  }
}
//Function to free memory allocated
void freeVector(char **vector){
  int count = 0;
  while(vector[count] != (char *)0){
    int word = strlength(vector[count]);
    free(vector[count]);
    count++;
  }
  free(vector);
}

void concat(char *str1, char *str2){
  char *pStr1, *pStr2;
  pStr1 = str1;
  pStr2 = str2;
  int newSize = 0;
  int i = 0;
  while(*pStr1 != '\0'){
    newSize++;
    pStr1++;
    i++;
  }

  while(*pStr2 != '\0'){
    newSize++;
    pStr2++;
  }
  
  newSize++;

  int j;
  str1 = (char *)realloc(str1, newSize);

  for(j=0; i < newSize; j++, i++){
    str1[i] = str2[j];

  }
  str1[i]='\0';
  
}
