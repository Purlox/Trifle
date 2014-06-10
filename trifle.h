#ifndef TRIFLE_H_INCLUDED
#define TRIFLE_H_INCLUDED

#include <stdbool.h>

/* Compares two floats if they are /likely/ the same number.
 * - You shouldn't be comparing floats with =, because they are approximations
 *     to real numbers, so they might print the same number on the screen, but
 *     might not actually be exactly equal under the hood causing the = return
 *     false.
 * - Use modifiers like 0.95 (less than 1) with the COMPARE_FLOATS macro. The
 *     other macro has a constant modifier.
 * - Generic version with C11 works only if you define SUPPORTS_GENERIC because
 *     some compilers still don't support _Generic.
 */
#if defined(SUPPORTS_GENERIC)

#define COMPARE_FLOATS( float1, float2, modifier )   \
  _Generic((float1), float:       compare_floats_f,  \
                     double:      compare_floats_d,  \
                     long double: compare_floats_ld, \
                     default: WRONG_TYPE)(float1, float2, modifier)

static inline bool
compare_floats_f(float float1,
                 float float2,
                 float modifier)
{
  return ((float1 * modifier < float2) && (float2 * modifier < float1));
}

static inline bool
compare_floats_d(double float1,
                 double float2,
                 double modifier)
{
  return ((float1 * modifier < float2) && (float2 * modifier < float1));
}

static inline bool
compare_floats_ld(long double float1,
                  long double float2,
                  long double modifier)
{
  return ((float1 * modifier < float2) && (float2 * modifier < float1));
}

#define COMPARE_FLOATS_CONST_MOD( float1, float2 )   \
  _Generic((float1), float:       compare_floats_f,  \
                     double:      compare_floats_d,  \
                     long double: compare_floats_ld, \
                     default: WRONG_TYPE)            \
                     (float1, float2, ADD_SUFFIX(float2, 0.999)

#define WRONG_TYPE( ... ) \
  _const_assert(true, "Wrong type(s) supplied to COMPARE_FLOATS(_CONST_MOD)");

#else /* defined(SUPPORTS_GENERIC) */

#define COMPARE_FLOATS( float1, float2, modifier ) \
  ( (float1) * modifier < (float2) && (float2) * modifier < (float1) )

#define COMPARE_FLOATS_CONST_MOD( float1, float2 ) \
  ( (float1) * 0.999 < (float2) && (float2) * 0.999 < (float1) )

#endif /* defined(SUPPORTS_GENERIC) */


/* Adds the appropriate literal suffix to number2 (which should be a literal),
 *     based on the type of number1, which should be a variable.
 * - Aimed to be used with other Generic macros, where number1 is a variable
 *     passed into the macro and number2 is a literal that needs to be of the
 *     appropriate type depending on the type of number1.
 */
#define ADD_SUFFIX( number1, number2 )                    \
  _Generic((number1), float:              number2 ## f,   \
                      double:             number2,        \
                      long double:        number2 ## L,   \
                      short:              number2,        \
                      unsigned short:     number2 ## u,   \
                      int:                number2,        \
                      unsigned int:       number2 ## u,   \
                      long:               number2 ## L,   \
                      unsigned long:      number2 ## uL,  \
                      long long:          number2 ## LL,  \
                      unsigned long long: number2 ## uLL, \
                      default:            number2)

#endif /* TRIFLE_H_INCLUDED */
