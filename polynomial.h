#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include "rational.h"

typedef struct polynomial_internal *polynomial;

polynomial init_polynomial(unsigned int, rational *);

polynomial add_polynomial(polynomial, polynomial);

polynomial mult_polynomial(polynomial, polynomial);

bool print_polynomial(polynomial);

bool destroy_polynomial(polynomial);

#endif // !POLYNOMIAL_H
