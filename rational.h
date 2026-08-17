#ifndef RATIONAL_H
#define RATIONAL_H

#include "rational_struct.h"

struct rational init_rational(bool, unsigned long, unsigned long);

void change_sign_rational(struct rational *);

struct rational mult_rational(struct rational, struct rational);

struct rational add_rational(struct rational, struct rational);

struct rational int_mult_rational(int, struct rational);

void print_rational(struct rational);

#endif // !RATIONAL_H
