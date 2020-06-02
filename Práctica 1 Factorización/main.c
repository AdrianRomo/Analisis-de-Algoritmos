/***      Basic Algorithms
* Date: February 16th 2020
* By: Edgar Adrian Nava Romo
* Master and Professor: Sandra Diaz Santiago
* Requeriments: gcc, gmp
* For more information please consult GMP library and Pollard Roh's algorithm.
* The GMP library let C store big numbers and work with them with low cost of resources to the machine.
* For this program I will use GCD Euclides Algorithm, Pollard Roh's algorithm and GCD by prime factorization method
***/

#include "Factorizacion.h"

/*** Main
Buffer: number of character that will be accepted
line: the number will be treated as char with the size of the buffer
current_N: this will be manipulated inside the functions, in first instance
***/
int main(int argc, char *argv[]) {
  int i;
  char buffer[MAX_LINE_LENGTH],buffer2[MAX_LINE_LENGTH];
  const char *line , *line2;
  mpz_t factors[1000] , factors2[1000];

  for (i = 0; i < FACTORS_ARRAY_SIZE; i++) { mpz_init(factors[i]); } //Test Factor_array_size for 1000 numbers
  printf("Insert 2 numbers\n\n");
  //Inputs
  printf("Insert a = ");
  line = fgets(buffer, sizeof(buffer), stdin);
  printf("Insert b = ");
  line2 = fgets(buffer2, sizeof(buffer2), stdin);
  mpz_t current_N, current_N2;
  mpz_init(current_N);
  mpz_set_str(current_N, line, 10);
  mpz_init(current_N2);
  mpz_set_str(current_N2, line2, 10);
  clock_t begin = clock();//Init Time Counter
  //Outputs
  //isprime(current_N);
  //isprime(current_N2);
  gmp_printf("\nGCD with Euclides Algorithm");
  euclidean(current_N, current_N2);

  printf("\nFactorization:\n");
  printf("\na = ");
  int factoresFirstN= factorize(current_N, factors);
  printf("\nb = ");
  int factoresSecondN= factorize(current_N2, factors2);
  GCD_Factors(factoresFirstN, factoresSecondN, factors, factors2);
  clock_t end = clock(); // End Time Counter
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("\ntook %f seconds to execute \n", time_spent);
  return 0;
}

/***                    Ejercicio 2
*         Factorizes N using Pollard's Rho Algorithm
*
* We get as parameters:
* N: Number given by user to factorize
* factors[]: Created array to store all the factors of N
* Steps:
* We search in the table of primes in "Constants.h" all the n
*
* Complexity: its expected running time is proportional to the square root of the
* size of the smallest prime factor of the composite number being factorized.
* Due to the use of probabilistic numbers in this algorithm, the complexity in Pollard's Roh
* algorithm is O(n^1/4 polylog(n)) with a probability of 0.5.
*
***/

