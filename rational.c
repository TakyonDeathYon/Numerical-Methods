#include "rational.h"
#include "GCD.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct rational_internal {
  bool sign;
  unsigned long a;
  unsigned long b;
};

// A function to initialise a rational number struct
// it returns by value the structure
rational init_rational(bool sign, unsigned long a, unsigned long b) {
  // Throw and error and stop the program if the
  // second value is 0 (i.e a/0)
  if (b == 0) {
    fprintf(stderr,
            "Error: Tried to initialise a rational with division by 0\n");
    exit(EXIT_FAILURE);
  }
  // Adjust the numbers to be coprime
  // ie 10/5 and 20/10 both initialise to 2/1
  unsigned long divisor = calc_gcd(a, b);
  unsigned long adjusted_a;
  unsigned long adjusted_b;
  // Check if the gcd is 0, then make a standard 0 value (0/1)
  if (divisor != 0) {
    adjusted_a = a / divisor;
    adjusted_b = b / divisor;
  } else {
    adjusted_a = 0;
    adjusted_b = 1;
  }
  // Initialise the rational number
  rational return_pointer = calloc(1, sizeof(struct rational_internal));
  return_pointer->sign = sign;
  return_pointer->a = adjusted_a;
  return_pointer->b = adjusted_b;
  // Return the rational pointer
  return return_pointer;
}

// A function to change the sign of a rational number
bool change_sign_rational(rational to_change) {
  if (to_change == NULL) {
    fprintf(stderr, "Passed NULL pointer");
    return false;
  }
  // Just change the sign with the not operator
  to_change->sign = !(to_change->sign);
  return true;
}

// Function to get the inverse of a rational
rational get_inverse(rational to_invert) {
  if (to_invert == NULL) {
    fprintf(stderr, "Passed NULL pointer");
    return NULL;
  }
  // Check if the rational is 0, and return an error if so
  if (to_invert->a == 0) {
    fprintf(stderr, "Cannot invert 0");
    exit(EXIT_FAILURE);
  }
  // Return a pointer the inverse of the rational
  return init_rational(to_invert->sign, to_invert->b, to_invert->a);
}

// A function to add two rational numbers together
rational add_rational(rational a, rational b) {
  if (a == NULL || b == NULL) {
    fprintf(stderr, "Passed NULL pointer");
    return NULL;
  }
  // Initialise all the needed variables
  bool new_sign;
  unsigned long new_a_val;
  unsigned long new_b_val = a->b * b->b;
  // The addition will change depending on the signs of the numbers
  if (a->sign && b->sign) {
    // If both are positive, just add them like fractions
    new_a_val = a->a * b->b + b->a * a->b;
    new_sign = true;
  } else if (a->sign) {
    // If a is positive but b negative
    if (a->a * b->b >= b->a * a->b) {
      // If a is bigger just subtract b
      new_a_val = a->a * b->b - b->a * a->b;
      new_sign = true;
    } else {
      // If a is smaller find the absolute difference
      // and then make the sign negative
      new_a_val = b->a * a->b - a->a * b->b;
      new_sign = false;
    }
  } else if (b->sign) {
    // If b is postive but a negative
    if (a->a * b->b <= b->a * a->b) {
      // If b is bigger, subract a from it
      new_a_val = b->a * a->b - a->a * b->b;
      new_sign = true;
    } else {
      // If a is bigger, find the absolute difference
      // and make the sign negative
      new_a_val = a->a * b->b - b->a * a->b;
      new_sign = false;
    }
  } else {
    // If they are both negative, just add them and
    // make the sign negative
    new_a_val = a->a * b->b + b->a * a->b;
    new_sign = false;
  }
  // Return by value the a rational with the new values
  return init_rational(new_sign, new_a_val, new_b_val);
}

// A function to multiply a rational number by an interger
rational int_mult_rational(int scalar, rational rational_num) {
  if (rational_num == NULL) {
    fprintf(stderr, "Passed NULL pointer");
    return NULL;
  }
  // Initialise an empty variable to take the scalar value
  rational temp;
  // Check whether the scalar value is positive or negative
  // and give the correct sign in each case
  if (scalar >= 0) {
    temp = init_rational(true, (unsigned long)scalar, (unsigned long)1);
  } else {
    temp = init_rational(false, (unsigned long)abs(scalar), (unsigned long)1);
  }
  // Now just use the rational multiplier to do the work
  return mult_rational(temp, rational_num);
}

// A function to multiply two rational numbers
rational mult_rational(rational a, rational b) {
  if (a == NULL || b == NULL) {
    fprintf(stderr, "Passed NULL pointer");
    return NULL;
  }
  // Just multiply the numerators and the denomenators by each other
  unsigned long new_a_val = a->a * b->a;
  unsigned long new_b_val = a->b * b->b;
  // Get the new sign by the rules of multiplication
  // ie -1 * -1 = 1, -1 * 1 = -1, 1 * 1 = 1
  bool new_sign = !((!b->sign) && a->sign) && !((!a->sign) && b->sign);
  // Return an new initialised rational number
  return init_rational(new_sign, new_a_val, new_b_val);
}

// A function to print out a rational number
bool print_rational(rational num) {
  if (num == NULL) {
    fprintf(stderr, "Passed NULL pointer");
    return false;
  }
  // This bit is to allow dropping the /1 for integer
  char str[256];
  sprintf(str, "/%lu", num->b);
  // Print out the number like a/b
  printf("%s%lu%s", (num->sign) ? "" : "-", num->a, (num->b == 1) ? "" : str);
  return true;
}

bool destroy_rational(rational to_destroy) {
  if (to_destroy == NULL) {
    fprintf(stderr, "Passed NULL pointer");
    return false;
  }
  free(to_destroy);
  return true;
}
