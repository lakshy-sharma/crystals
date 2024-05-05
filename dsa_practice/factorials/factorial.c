/*
License: GNU GPLv2
Author: Lakshy Sharma
Description: This file contains the algorithm to calculate the factorial of a number using recursive as well as iterative approach.
Language: C
*/
#include <stdio.h>

int recursiveFactorial(int number) {
  int factorial;
  if (number == 0) {
    return 1;
  } else {
    factorial = number * recursiveFactorial(number -1);
  }
  return factorial;
}

int iterativeFactorial(int number) {

  int factorial = 1, i;
  for (i=1; i <= number; i++) {
    factorial = factorial * i;
  }
  return factorial;
}

int main() {
  // Gather inputs.
  int number, method, result;
  printf("Please input an integer to calculate the factorial for: ");
  scanf("%d", &number);
  printf("Press 1 for recursive calculations or 2 for iterative calculations: ");
  scanf("%d", &method);


  // Call your respective function.
  if (method == 1) {
    result = recursiveFactorial(number);
  } else {
    result = iterativeFactorial(number);
  }

  printf("The factorial of your number is: %d.\n", result);
  return 0;
}