/*
License: GNU GPLv2
Author: Lakshy Sharma
Description: This file contains the function for calculation of greatest common divisor.
*/
#include <stdio.h>

int recursiveGCD(int number1, int number2) {
  int gcd;
  if (number1 == 0) {
    return number2;
  } else if (number2 == 0) {
    return number1;
  } else {
    gcd = recursiveGCD(number2, number1 %number2);
  }
  return gcd;
}

int iterativeGCD(int number1, int number2) {
  return 0;
}

int main() {
  // Gather inputs.
  int number1, number2, method, result;
  printf("Input your integer 1: ");
  scanf("%d", &number1);
  printf("Input your integer 2: ");
  scanf("%d", &number2);
  printf("Press 1 for recursive calculations or 2 for iterative calculations: ");
  scanf("%d", &method);


  // Call your respective function.
  if (method == 1) {
    result = recursiveGCD(number1, number2);
  } else {
    result = iterativeGCD(number1, number2);
  }

  printf("The GCD of your numbers is: %d.\n", result);
  return 0;
}