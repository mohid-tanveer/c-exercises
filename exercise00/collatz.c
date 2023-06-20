#include <stdio.h>

// function takes number and recursively runs the collatz sequence and keeps track of
// length of sequence. (the collatz sequence basically states that “as long as n is 
// not 1: if n is even, n becomes n/2; otherwise, n becomes 3n+1.”)
void collatz(int *add_number, int *add_count) {
  while (*add_number != 1) {
    if (*add_number % 2 == 0) {
      *add_number /= 2;
      *add_count += 1;
    } else {
      *add_number = (*add_number * 3) + 1;
      *add_count += 1;
    }
  }
  *add_count += 1;
}

// runs an input loop that will take the input number and run a collatz sequence.
// prints the starting number and the length of the sequence.
int main() {
  int number = 0;
  int numberfinal = 0;
  int count = 0;
  while (1) {
    // checks that the input value is a valid positive number.
    while (number < 1) {
      printf("Enter a number that is greater than 0 (CTRL-C to quit): ");
      scanf("%d", &number);
      printf("\n");
    }
    numberfinal = number;
    collatz(&numberfinal, &count);
    printf("%d -> %d\n\n", number, count);
    number = 0;
    count = 0;
  }
  return 0;
}
