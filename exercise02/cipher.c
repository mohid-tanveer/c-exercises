#include <ctype.h>
#include <stdio.h>
#include <string.h>

void cipherText(char *phrase, char *subPad) {
  int difference[26];
  char alpha[] = "abcdefghijklmnopqrstuvwxyz";
  for (int i = 0; i < 26; i++) {
    difference[i] = subPad[i] - alpha[i];
  }
  for (int i = 0; i < strlen(phrase); i++) {
    if (islower(phrase[i])) {
      for (int j = 0; j < 26; j++) {
        if (alpha[j] == phrase[i]) {
          int index = j;
          phrase[i] += difference[j];
          break;
        }
      }
    }
  }
  printf("%s", phrase);
}

int main() {
  char phrase[1024];
  char subPad[26];
  printf("Enter substitution pad: ");
  scanf("%s", subPad);
  printf("Type in phrases to translate or (ctrl-C) to quit.");
  while (1) {
    fgets(phrase, 1024, stdin);
    cipherText(phrase, subPad);
  }
  return 0;
}
