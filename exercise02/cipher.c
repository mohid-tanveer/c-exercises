#include <ctype.h>
#include <stdio.h>
#include <string.h>

// cipherText is given a phrase as well as the substitution pad and ciphers the phrase
// using mathematical manipulation of the characters with regards to ASCII values.
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

// this program allows the user to input a substitution pad in order to encrypt a phrase. 
// for example, if the subpad is qwertyuiopasdfghjklzxcvbnm, then the letter a will be 
// replaced by q, b with w, c with e, etc.
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
