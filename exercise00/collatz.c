#include <stdio.h>

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

int main() {
  int number = 0;
  int numberfinal = 0;
  int count = 0;
  while (1) {
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
