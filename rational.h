#ifndef RATIONAL_H
#define RATIONAL_H
#include <stdbool.h>

typedef struct rational_internal *rational;

rational init_rational(bool, unsigned long, unsigned long);

bool change_sign_rational(rational);

rational mult_rational(rational, rational);

rational add_rational(rational, rational);

rational int_mult_rational(int, rational);

bool print_rational(rational);

bool destroy_rational(rational);

#endif // !RATIONAL_H
