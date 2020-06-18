/*
	File:		fp.h

	Contains:	Portable SANE

	Written by:	Ali Sazegari et al

	Copyright:	� 1993,95 by Apple Computer, Inc., all rights reserved.
*/

/*******************************************************************************
*                                                                              *
*      File fp.h,- Newton C++ Tools version                                    *
*                                                                              *
*      A collection of numerical functions designed to facilitate a wide       *
*      range of numerical programming. It is modeled after the Numerical       *
*      C Extensions Group's requirements ( NCEG / X3J11.1 ).                   *
*      The <fp.h> declares many functions in support of numerical programming. *
*      It provides a superset of <math.h> and <sane.h> functions.  Some        *
*      functionality previously found in <sane.h> can be found in <fenv.h>     *
*      and <faux.h>                                                            *
*                                                                              *
*      All of these functions are IEEE 754 aware and treat exceptions, NaNs,   *
*      positive and negative zero and infinity consistent with the floating    *
*      point standard.                                                         *
*                                                                              *
*      Copyright � 1992 Apple Computer, Inc.  All rights reserved.             *
*                                                                              *
*      Written by Ali Sazegari, started on July 1992,                          *
*      based on the file Numerics.h by Jim Thomas.                             *
*                                                                              *
*      Adapted for Newton C++ Tools by John Arkley 1995                        *
*      Generally removing everything related to Extended as Newton has only    *
*	   float and double support                                                *
*******************************************************************************/

#ifndef __FP_H
#define __FP_H

/*      efficient types are included in Types.h.                              */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
*                 CUSTOM DEFINITIONS THAT SHOULD BE IN TYPES.H.                *
*******************************************************************************/
#ifdef forARM
typedef double double_t;
#undef sin
#undef cos
#undef tan
#undef acos
#undef asin
#undef atan
#undef atan2
#undef cosh
#undef sinh
#undef tanh
#undef exp
#undef frexp
#undef ldexp
#undef log
#undef log10
#undef modf
#undef pow
#undef sqrt
#undef ceil
#undef fabs
#undef floor
#undef fmod
#endif

/*******************************************************************************
* 	Macros to access long subfields of a double value.				 *
*******************************************************************************/
#define highpartd(x) *((long *) &x)
#define lowpartd(x)  *((long *) &x + 1)

/*******************************************************************************
*                              Define some constants.                          *
*******************************************************************************/


#define      DOUBLE_SIZE                  8

#define      HUGE_VAL                  __inf()
#define      INFINITY                  __inf()
#define      NAN                        nan("255")

/*    the macro DECIMAL_DIG is obtained by satisfying the constraint that the
      conversion from double to decimal and back is the identity function.   */

#define      DECIMAL_DIG                  21

/*******************************************************************************
*                            Trigonometric functions                           *
*******************************************************************************/

double_t cos ( double_t x );
double_t sin ( double_t x );
double_t tan ( double_t x );

double_t acos ( double_t x );            /*  argument x is in [0,pi]          */
double_t asin ( double_t x );            /*  argument x is in [-pi/2,pi/2]    */
double_t atan ( double_t x );            /*  argument x is in [-pi/2,pi/2]    */


/*    atan2 computes the arc tangent of y/x in [-pi,pi] using the sign of
      both arguments to determine the quadrant of the computed value.         */

double_t atan2 ( double_t y, double_t x );


/*******************************************************************************
*                              Hyperbolic functions                            *
*******************************************************************************/

double_t cosh ( double_t x );
double_t sinh ( double_t x );
double_t tanh ( double_t x );

double_t acosh ( double_t x );
double_t asinh ( double_t x );
double_t atanh ( double_t x );


/*******************************************************************************
*                              Exponential functions                           *
*******************************************************************************/

double_t exp ( double_t x );


/*    expm1 computes the base e exponential of the argument minus 1,
      i. e., exp(x) - 1.  For small enough arguments, expm1 is expected
      to be more accurate than the straight forward computation of exp(x) - 1.*/

double_t expm1  ( double_t x );

/*      exp2 computes the base 2 exponential.                                 */

double_t exp2  ( double_t x );

double_t frexp ( double_t x, int *exponent );
double_t ldexp ( double_t x, int n );

double_t log ( double_t x );


/*      log2 computes the base 2 logarithm.                                   */

double_t log2 ( double_t x );

/*    log1p computes the base e logorithm of 1 plus the argument,
      i. e., log (1 x).  For small enough arguments, log1p is expected
      to be more accurate than the straightforward computation of log (1+x).  */