int factorize(mpz_t N, mpz_t factors[]) {
  mpz_t x;
  int num_factors = 0;
  num_factors = find_in_table(N, factors);
  int result;
  mpz_init(x);
  mpz_set_ui(x,1UL);
  do {
    /** mpz_probab_prime_p performs some trial divisions, a Baillie-PSW probable prime test,then reps-24
    * Miller-Rabin probabilistic primality tests. A higher reps value will reduce the chances of a non-prime being identified as
    *“probably prime”. A composite number will be identified as a prime with an asymptotic probability of less than 4^(-reps).
    * Reasonable values of reps are between 15 and 50. **/
    mpz_set(factors[100],x);
    if(mpz_probab_prime_p(N, 50)) {
      gmp_printf(" %Zd ", N);
      mpz_set(factors[100],N);
      mpz_set_ui(N, 1);
      break;
    }
    result = pollards(N, factors, num_factors);
    if (!result) {
      break;
    }
    num_factors++;
  } while (mpz_cmp_si(N, 1) != 0);
  // If N != 1 (it's not fully factorized)
  if (mpz_cmp_si(N, 1)) {
    printf("Aborted, factorization not possible \n");
    return 0;
  }
  else {
    // Print_Factors(factors, num_factors, x);
    Print_Factors(factors, num_factors);
    return num_factors;
  }
  printf("\n");
}
/*
* Search in constants.h to save time
*/
int find_in_table(mpz_t N, mpz_t factors[]) {
  int i;
  int factor_index = 0;
  unsigned long int remainder;
  mpz_t factor;
  mpz_init(factor);
  for (i = 0; i < FIRST_PRIMES_SIZE; i++) {
    remainder = mpz_fdiv_ui(N, first_primes[i]);
    if (remainder == 0) {
      /* Remove all occurrences of this factor from N.
      All occurrences must be stored. */
      while (remainder == 0) {
        mpz_set_ui(factor, first_primes[i]);
        mpz_set(factors[factor_index], factor);
        factor_index++;
        mpz_fdiv_q_ui(N, N, first_primes[i]);
        remainder = mpz_fdiv_ui(N, first_primes[i]);
      }
    }
  }
  mpz_clear(factor);
  return factor_index;
}
/*
* If the number isn't in the prime table, pollard will get the random prime number generated before and continue with the algorithm
*/
int pollards(mpz_t N, mpz_t factors[], int num_factors) {

  // Initialize random number container
  mpz_t xi_last;
  mpz_init(xi_last);

  // Initialize and get random first factor
  gmp_randstate_t rand_state;
  gmp_randinit_default(rand_state);
  gmp_randseed_ui(rand_state, time(NULL));

  // Set random number
  mpz_urandomm(xi_last, rand_state, N);

  //Get last random factor
  mpz_t x2i_last;
  mpz_init(x2i_last);
  nextprime(x2i_last, xi_last, N);

  mpz_t xi, x2i, diff;
  mpz_init(xi); mpz_init(x2i); mpz_init(diff);

  mpz_t d;
  mpz_init(d);

  mpz_t count;
  mpz_init_set_ui(count, 0);
  mpz_t limit;
  mpz_init(limit);
  //We're gonna compare N in base 2, this is, to use the less memory we can using different range of bits
  if (mpz_sizeinbase(N,2) > 40) {
    mpz_set_ui(limit, 100000);
  } else if (mpz_sizeinbase(N,2) > 20) {
    mpz_set_ui(limit, 90000);
  } else {
    mpz_set_ui(limit, 20000);
  }
  // N will be reduced until
  while(mpz_cmp(count, limit) < 0) {
    nextprime(xi, xi_last, N);

    nextprime(x2i, x2i_last, N);
    nextprime(x2i, x2i, N);

    mpz_sub(diff, x2i, xi);
    mpz_gcd(d, diff, N);
    //If (x2i-xi)-(gcd(diff,N) compared to 1 > 0) -> return 1 and set d as number of factors, N will be now N = N / d
    if(mpz_cmp_si(d, 1) > 0) {
      mpz_set(factors[num_factors],d);
      mpz_fdiv_q(N, N, d);
      return 1;
    }
    mpz_set(xi_last, xi);
    mpz_set(x2i_last, x2i);
    mpz_add_ui(count,count,1);
  }
  // Clear variables
  mpz_clear(xi_last); mpz_clear(x2i_last); mpz_clear(xi); mpz_clear(x2i); mpz_clear(diff);

  return 0;
}
/**                   nextprime function
* here, we're gonna get the next prime according to the formula (x^2+1) mod N,
* this will find the prime number next to N and N = nextprime to get factors,
* There are 2 ways to solve it, the (x^2 +1) mod N will repeat somewhere or
**/
void nextprime(mpz_t next, mpz_t prev, mpz_t N) {
  mpz_pow_ui(next, prev, 2); // X^2
  mpz_add_ui(next, next, 1); // X^2 + 1
  mpz_mod(next, next, N);    // (X^2 + 1) mod N
}

