#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
  char roomName[50];
  char roomCode[5];
  char roomDescription[512];
} Room;

Room* roomsCreate(FILE *fp);
void printRooms(Room *rooms);


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

  Room* rooms = roomsCreate(fp);
  printRooms(rooms);

  return 0;
}

Room* roomsCreate(FILE *fp){
  char buffer[512];
  char sep[] = ":";

  int counter = 0;
  int numOfRooms = 10;
  Room *rooms = malloc(sizeof(Room)*numOfRooms);

  while(fgets(buffer, sizeof(buffer), fp)){
    char *tp = strtok(buffer, sep);
    char *desc = strtok(NULL, sep);
    desc++;
    
    int compare = strcmp(tp, "Room Name");
    if (compare == 0) counter+=1;
    
    if (counter == numOfRooms){
      numOfRooms*=2;
      rooms = realloc(rooms, sizeof(Room)*numOfRooms);
    }

    int findName = strcmp(tp, "Room Name");
    int findCode = strcmp(tp, "Room Code");
    int findDesc = strcmp(tp, "Room Description");

    if (findName == 0) strcpy(rooms[counter-1].roomName, desc);
    if (findCode == 0) strcpy(rooms[counter-1].roomCode, desc);
    if (findDesc == 0) strcpy(rooms[counter-1].roomDescription, desc);

  }
  return rooms;
}

void printRooms(Room *rooms){
  int size = sizeof(rooms)/sizeof(rooms[0]);
  // for (int i = 0; i < 20; i++){
  //   printf("Room %s: %s",rooms[i].roomCode, rooms[i].roomName);
  // }
  printf("%d", size);
}