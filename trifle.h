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
#define COMPARE_FLOATS( float1, float2, percantage ) \
  ( (float1) * percentage < (float2) && (float2) * percentage < (float1) )

#define _COMPARE_FLOATS( float1, float2 ) \
  ( (float1) * 0.98 < (float2) && (float2) * 0.98 < (float1) )


#endif // TRIFLE_H_INCLUDED
