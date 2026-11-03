#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
  char roomName[50];
  char roomCode[5];
  char roomDescription[512];
} Room;

//int findNumOfRooms(FILE *fp)

int main(int argc, char *argv[]){
  if(argc > 2){
    printf("too many arguments");
    return 1;
  }

  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL){
    printf("Could not open file\n");
    return 1;
  }
  
  
  char buffer[512];
  char sep[] = ":";
  char space[] = " ";

  int counter = 0;
  int numOfRooms = 10;
  Room *rooms = malloc(sizeof(Room)*numOfRooms);

  while(fgets(buffer, sizeof(buffer), fp)){
    char *tp = strtok(buffer, sep);
    char *desc = strtok(NULL, sep);
    //desc = strtok(NULL, space);
    printf("%s\n", buffer);
    
    int compare = strcmp(tp, "Room Name");
    if (compare == 0) counter+=1;
    
    if (counter == numOfRooms){
      numOfRooms*=2;
      rooms = realloc(rooms, sizeof(Room)*numOfRooms);
    }

    int findName = strcmp(tp, "Room Name");
    int findCode = strcmp(tp, "Room Name");
    int findDesc = strcmp(tp, "Room Name");

    if (findName == 0){ strcpy(rooms[counter-1].roomName, desc); printf("%s\n",desc);}
    if (findCode == 0) strcpy(rooms[counter-1].roomCode, desc);
    if (findDesc == 0) strcpy(rooms[counter-1].roomDescription, desc);

  }

  printf("%s\n",rooms[0].roomName);

  return 0;
}
