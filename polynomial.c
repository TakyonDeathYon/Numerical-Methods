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
  _temp->coefficients =
      calloc((size_t)(degree + 1), sizeof(struct rational_internal));
  for (unsigned int i = 0; i < degree + 1; i++) {
    memcpy(&_temp->coefficients[i], coefficients[i],
           sizeof(struct rational_internal));
  }
  return _temp;
}

bool print_polynomial(polynomial to_print) {
  if (to_print == NULL) {
    fprintf(stderr, "Passed NULL pointer");
    return false;
  }
  printf("Degree: %u\n", to_print->degree);
  printf("Coefficients: ");
  for (unsigned int i = 0; i < to_print->degree + 1; i++) {
    print_rational(&to_print->coefficients[i]);
    printf(", ");
  }
  printf("\b\b   \n");
  return true;
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
  for (unsigned int i = 0; i < smaller->degree + 1; i++) {
    summed_coefficents[i] =
        add_rational(&bigger->coefficients[i], &smaller->coefficients[i]);
  }
  for (unsigned int i = smaller->degree + 1; i < bigger->degree + 1; i++) {
    summed_coefficents[i] = &bigger->coefficients[i];
  }
  polynomial sum = init_polynomial(bigger->degree, summed_coefficents);
  return sum;
}

polynomial mult_polynomial(polynomial a, polynomial b) {
  polynomial bigger;
  polynomial smaller;
  if (a->degree > b->degree) {
    bigger = a;
    smaller = b;
  } else {
    bigger = b;
    smaller = a;
  }
  unsigned int new_deg = bigger->degree + smaller->degree;
  rational coeffs[new_deg];
  rational _temp_sum;
  rational _multiplied;
  for (unsigned int i = 0; i < new_deg + 1; i++) {
    _temp_sum = init_rational(true, 0, 1);
    for (unsigned int j = 0; j < i + 1; j++) {
      if (j < bigger->degree + 1 && (i - j) < smaller->degree + 1) {
        _multiplied = mult_rational(&bigger->coefficients[j],
                                    &smaller->coefficients[i - j]);
        _temp_sum = add_rational(_temp_sum, _multiplied);
        destroy_rational(_multiplied);
      }
    }
    coeffs[i] = _temp_sum;
  }
  polynomial to_return = init_polynomial(new_deg, coeffs);
  for (unsigned int i = 0; i < new_deg + 1; i++) {
    destroy_rational(coeffs[i]);
  }
  return to_return;
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
