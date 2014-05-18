#ifndef TRIFLE_H_INCLUDED
#define TRIFLE_H_INCLUDED

/* Compares two floats if they are /likely/ the same number.
 * Floats are approximations to real numbers anyway, so you should never
 *   compare them for exact equality with =, as they can be numbers that might
 *   print the same number on the screen, but might not actually be exactly
 *   equal under the hood.
 * Use percentages like 0.95 with the first macro.
 * I decided to use percantages that make the float smaller to prevent
 *   potential overflows.
 */
#  if defined __STDC_VERSION__ == 201112L

#define COMPARE_FLOATS( float1, float2, percentage ) \
  _Generic((float1), float: REAL_COMPARE_FLOATS, \
                     double: REAL_COMPARE_FLOATS, \
                     long double: REAL_COMPARE_FLOATS, \
                     default: WRONG_TYPE)(float1, float2, percentage)
#define REAL_COMPARE_FLOATS( float1, float2, percentage ) \
  ( (float1) * percentage < (float2) && (float2) * percentage < (float1) )

#define COMPARE_FLOATS_WITH_SET_PERCENTAGE( float1, float2 ) \
  _Generic((float1), float: COMPARE_FLOATS_WITH_SET_PERCENTAGE_f, \
                     double: COMPARE_FLOATS_WITH_SET_PERCENTAGE_d, \
                     long double: COMPARE_FLOATS_WITH_SET_PERCENTAGE_ld, \
                     default: WRONG_TYPE)(float1, float2)

#define COMPARE_FLOATS_WITH_SET_PERCENTAGE_f( float1, float2 ) \
  ( (float1) * 0.999f < (float2) && (float2) * 0.999f < (float1) )
#define COMPARE_FLOATS_WITH_SET_PERCENTAGE_f( float1, float2 ) \
  ( (float1) * 0.999 < (float2) && (float2) * 0.999 < (float1) )
#define COMPARE_FLOATS_WITH_SET_PERCENTAGE_f( float1, float2 ) \
  ( (float1) * 0.999L < (float2) && (float2) * 0.999L < (float1) )

#define WRONG_TYPE( float1, float2 ) \
  _Static_assert(1, "Wrong type(s) supplied to COMPARE_FLOATS");

#  else

#define COMPARE_FLOATS( float1, float2, percentage ) \
  ( (float1) * percentage < (float2) && (float2) * percentage < (float1) )

#define COMPARE_FLOATS_WITH_SET_PERCENTAGE( float1, float2 ) \
  ( (float1) * 0.999 < (float2) && (float2) * 0.999 < (float1) )

#  endif

#endif // TRIFLE_H_INCLUDED
