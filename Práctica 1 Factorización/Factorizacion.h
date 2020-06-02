/***      Basic Algorithms
* Date: February 16th 2020
* By: Edgar Adrian Nava Romo
* Master and Professor: Sandra Diaz Santiago
* Requeriments: gcc, gmp
* For more information please consult GMP library and Pollard Roh's algorithm.
* The GMP library let C store big numbers and work with them with low cost of resources to the machine.
* For this program I will use GCD Euclides Algorithm, Pollard Roh's algorithm and GCD by prime factorization method
***/

//Libraries
#include <stdio.h>
#include <gmp.h>
#include <time.h>
#include "constants.h"

//Definitions
#define FACTORS_ARRAY_SIZE 1000
#define MAX_LINE_LENGTH 256

//Functions
int factorize(mpz_t, mpz_t[]);
int find_in_table(mpz_t, mpz_t[]);
int pollards(mpz_t, mpz_t[], int);
void nextprime(mpz_t, mpz_t, mpz_t);
void Print_Factors(mpz_t[], int);
void GCD_Factors(int, int, mpz_t[], mpz_t[]);
void euclidean(mpz_t, mpz_t);
