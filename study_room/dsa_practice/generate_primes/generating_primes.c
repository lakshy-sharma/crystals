/*
 * License: GNU GPLv2
 * Author: Lakshy Sharma
 * Description: Generate all primes upto a given number a given number using sieve or factorization.
 * Language: C
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_STRING_INPUT_LIMIT 20

/*
 * This function calculates the prime factors and tells whether the number has a prime factor or not.
*/
int perform_factorisation_test(int test_number) {
    int pivot_point = (int)sqrt(test_number);
    // Perform the factorisation upto the pivot point.
    // We start from 2 because 0 is illegal and 1 is always a factor.
    for (int potential_factor = 2; potential_factor <= pivot_point+1; potential_factor++){
        if (test_number == 2) {
            return 0;
        }
        if ((test_number % potential_factor) == 0) {
            return -1; // If we have a match then test was a failure.
        }
    }
    return 0; // If we dont have a match then test was not a failure.
}

/*
 * Why: This function finds all prime numbers upto a given point and benchmarks the two methods used for performing the calculations.
 *
 * Args:
 *    target_number: The target number upto where we must calculate the prime numbers.
 *    storage: A pointer to memory location where we must store all our prime numbers.
 *
 * Returns:
 *    Pointer: A Pointer memory 
*/
int find_primes(int target_number) {
    int* factorisation_primes;
    int* eratosthenes_primes;
    int* eratosthenes_sieve;

    // Allocate required memory from the heap.
    if (target_number <= 15) {
        // We might need full memory since below 10 prime numbers are very frequent.
        factorisation_primes = (int*)calloc(target_number, sizeof(int));
        eratosthenes_sieve = (int*)calloc(target_number, sizeof(int));
        eratosthenes_primes = (int*)calloc(target_number, sizeof(int));
    } else {
        // Allocate only half the target number since prime numbers are very less.
        factorisation_primes = (int*)calloc((target_number/2), sizeof(int));
        eratosthenes_sieve = (int*)calloc(target_number, sizeof(int));
        eratosthenes_primes = (int*)calloc((target_number/2), sizeof(int));
    }

    // Prime factorisation
    clock_t start_time, end_time;
    start_time = clock();
    int ref = 0;
    for (int check_number = 2; check_number <= target_number ; check_number++) {
        // If the test passes then append the checked element into the memory.
        if (perform_factorisation_test(check_number) == 0) {
            // Store the number into memory and increase reference by 1.
            factorisation_primes[ref] = check_number;
            ref = ref + 1;
        }
    }
    end_time = clock();
    int time_taken = (end_time - start_time)/1000;
    printf("Time taken by Fast prime factorisation: %d microseconds.\n", time_taken);

    // Sieve of Eratosthenes.
    start_time = clock();
    ref = 0;
    // Start iterating over the sieve with a seed value of 2.
    for (int generator_number = 2; generator_number <= target_number; generator_number++) {
        // Our array is initialized to zero and numbers are marked as 1 if they are composites.
        if (eratosthenes_sieve[generator_number] != 1) {
            // Since our number hasnt yet been marked as composite we can add it as a prime number.
            eratosthenes_primes[ref] = generator_number;
            ref = ref+1;
            // Calculate all the multiples of this prime number and filter them in our sieve.
            for (int multiplier = 2; generator_number*multiplier <= target_number; multiplier++) {
                eratosthenes_sieve[generator_number*multiplier] = 1;
            }
        }
    }
    end_time = clock();
    time_taken = (end_time - start_time);
    printf("Time taken by Sieve of Eratosthenes: %d nanoseconds.\n", time_taken);

    // Cross Checking.
    int check_length = 0;
    if (target_number <=15) {
        check_length = target_number;
    } else {
        check_length = target_number/2;
    }
    for (int i=0; i <= check_length; i++){
        printf("%d,", eratosthenes_primes[i]);
    }
    for (int i=0; i <= check_length; i++){
        printf("%d,", factorisation_primes[i]);
    }
    for (int i=0; i <= check_length; i++){
        if (factorisation_primes[i] != eratosthenes_primes[i]) {
            printf("Cross Check Failed\n");
            printf("%d,%d\n", factorisation_primes[i], eratosthenes_primes[i]);
            break;
        }
    }
    printf("Cross Check Passed\n");
    return 0;
}

/*
The main entrypoint.
*/
int main() {
    // Gather inputs from user.
    int target_number;
    char result_file[MAX_STRING_INPUT_LIMIT];
    printf("Provide the highest integer till where we want to calculate the primes.");
    scanf("%d", &target_number);
    // printf("Provide the path to file to store the results.");
    // fgets(result_file, MAX_STRING_INPUT_LIMIT, stdin);

    // Perform the prime factorisation and sieve of eratosthenes algorithms.
    // Evaluate the performance of both algorithms and return the prime numbers with a cross check.
    find_primes(target_number);

    // Store results in the target file.
    return 0;
}