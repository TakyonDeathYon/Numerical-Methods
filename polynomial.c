#include "polynomial.h"
#include "rational.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct for polyonmials, used internally
// The coeffieients start with the smallest and increase
// i.e. [-1/2, 3, 4] is -1/2 + 3x +4x^2
struct polynomial_internal {
  unsigned int degree;
  rational coefficients;
};

// Redefining the internal structure of a rational as it is needed here
struct rational_internal {
  bool sign;
  unsigned long a;
  unsigned long b;
};

// Function to initialise a polynomial, given the degree and coefficients
polynomial init_polynomial(unsigned int degree, rational *coefficients) {
  // Check if pointer passed is NULL
  if (coefficients == NULL) {
    fprintf(stderr, "Passed NULL pointer");
    return NULL;
  }
  // Initialise the pointer to return
  polynomial _temp = calloc(1, sizeof(struct polynomial_internal));
  // Set the degree
  _temp->degree = degree;
  // Calloc the correct amount of space at the end of the struct to hold the
  // rationals
  _temp->coefficients =
      calloc((size_t)(degree + 1), sizeof(struct rational_internal));
  // For each coefficient copy the value from the pointer into the new struct
  // The coefficients are stored in one block of continuous memory, and
  // referencing them via [i] will return the struct rational_internal type, and
  // thus to pass stuff into the rational functions, you need to pass the
  // address
  for (unsigned int i = 0; i < degree + 1; i++) {
    memcpy(&_temp->coefficients[i], coefficients[i],
           sizeof(struct rational_internal));
  }
  // Return a pointer to the polynomial
  return _temp;
}

// A function to print out a polynomial, it prints the
// coefficients, in the form: a + (b)x^1 + (c)x^2 + ...
bool print_polynomial(polynomial to_print) {
  // Check if the passed pointer is null
  if (to_print == NULL) {
    fprintf(stderr, "Passed NULL pointer");
    return false;
  }
  // Print the first coefficient, since it always exists and
  // if formatted differently
  print_rational(&to_print->coefficients[0]);
  printf(" + ");
  // Loop through all the coefficients and print them
  for (unsigned int i = 1; i < to_print->degree + 1; i++) {
    printf("(");
    print_rational(&to_print->coefficients[i]);
    printf(")x^%u + ", i);
  }
  // Remove the last printed " + "
  printf("\b\b\b   ");
  return true;
}

polynomial add_polynomial(polynomial a, polynomial b) {
  // Check if the passed pointer is null
  if (a == NULL || b == NULL) {
    fprintf(stderr, "Passed NULL pointer");
    return NULL;
  }
  // Initialise the variables to refer to the bigger and smaller polynomials
  polynomial bigger;
  polynomial smaller;
  if (a->degree > b->degree) {
    bigger = a;
    smaller = b;
  } else {
    bigger = b;
    smaller = a;
  }
  // Initialise a list with the correct length for the summed coefficients
  rational summed_coefficents[bigger->degree];
  // For all the length of the smaller polynomial, set the summed coefficients
  // to be the sum of the a one with the b
  for (unsigned int i = 0; i < smaller->degree + 1; i++) {
    summed_coefficents[i] =
        add_rational(&bigger->coefficients[i], &smaller->coefficients[i]);
  }
  // For the rest of the polynomial, just take the values from the longer
  // polynomial, since the smaller one doesn't have any
  for (unsigned int i = smaller->degree + 1; i < bigger->degree + 1; i++) {
    summed_coefficents[i] = &bigger->coefficients[i];
  }
  // Initialise a polynomial to return with correct values
  polynomial sum = init_polynomial(bigger->degree, summed_coefficents);
  // Make sure to free the memory after using it
  for (unsigned int i = 0; i < smaller->degree + 1; i++) {
    destroy_rational(summed_coefficents[i]);
  }
  // Return a pointer to the sum
  return sum;
}

// A function to multiply two polynomials
polynomial mult_polynomial(polynomial a, polynomial b) {
  // The degree of the new polynomial is the sum of the degrees of the
  // ones you multiply
  unsigned int _new_deg = a->degree + b->degree;
  // Initialise temporary variables to calculate the coefficients
  rational _coeffs[_new_deg];
  rational _temp_sum;
  rational _multiplied;
  rational _temp_destroy;
  // Loop through each power of x in the new polynomial
  for (unsigned int i = 0; i < _new_deg + 1; i++) {
    // Reset the sum for the current power to 0
    _temp_sum = init_rational(true, 0, 1);
    // For each power, loop through all the combinations of powers of x in a
    // and b that add to the new power i.e. for x^2 in the new polynomial, you
    // need to have x^0 and x^2, x^1 and x^1 and x^2 and x^0
    for (unsigned int j = 0; j < i + 1; j++) {
      if (j < a->degree + 1 && (i - j) < b->degree + 1) {
        // Multiply the coefficients of the pairs of powers together, and add
        // them together
        _multiplied =
            mult_rational(&a->coefficients[j], &b->coefficients[i - j]);
        // Assign the old value to a holder, so it can be destroyed afterwards
        _temp_destroy = _temp_sum;
        // Add the previous sum to the multipled value
        _temp_sum = add_rational(_temp_sum, _multiplied);
        // Destroy the temporary values
        destroy_rational(_temp_destroy);
        destroy_rational(_multiplied);
      }
    }
    // Put the sum now as the coefficient
    _coeffs[i] = _temp_sum;
  }
  // Initialise the polynomial to return, with the correct coefficients
  polynomial to_return = init_polynomial(_new_deg, _coeffs);
  // Destroy the left over memory
  for (unsigned int i = 0; i < _new_deg + 1; i++) {
    destroy_rational(_coeffs[i]);
  }
  // Return a pointer to the product
  return to_return;
}

// A function to free all the memory assosiated with a polynomial
bool destroy_polynomial(polynomial to_destroy) {
  // Check if the pointer passed is null
  if (to_destroy == NULL) {
    fprintf(stderr, "Passed NULL pointer");
    return false;
  }
  // First free the memory that the coefficients are stored in, then the main
  // location of the struct
  free(to_destroy->coefficients);
  free(to_destroy);
  return true;
}
