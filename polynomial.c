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
  rational *coefficients;
};

struct rational_internal {
  bool sign;
  unsigned long a;
  unsigned long b;
};

// Function to initialise a polynomial, given the degree and coefficients
// UNTESTED
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
  // Copy the coefficients pointers into the polynomial
  _temp->coefficients = calloc((size_t)(degree + 1), sizeof(rational));
  for (int i = 0; i < degree + 1; i++) {
    memcpy(_temp->coefficients[i], coefficients[i],
           sizeof(struct rational_internal));
  }
  return _temp;
}

polynomial add_polynomial(polynomial a, polynomial b) {
  if (a == NULL || b == NULL) {
    fprintf(stderr, "Passed NULL pointer");
    return NULL;
  }
  polynomial bigger;
  polynomial smaller;
  if (a->degree > b->degree) {
    bigger = a;
    smaller = b;
  } else {
    bigger = b;
    smaller = a;
  }
  rational summed_coefficents[bigger->degree];
  for (int i = 0; i < smaller->degree + 1; i++) {
    summed_coefficents[i] =
        add_rational(bigger->coefficients[i], smaller->coefficients[i]);
  }
  for (int i = smaller->degree + 1; i < bigger->degree + 1; i++) {
    summed_coefficents[i] = bigger->coefficients[i];
  }
  polynomial sum = init_polynomial(bigger->degree, summed_coefficents);
  return sum;
}

bool destroy_polynomial(polynomial to_destroy) {
  if (to_destroy == NULL) {
    fprintf(stderr, "Passed NULL pointer");
    return false;
  }
  free(to_destroy->coefficients);
  free(to_destroy);
  return true;
}
