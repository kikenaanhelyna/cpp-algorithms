/*This program uses the following functions - strcat(), strcpy(), strlen(),
sprintf(), and scanf().
This program does the following:
Prompts the user for their first name followed by their last name. 
Prompts the user to enter their lucky number (from 1 to 99).
Creates a username for the person which is the person's first name initial 
followed by their last name followed by their lucky number. 
Prompts the user for 3 other names (first names only) and stores them in 
the 3-element array that is passed in as the third parameter.
You may assume that no name will exceed 30 characters in length, so a 
full name cannot exceed 61 characters in length when the space is added in.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getData(char**, char*[]);

int main() {
  char* username;
  char* teamNames[3];
  int   luckyNum;
  luckyNum = getData(&username, teamNames);
  printf("The username is %s\n", username);
  printf("%s's lucky number is %d.\n", username, luckyNum);
  printf("The team members are:\n  - %s\n  - %s\n  - %s\n",
                     teamNames[0],teamNames[1],teamNames[2]);
  return 0;
}

int getData(char** uname, char* team[]) {
  int luckyNumber;
  char fName[30], lName[30];

  printf("Please enter your first and last name: ");
  scanf("%s %s", fName, lName);

  printf("%s %c., enter your lucky number (<100): ", fName, lName[0]);
  scanf("%d", &luckyNumber);

  *uname = (char*)malloc(sizeof(char)*(strlen(lName)+4));
  sprintf(*uname,"%c%s%d",fName[0],lName,luckyNumber);

  int i=0;
  for(i=0; i<3; i++) {
    printf("Please enter team member %d: ",i+1);
    scanf("%s",fName);
    team[i] = (char*)malloc(sizeof(char)*(strlen(fName)+1));
    strcpy(team[i],fName);
  }
  return luckyNumber;
}
