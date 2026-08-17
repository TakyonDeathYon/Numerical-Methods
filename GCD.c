#include <stdio.h>

unsigned long calc_gcd(unsigned long a, unsigned long b) {
  unsigned long ajmin1 = (a > b) ? a : b;
  unsigned long aj = (a > b) ? b : a;
  if (aj == 0) {
    fprintf(stderr, "Error: Tried to divide by 0 in GCD");
    return 0;
  }
tco:
  if (aj == ajmin1) {
    return aj;
  }
  unsigned long rj = ajmin1 % aj;
  if (rj == 0) {
    return aj;
  }
  ajmin1 = aj;
  aj = rj;
  goto tco;
}
