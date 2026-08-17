#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include "rational.h"

typedef struct polynomial_internal *polynomial;

polynomial init_polynomial(unsigned int, rational *);

#endif // !POLYNOMIAL_H
