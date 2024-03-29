#include <stdio.h>
#include <stdlib.h>

// this program allows for both manual input and file input by reading integers from standard
// input (one per line) and adding them to a data structure. when an end of file character is
// met the program prints the digits in reverse order. try running "$ cat nums.txt | ./reverse"
// for sample output compared to the nums.txt file.
int main() {
  int *nums = malloc(sizeof(int)); // allocate initial memory for one integer
  int i = 0;
  char input[256]; // sets buffer size of 256 characters including null
                   // terminator from input
  while (fgets(input, 256, stdin) != NULL) {
    int num = atoi(input);
    nums[i] = num;
    i++;
    nums = realloc(
        nums,
        (i + 1) *
            sizeof(int)); // allocate additional memory for one more integer
  }
  for (int j = i - 1; j >= 0; j--) {
    printf("%d ", nums[j]);
  }
  printf("\n");
  free(nums);  // free dynamically allocated memory
  nums = NULL; // sets nums pointer to null.
  return 0;
}
