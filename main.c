#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
  char roomName[50];
  char roomCode[3];
  char roomDescription[500];
} Room;

int main(int argc, char *argv[]){
  if(argc > 2){
    printf("too many arguments");
    return 1;
  }

  FILE *fp = fopen(argv[1], "r");
  
  char buffer[512];
  char sep[] = ":";

  if (fp == NULL){
    printf("Could not open file\n");
    return 1;
  }

  while(fgets(buffer, sizeof(buffer), fp)){
    char *tp = strtok(buffer, sep);
    printf("%s\n", buffer);
  }




  return 0;
}
