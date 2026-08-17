#include "polynomial.h"

struct polynomial_internal {
  unsigned int degree;
  struct rational *coefficients;
};

polynomial *init_polynomial(unsigned int degree,
                            struct rational *coefficients) {
  polynomial *_temp;
  return _temp;
}
