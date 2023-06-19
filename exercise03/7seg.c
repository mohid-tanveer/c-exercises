#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print7Seg(char *input, int *ints) {
  // array holding top, middle, and bottom segments of numbers 0-9
  char segments[10][3][4] = {{" - ", "| |", "|_|"}, {"   ", " | ", " | "},
                             {" - ", " _|", "|_ "}, {" - ", " _|", " _|"},
                             {"   ", "|_|", "  |"}, {" - ", "|_ ", " _|"},
                             {" - ", "|_ ", "|_|"}, {" - ", "  |", "  |"},
                             {" - ", "|_|", "|_|"}, {" - ", "|_|", "  |"}};
  // first for loop allows for first line to print just the top segments and so
  // on for rest of segments
  for (int i = 0; i < 3; i++) {
    // second for loop iterates through the numbers input to print specific
    // segment of the number in the array.
    for (int j = 0; j < strlen(input); j++) {
      printf("%s ", segments[ints[j]][i]);
    }
    printf("\n");
  }
}

int main() {
  char userInput[10];
  int userInts[10];
  while (1) {
    printf("Enter a number (ctrl-c to quit): ");
    scanf("%s", userInput);
    for (int i = 0; i < strlen(userInput); i++) {
      userInts[i] = (int)userInput[i] - 48;
    }
    print7Seg(userInput, userInts);
  }
}
