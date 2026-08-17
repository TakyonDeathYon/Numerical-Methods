#include "polynomial.h"
#include "rational.h"
#include <stdlib.h>
#include <string.h>

struct polynomial_internal {
  unsigned int degree;
  rational *coefficients;
};

polynomial init_polynomial(unsigned int degree, rational *coefficients) {
  polynomial _temp;
  _temp->degree = degree;
  _temp->coefficients = calloc((size_t)degree, sizeof(rational));
  memcpy(_temp->coefficients, coefficients,
         (sizeof(rational) * (size_t)degree));
  return _temp;
}
