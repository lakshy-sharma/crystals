/*
License: GNU GPLv2
Author: Lakshy Sharma
Description: Generate all primes upto a given number a given number using sieve or factorization.
Language: Golang
*/

package main

import (
	"fmt"
	"math"
	"reflect"
	"time"
)

func timer(name string) func() {
	start := time.Now()
	return func() {
		fmt.Printf("%s took %v\n", name, time.Since(start))
	}
}

func factorisationTest(testNumber int) bool {
	// Calculate the root of the number and reduce the calculation range by half.
	root := int(math.Sqrt(float64(testNumber)))
	for i := 2; i <= root+1; i++ {
		if testNumber%i == 0 {
			return false
		}
	}
	return true
}

func fastPrimeFactorisation(target int) []int {
	defer timer("factorisation")()
	var primes = []int{2}

	for testNumber := 2; testNumber <= target; testNumber++ {
		if factorisationTest(testNumber) {
			primes = append(primes, testNumber)
		}
	}
	return primes
}

func generateSieveofEratosthenes(target int) []int {
	defer timer("sieve")()
	// Generate the sieve and a list to hold all primes.
	var sieve = make([]int, target+1)
	var primes []int

	// Iterate over the sieve with a seed value of 2.
	for generatorNum := 2; generatorNum <= target; generatorNum++ {

		// All composites are marked as 1 so skip any composites.
		if sieve[generatorNum] != 1 {
			// If number isnt composite then add it to list of primes and compute all its multiples.
			primes = append(primes, generatorNum)
			// Start by multiplication with 2 and go up until your multiples exceed the total target.
			for multiple := 2; multiple*generatorNum <= target; multiple++ {
				// For each multiple mark it as a composite in your sieve.
				sieve[generatorNum*multiple] = 1
			}
		}
	}
	return primes
}

func main() {
	var target int

	fmt.Printf("The number to calculate primes upto: ")
	fmt.Scanf("%d", &target)

	fastFactorsResult := fastPrimeFactorisation(target)
	sieveResult := generateSieveofEratosthenes(target)

	if reflect.DeepEqual(fastFactorsResult, sieveResult) {
		fmt.Println("Cross check result: Pass")
		fmt.Printf("The primes upto %d:\n%d.\n", target, sieveResult)
	} else {
		fmt.Errorf("Cross check result: Failed")
	}
}
