#include <stdio.h>
#include <string.h>

// Reverses word - Does not return anything; rather prints in place backwards.
void reverseWord(char *word) {
  int len = strlen(word);
  // Iterates backwards from length of the string minus 1 printing each char in
  // the word
  for (int i = (len - 1); i >= 0; i--) {
    printf("%c", word[i]);
  }
  printf("\n");
}

// Takes a singular word and prints it regularly as well as the reversed word through the 
// reverseWord function. The main function focuses on formatting of text printed.
int main() {
  char word[50];
  while (1) {
    printf("Enter a word (ctrl-C to quit): ");
    scanf("%s", word);
    printf("%s --> ", word);
    reverseWord(word);
  }
  return 0;
}