double_t log1p ( double_t x );
double_t log10 ( double_t x );


/*      logb extracts the exponent of its argument, as a signed integral
      value. A subnormal argument is treated as though it were first
      normalized. Thus

      1 <= x * 2^( - Logb ( x ) ) < 2                                         */

double_t logb ( double_t x );

// NOT AVAILABLE IN NEWTON 
// long double modfl ( long double x, long double *iptrl );
#define modfl( x,y)  (?? modfl is not available on newton)
double      modf  ( double x, double *iptr );
float       modff ( float x, float *iptrf );

/*    scalb computes x * 2^n efficently.  This is not normally done by
      computing 2^n explicitly.                                               */

double_t scalb ( double_t x, long int n );

/*******************************************************************************
*                     Power and absolute value functions                       *
*******************************************************************************/

double_t fabs ( double_t x );

/*    hypot computes the square root of the sum of the squares of its
      arguments, without undue overflow or underflow.                         */

double_t hypot ( double_t x, double_t y );
double_t pow   ( double_t x, double_t y );
double_t sqrt  ( double_t x );


/*******************************************************************************
*                        Gamma and Error functions                             *
*******************************************************************************/

double_t erf  ( double_t x );            /*   the error function              */
double_t erfc ( double_t x );            /*   complementary error function    */

double_t gamma ( double_t x );

/*    lgamma computes the base-e logarithm of the absolute value of
      gamma of its argument x, for x > 0.                                     */

double_t lgamma ( double_t x );

/*******************************************************************************
*                        Nearest integer functions                             *
*******************************************************************************/

double_t ceil  ( double_t x );
double_t floor ( double_t x );

/*    the rint function rounds its argument to an integral value in floating
      point format, honoring the current rounding direction.                  */

double_t rint ( double_t x );

/*    nearbyint differs from rint only in that it does not raise the
      inexact exception. It is the nearbyint function recommended by the
      IEEE floating-point standard 854.                                       */

double_t nearbyint ( double_t x );

/*    the function rinttol rounds its argument to the nearest long int using
      the current rounding direction.
      >>Note that if the rounded value is outside the range of long int, then
      the result is undefined.                                                */

long int rinttol ( double_t x );

/*    the round function rounds the argument to the nearest integral value
      in double format similar to the Fortran "anint" function.  That is:
      add half to the magnitude and chop.                                     */

double_t round ( double_t x );

/*    roundtol is similar to the Fortran function nint or to the Pascal round
      >>Note that if the rounded value is outside the range of long int, then
      the result is undefined.                                                */

long int roundtol ( double_t round );

/*    trunc computes the integral value, in floating format, nearest to
      but no larger in magnitude than its argument.                           */

double_t trunc ( double_t x );

/*******************************************************************************
*                            Remainder functions                               *
*******************************************************************************/

double_t fmod ( double_t x, double_t y );

/*    the following two functions compute the remainder.  remainder is required
      by the IEEE 754 floating point standard. The second form correponds to the
      SANE remainder; it stores into 'quotient' the 7 low-order bits of the
      integer quotient x/y, such that -127 <= quotient <= 127.                */

double_t remainder ( double_t x, double_t y );
double_t remquo    ( double_t x, double_t y, int *quo );

/*******************************************************************************
*                             Auxiliary functions                              *
*******************************************************************************/

/*    copysign produces a value with the magnitude of its first argument
      and sign of its second argument. NOTE: the order of the arguments
      matches the recommendation of the IEEE 754 floating point standard,
      which is opposite from the SANE copysign function.                      */

double_t copysign ( double_t x, double_t y );

/*    the call 'nan ( "n-char-sequence" )' returns a quiet NaN with content
      indicated through tagp in the selected data type format.                */

// long double nanl ( const char *tagp );
double      nan  ( const char *tagp );
float       nanf ( const char *tagp );

/*    these compute the next representable value, in the type indicated,
      after 'x' in the direction of 'y'.  if x == y then y is returned.       */

// long double nextafterl ( long double x, long double y );
double      nextafterd ( double x, double y );
float       nextafterf ( float x, float y );

/*******************************************************************************
*                              Inquiry macros                                  *
*******************************************************************************/
// JTC: collapse FP_SNAN and FP_QNAN into FP_NAN as per nceg.
// Temporarily SNAN be bogus -- but check whether there's ever a distinction.

