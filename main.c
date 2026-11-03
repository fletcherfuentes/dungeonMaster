#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <ctype.h>

// making struct
typedef struct{
  char roomName[50];
  //idk why it breaks when i do less than 5
  char roomCode[5];
  char roomDescription[512];
} Room;

// declaring functions
int roomSize(FILE *fp);
Room* roomsCreate(FILE *fp,int size);
//Room* stringTrim(Room *rooms, int size);
void printRooms(Room *rooms, int size);


// command line to get file as the only other argument
int main(int argc, char *argv[]){
  if(argc > 2){
    printf("too many arguments");
    return 1;
  }

  //checking to see if file is readable
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL){
    printf("Could not open file\n");
    return 1;
  }

  int size = roomSize(fp);
  //going back to the start of the file to read it again for making the rooms
  rewind(fp);
  //making the struct array
  Room* rooms = roomsCreate(fp,size);
  
  //printing the room and code
  printRooms(rooms, size);

  return 0;
}

//getting the number of rooms by counting how many times room name is read
int roomSize(FILE *fp){
  char buffer[512];
  char sep[] = ":";

  int counter = 0;
  
  while(fgets(buffer, sizeof(buffer), fp)){
    char *tp = strtok(buffer, sep);
    int compare = strcmp(tp, "Room Name");
    if (compare == 0) counter+=1;
  }
  
  return counter;
}

//takes size as the number of rooms to make the pointer array
Room* roomsCreate(FILE *fp, int size){
  char buffer[512];
  char sep[] = ":";


  Room *rooms = malloc(sizeof(Room)*size);

  int i = 0;
  while(fgets(buffer, sizeof(buffer), fp)){
    // gets what part of the room it is
    char *tp = strtok(buffer, sep);
    // gets the other side of the : with the actual info
    char *desc = strtok(NULL, sep);
    // getting rid of the front space after the :
    desc++;

    // variables to find out if the line has info and what info it has
    int findName = strcmp(tp, "Room Name");
    int findCode = strcmp(tp, "Room Code");
    int findDesc = strcmp(tp, "Room Description");

    // if statements to copy the room info into the structs
    if (findName == 0) strcpy(rooms[i].roomName, desc);
    if (findCode == 0){
      // thought this would shorten the string and get rid of whitespace
      desc[2] == '\0';
      strcpy(rooms[i].roomCode, desc);
    }
    if (findDesc == 0){ 
      //counter to keep track of the rooms
      strcpy(rooms[i].roomDescription, desc);
      i++;
    }

  }
  return rooms;
}

//function to print each of the rooms in a for loop
void printRooms(Room *rooms, int size){
  for (int i = 0; i < size; i++){
    printf("Room %s: %s\n",rooms[i].roomCode, rooms[i].roomName);
  }
}
// Room* stringTrim(Room *rooms,int size){
//   // for(int i = 0; i < size; i++){
//   //   int nameLength = strlen(rooms[i].roomName);
//   //     if (nameLength > 0 && (rooms[i].roomName[nameLength-1] == '\n' || rooms[i].roomName[nameLength-1] == '\r'))
//   //       rooms[i].roomName[nameLength-1] = '\0';
      
//   //   int codeLength = strlen(rooms[i].roomCode);
//   //     if (codeLength > 0 && rooms[i].roomCode[2] == ' ')
//   //       rooms[i].roomCode[2] = '\0';
     
//   //   int descLength = strlen(rooms[i].roomDescription);
//   //     if (descLength > 0 && (rooms[i].roomDescription[descLength-1] == '\n' || rooms[i].roomDescription[descLength-1] == '\r'))
//   //       rooms[i].roomDescription[descLength-1] = '\0';
//   //}
//   //printf("bruh");
//   printf("Room %s: %s\n",rooms[0].roomCode, rooms[0].roomName);
//   return rooms;
// }
