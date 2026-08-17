// A function to calculate the gcd of two numbers using Euclid's algorithm
unsigned long calc_gcd(unsigned long a, unsigned long b) {
  // Initialise the variables with the biggest as ajmin1
  unsigned long ajmin1 = (a > b) ? a : b;
  unsigned long aj = (a > b) ? b : a;
  // If there is a 0, then just return 0 as the default
  if (aj == 0) {
    return 0;
  }
  // Using tags to imitate tail call optimisation
tco:
  // If the values are the same, then the number itself is the GCD
  if (aj == ajmin1) {
    return aj;
  }
  // Find the remainder of the division
  unsigned long rj = ajmin1 % aj;
  // If the remainder is 0, return the divisor
  if (rj == 0) {
    return aj;
  }
  // Change values to new ones
  ajmin1 = aj;
  aj = rj;
  // Go back to top and do again
  goto tco;
}