enum NumberKind
            {
            FP_NAN = 0,         /*      NaN                 	              */
            FP_INFINITE,        /*      + or - infinity                       */
            FP_ZERO,            /*      + or - zero                           */
            FP_NORMAL,          /*      all normal numbers                    */
            FP_SUBNORMAL        /*      denormal numbers                      */
            };
			
#define FP_SNAN FP_NAN
#define FP_QNAN FP_NAN

#define      fpclassify(x)    ( ( sizeof ( x ) == DOUBLE_SIZE ) ?              \
                              __fpclassifyd ( x ) :                            \
                              __fpclassifyf ( x ) )

/*    isnormal is non-zero if and only if the argument x is normalized.       */

#define      isnormal(x)      ( ( sizeof ( x ) == DOUBLE_SIZE ) ?              \
                              __isnormald ( x ) :                              \
                              __isnormalf ( x ) )

/*    isfinite is non-zero if and only if the argument x is finite.           */

#define      isfinite(x)      (( sizeof ( x ) == DOUBLE_SIZE ) ?              \
                              __isfinited ( x ) :                             \
                              __isfinitef ( x ) )

/*    isnan is non-zero if and only if the argument x is a NaN.               */

#define      isnan(x)         ( ( sizeof ( x ) == DOUBLE_SIZE ) ?               \
                              __isnand ( x ) :                                 \
                              __isnanf ( x ) )

/*    signbit is non-zero if and only if the sign of the argument x is
      negative. this includes, NaNs, infinities and zeros.                    */

#define      signbit(x)       ( ( sizeof ( x ) == DOUBLE_SIZE ) ?               \
                              __signbitd ( x ) :                               \
                              __signbitf ( x ) )

/*******************************************************************************
*                      Max, Min and Positive Difference                        *
*******************************************************************************/

/*    These extension functions correspond to the standard functions, dim
      max and min.

      The fdim function determines the 'positive difference' between its
      arguments: { x - y, if x > y }, { +0, if x <= y }.  If one argument is
      NaN, then fdim returns that NaN.  if both arguments are NaNs, then fdim
      returns the first argument.                                             */

double_t fdim ( double_t x, double_t y );

/*     max and min return the maximum and minimum of their two arguments,
      respectively.  They correspond to the max and min functions in FORTRAN.
      NaN arguments are treated as missing data.  If one argument is NaN and
      the other is a number, then the number is returned.  If both are NaNs
      then the first argument is returned.                                    */

double_t fmax ( double_t x, double_t y );
double_t fmin ( double_t x, double_t y );

/*******************************************************************************
*                                Constants                                     *
*******************************************************************************/

extern const double_t pi;

/*******************************************************************************
*                              Internal prototypes                             *
*******************************************************************************/
// nceg dictates type int, not long int for these.

int __fpclassify  ( long double x );
int __fpclassifyd ( double x );
int __fpclassifyf ( float x );

int __isnormal  ( long double x );
int __isnormald ( double x );
int __isnormalf ( float x );

int __isfinite  ( long double x );
int __isfinited ( double x );
int __isfinitef ( float x );

int __isnan  ( long double x );
int __isnand ( double x );
int __isnanf ( float x );

int __signbit  ( long double x );
int __signbitd ( double x );
int __signbitf ( float x );

double __inf ( void );

/*******************************************************************************
*                              Non NCEG extensions                             *
*******************************************************************************/

#ifndef __NOEXTENSIONS__

/*******************************************************************************
*                              Financial functions                             *
*******************************************************************************/

/*    compound computes the compound interest factor "(1 + rate) ^ periods"
      more accurately than the straightforward computation with the Power
      function.  This is SANE's compound function.                            */

double_t compound ( double_t rate, double_t periods );

/*      The function annuity computes the present value factor for an annuity
      "( 1 - ( 1 + rate ) ^ ( - periods ) ) / rate" more accurately than the
      straightforward computation with the Power function. This is SANE's
      annuity function.                                                       */

double_t annuity ( double_t rate, double_t periods );

/*******************************************************************************
*                              Random function                                 *
*******************************************************************************/

double_t randomx ( double_t *x );

/*******************************************************************************
*                              Relational operator                             *
*******************************************************************************/

typedef short relop;                         /*      relational operator      */

enum
      {
      GREATERTHAN = ( ( relop ) ( 0 ) ),
      LESSTHAN,
      EQUALTO,
      UNORDERED
      };

relop relation ( double_t x, double_t y );


#endif      /* __NOEXTENSIONS__ */

#ifdef __cplusplus
}
#endif

#endif
