/*
License: GNU GPLv2
Author: Lakshy Sharma
Description: This file contains the algorithm to calculate the factorial of a number using recursive as well as iterative approach.
Language: Golang
*/
package main

import (
	"fmt"
	"time"
)

func timer(name string) func() {
	start := time.Now()
	return func() {
		fmt.Printf("%s took %v\n", name, time.Since(start))
	}
}

func recursiveFactorials(target int) int {
	var factorial int = 1 // Remember factorials initialize at 1.
	if target == 0 {
		factorial = factorial * 1
	} else {
		factorial = target * recursiveFactorials(target-1)
	}
	return factorial
}

func iterativeFactorials(target int) int {
	defer timer("iterative")()
	var factorial int = 1 // Remember factorials initialize at 1.
	for i := 1; i <= target; i++ {
		factorial = factorial * i
	}
	return factorial
}

func main() {
	// Gather the inputs.
	var target, method, result int

	fmt.Printf("Please input the number to calculate the factorial for: ")
	fmt.Scanf("%d", &target)
	fmt.Printf("Press 1 for recursive calculations and 2 for iterative calculations: ")
	fmt.Scanf("%d", &method)

	// Call the respective function.
	if method == 1 {
		defer timer("recurisve")()
		result = recursiveFactorials(target)
	} else {
		result = iterativeFactorials(target)
	}

	fmt.Printf("The factorial of your number is: %d\n", result)
}