void Print_Factors(mpz_t factors[], int num_factors) {
  int i;
  for (i = 0; i < num_factors; i++) {
    gmp_printf("* %Zd ", factors[i]);
  }
}

/***                    Ejercicio 3
* Implement a Funtion to calculate GCD of 2 numbers with prime factorization Algorithm
* factoresFirstN -> number of factors that are in factors[]
* factoresSecondN -> number of factors that are in factors2[]
* factors[] -> array of factors in number "a"
* factors2[] -> array of factors in number "b"
* This function first detects wich number has more factors, and store it in fac1 or fac2 depending the case
* then, we took the largest array and compare it with the other, finding the common numbers in both arrays
* At last, all the common numbers are multiplied and stored in "add".
* Complexity: The complexity of the alforithm to compare the two arrays is of O(n+m) at the worst case
***/
void GCD_Factors(int factoresFirstN, int factoresSecondN, mpz_t factors[], mpz_t factors2[]){
  int i = 0, j = 0, savePosition = 0, fact1, fact2;
  mpz_t add, fac1[200], fac2[200];
  mpz_init(add);
  mpz_set_ui(add,1);
  printf("\n\nCommon Factors = ");
  for (size_t k = 0; k < 200; k++) {
    mpz_init(fac1[k]);
    mpz_init(fac2[k]);
  }
  if (mpz_cmp(factors2[100], factors[100]) == 0) {
    gmp_printf(" * %Zd", factors[100]);
    mpz_mul(add,add,factors[100]);
  }
  if (factoresFirstN >= factoresSecondN) {
    fact1 = factoresFirstN;
    fact2 = factoresSecondN;
    for (size_t k = 0; k < 100; k++) {
      mpz_set(fac1[k], factors[k]);
      mpz_set(fac2[k], factors2[k]);
    }

  } else{
    fact2 = factoresFirstN;
    fact1 = factoresSecondN;
    for (size_t k = 0; k < 100; k++) {
      mpz_set(fac1[k], factors2[k]);
      mpz_set(fac2[k], factors[k]);
    }
  }
  while(fact1 > i && fact2 > j){
    if (mpz_cmp(fac1[i], fac2[j]) < 0) {
      i++;
    }else if(mpz_cmp(fac2[j], fac1[i])){
      j++;
    } else {
      gmp_printf(" * %Zd", fac1[i]);
      mpz_mul(add,add,fac1[i]);
      i++;
      j++;
    }
    mpz_clear(add);
  }
  if(mpz_get_ui(add) == 1)
  printf(" is the only Factor in common\n");
  else
  gmp_printf("\nGCD = %Zd\n", add);

}

/***                    Ejercicio 4
*           Implement a function with Euclidean Factorization Algorithm
* We get as parameters:
* numero1 -> first number given by user
* numero2 -> second number given by user
*
* Description: The original version of Euclid’s algorithm is based on subtraction:
* we recursively subtract the smaller number from the larger.
* Let’s estimate this algorithm’s time complexity (based on n = a+b).
* The number of steps can be linear, for e.g. gcd(x, 1), so the time complexity is O(n).
* This is the worst-case complexity, because the value x + y decreases with every step.
*
***/

void euclidean(mpz_t numero1, mpz_t numero2){
  mpz_t a, b, r;
  mpz_init(a); mpz_init(b); mpz_init(r);

  mpz_set_ui(r,1);
  if (mpz_cmp(numero1, numero2) > 0) {
    mpz_set(a,numero1);
    mpz_set(b,numero2);
  } else{
    mpz_set(b,numero1);
    mpz_set(a,numero2);
  }
  while (mpz_cmp_ui (b, 0)!= 0){
    mpz_sub(r, a, b); // r = a - b

    if (mpz_cmp(r, b) >= 0){ mpz_set (a,r); }
    else { mpz_set (a,b); mpz_set (b,r); }

  }
  gmp_printf(": %Zd\n" , a);
  mpz_clear(a); mpz_clear(b); mpz_clear(r);
}
