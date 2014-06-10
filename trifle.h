#ifndef TRIFLE_H_INCLUDED
#define TRIFLE_H_INCLUDED

#include <stdbool.h>

/* Compares two floats if they are /likely/ the same number.
 * Floats are approximations to real numbers anyway, so you should never
 *   compare them for exact equality with =, as they can be numbers that might
 *   print the same number on the screen, but might not actually be exactly
 *   equal under the hood.
 * Use modifiers like 0.95 with the COMPARE_FLOATS macro. The other one has a
 *   const modifier, that should be good enough for general cases.
 * I decided to use percantages that make the float smaller to prevent
 *   potential overflows.
 * Generic version with C11 works only if you define SUPPORTS_GENERIC because
 *   some compilers still don't support _Generic.
 */
# if defined(__STDC__)
#  if defined(__STDC_VERSION__) && (__STDC_VERSION__ == 201112L) /* C11 */

#   if defined(SUPPORTS_GENERIC)

#define COMPARE_FLOATS( float1, float2, modifier ) \
  _Generic((float1), float: compare_floats_f, \
                     double: compare_floats_d, \
                     long double: compare_floats_ld, \
                     default: WRONG_TYPE)(float1, float2, modifier)

bool compare_floats_f(float float1, float float2, float modifier) {
  return ((float1 * modifier < float2) && (float2 * modifier < float1));
}

bool compare_floats_d(double float1, double float2, double modifier) {
  return ((float1 * modifier < float2) && (float2 * modifier < float1));
}

bool compare_floats_ld(long double float1, long double float2, long double modifier) {
  return ((float1 * modifier < float2) && (float2 * modifier < float1));
}

#define COMPARE_FLOATS_CONST_MOD( float1, float2 ) \
  _Generic((float1), float: compare_floats_f, \
                     double: compare_floats_d, \
                     long double: compare_floats_ld, \
                     default: WRONG_TYPE)(float1, float2, 0.999L)

#define WRONG_TYPE( float1, float2 ) \
  _const_assert(true, "Wrong type(s) supplied to COMPARE_FLOATS");

#   else /* defined(SUPPORTS_GENERIC) */

#define COMPARE_FLOATS( float1, float2, modifier ) \
  ( (float1) * modifier < (float2) && (float2) * modifier < (float1) )

#define COMPARE_FLOATS_CONST_MOD( float1, float2 ) \
  ( (float1) * 0.999 < (float2) && (float2) * 0.999 < (float1) )

#   endif /* defined(SUPPORTS_GENERIC) */

#  else /* isn't C11 */

#define COMPARE_FLOATS( float1, float2, modifier ) \
  ( (float1) * modifier < (float2) && (float2) * modifier < (float1) )

#define COMPARE_FLOATS_CONST_MOD( float1, float2 ) \
  ( (float1) * 0.999 < (float2) && (float2) * 0.999 < (float1) )

#  endif /* C11 */
# endif /* defined(__STDC__) */

#endif /* TRIFLE_H_INCLUDED */
