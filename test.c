#include <stdio.h>
#include "trifle.h"

int main() {
  static float x = 9.9;
  float var = 3.3;

  printf("9.9 == 3.3 * 3:   %i - %i\n", COMPARE_FLOATS(x, var * 3, 0.999), x == (var * 3));
  printf("142.34 == 142.3:  %i - %i\n", COMPARE_FLOATS(142.34, 142.3, 0.9999), 142.34 == 142.3);

  return 0;
}
