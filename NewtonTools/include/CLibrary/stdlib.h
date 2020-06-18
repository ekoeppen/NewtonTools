/*
	File:		stdlib.h

	Contains:	C++ Tools subset of stdlib.h

	Written by:	Newton Tools Team

	Copyright:	� 1993 - 1995 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	 <1>	06/23/95	Removed functions not present in Newton 2.0

*/
#pragma force_top_level
#pragma include_only_once

/* stdlib.h: ANSI draft (X3J11 May 88) library header, section 4.10 */
/* Copyright (C) Codemist Ltd., 1988                            */
/* Copyright (C) Advanced Risc Machines Ltd., 1991              */

/*
 * stdlib.h declares four types, several general purpose functions,
 * and defines several macros.
 */

#ifndef __STDLIB_H
#define __STDLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __size_t
#  define __size_t 1
   typedef unsigned int size_t;   /* from <stddef.h> */
#endif

#ifndef __wchar_t
#define __wchar_t 1
#if !defined(__cplusplus)
   typedef int wchar_t;           /* from <stddef.h> */
#endif
#endif

#ifndef NULL
#  define NULL 0                  /* from <stddef.h> */
#endif

typedef struct div_t { int quot, rem; } div_t;
   /* type of the value returned by the div function. */
typedef struct ldiv_t { long int quot, rem; } ldiv_t;
   /* type of the value returned by the ldiv function. */

#ifdef __EXIT_FAILURE
#  define EXIT_FAILURE __EXIT_FAILURE
   /*
    * an integral expression which may be used as an argument to the exit
    * function to return unsuccessful termination status to the host
    * environment.
    */
#else
#  define EXIT_FAILURE 1  /* unixoid */
#endif
#define EXIT_SUCCESS 0
   /*
    * an integral expression which may be used as an argument to the exit
    * function to return successful termination status to the host
    * environment.
    */

#define RAND_MAX 0x7fffffff
   /*
    * an integral constant expression, the value of which is the maximum value
    * returned by the rand function.
    */
#define _ANSI_RAND_MAX 0x7fff /* for the so-called portable version rand() */
   /*
    * an integral constant expression, the value of which is the maximum value
    * returned by the _ANSI_rand function.
    */
#define MB_CUR_MAX 1
   /*
    * a positive integer expression whose value is the maximum number of bytes
    * in a multibyte character for the extended character set specified by the
    * current locale (category LC_CTYPE), and whose value is never greater
    * than MB_LEN_MAX.
    */

extern double atof(const char * /*nptr*/);
   /*
    * converts the initial part of the string pointed to by nptr to double
    * representation.
    * Returns: the converted value.
    */
extern int atoi(const char * /*nptr*/);
   /*
    * converts the initial part of the string pointed to by nptr to int
    * representation.
    * Returns: the converted value.
    */
extern long int atol(const char * /*nptr*/);
   /*
    * converts the initial part of the string pointed to by nptr to long int
    * representation.
    * Returns: the converted value.
    */

extern double strtod(const char * /*nptr*/, char ** /*endptr*/);
   /*
    * converts the initial part of the string pointed to by nptr to double
    * representation. First it decomposes the input string into three parts:
    * an initial, possibly empty, sequence of white-space characters (as
    * specified by the isspace function), a subject sequence resembling a
    * floating point constant; and a final string of one or more unrecognised
    * characters, including the terminating null character of the input string.
    * Then it attempts to convert the subject sequence to a floating point
    * number, and returns the result. A pointer to the final string is stored
    * in the object pointed to by endptr, provided that endptr is not a null
    * pointer.
    * Returns: the converted value if any. If no conversion could be performed,
    *          zero is returned. If the correct value is outside the range of
    *          representable values, plus or minus HUGE_VAL is returned
    *          (according to the sign of the value), and the value of the macro
    *          ERANGE is stored in errno. If the correct value would cause
    *          underflow, zero is returned and the value of the macro ERANGE is
    *          stored in errno.
    */
extern long int strtol(const char * /*nptr*/, char **/*endptr*/, int /*base*/);
   /*
    * converts the initial part of the string pointed to by nptr to long int
    * representation. First it decomposes the input string into three parts:
    * an initial, possibly empty, sequence of white-space characters (as
    * specified by the isspace function), a subject sequence resembling an
    * integer represented in some radix determined by the value of base, and a
    * final string of one or more unrecognised characters, including the
    * terminating null character of the input string. Then it attempts to
    * convert the subject sequence to an integer, and returns the result.
    * If the value of base is 0, the expected form of the subject sequence is
    * that of an integer constant (described in ANSI Draft, section 3.1.3.2),
    * optionally preceeded by a '+' or '-' sign, but not including an integer
    * suffix. If the value of base is between 2 and 36, the expected form of
    * the subject sequence is a sequence of letters and digits representing an
    * integer with the radix specified by base, optionally preceeded by a plus
    * or minus sign, but not including an integer suffix. The letters from a
    * (or A) through z (or Z) are ascribed the values 10 to 35; only letters
    * whose ascribed values are less than that of the base are permitted. If
    * the value of base is 16, the characters 0x or 0X may optionally precede
    * the sequence of letters and digits following the sign if present.
    * A pointer to the final string is stored in the object
    * pointed to by endptr, provided that endptr is not a null pointer.
    * Returns: the converted value if any. If no conversion could be performed,
    *          zero is returned. If the correct value is outside the range of
    *          representable values, LONG_MAX or LONG_MIN is returned
    *          (according to the sign of the value), and the value of the
    *          macro ERANGE is stored in errno.
    */
extern unsigned long int strtoul(const char * /*nptr*/,
                                       char ** /*endptr*/, int /*base*/);
   /*
    * converts the initial part of the string pointed to by nptr to unsigned
    * long int representation. First it decomposes the input string into three
    * parts: an initial, possibly empty, sequence of white-space characters (as
    * determined by the isspace function), a subject sequence resembling an
    * unsigned integer represented in some radix determined by the value of
    * base, and a final string of one or more unrecognised characters,
    * including the terminating null character of the input string. Then it
    * attempts to convert the subject sequence to an unsigned integer, and
    * returns the result. If the value of base is zero, the expected form of
    * the subject sequence is that of an integer constant (described in ANSI
    * Draft, section 3.1.3.2), optionally preceeded by a '+' or '-' sign, but
    * not including an integer suffix. If the value of base is between 2 and
    * 36, the expected form of the subject sequence is a sequence of letters
    * and digits representing an integer with the radix specified by base,
    * optionally preceeded by a '+' or '-' sign, but not including an integer
    * suffix. The letters from a (or A) through z (or Z) stand for the values
    * 10 to 35; only letters whose ascribed values are less than that of the
    * base are permitted. If the value of base is 16, the characters 0x or 0X
    * may optionally precede the sequence of letters and digits following the
    * sign, if present. A pointer to the final string is stored in the object
    * pointed to by endptr, provided that endptr is not a null pointer.
    * Returns: the converted value if any. If no conversion could be performed,
    *          zero is returned. If the correct value is outside the range of
    *          representable values, ULONG_MAX is returned, and the value of the    *          macro ERANGE is stored in errno.
    */

extern int rand(void);
   /*
    * Computes a sequence of pseudo-random integers in the range 0 to RAND_MAX.
    * Uses an additive generator (Mitchell & Moore) of the form:
    *   Xn = (X[n-24] + X[n-55]) MOD 2^31
    * This is described in section 3.2.2 of Knuth, vol 2. It's period is
    * in excess of 2^55 and its randomness properties, though unproven, are
    * conjectured to be good. Empirical testing since 1958 has shown no flaws.
    * Returns: a pseudo-random integer.
    */
extern void srand(unsigned int /*seed*/);
   /*
    * uses its argument as a seed for a new sequence of pseudo-random numbers
    * to be returned by subsequent calls to rand. If srand is then called with
    * the same seed value, the sequence of pseudo-random numbers is repeated.
    * If rand is called before any calls to srand have been made, the same
    * sequence is generated as when srand is first called with a seed value
    * of 1.
    */
extern int _ANSI_rand(void);
   /*
    * The ANSI-defined 16-bit random number generator which computes
    * a sequence of pseudo-random integers in the range 0 to _ANSI_RAND_MAX.
    * Its properties are poor, though it IS very portable.
    * *** NOT AVAILABLE IN THE SHARED C LIBRARY ***
    * Returns: a pseudo-random integer.
    */
extern void _ANSI_srand(unsigned int /*seed*/);
   /*
    * Uses its argument as a seed for a new sequence of pseudo-random numbers
    * to be returned by subsequent calls to _ANSI_rand. If _ANSI_srand is then
    * called with the same seed value, the sequence of pseudo-random numbers
    * is repeated. If _ANSI_rand is called before any calls to _ANSI_srand have
    * been made, the same sequence is generated as when _ANSI_srand is first
    * called with a seed value of 1.
    * *** NOT AVAILABLE IN THE SHARED C LIBRARY ***
    */

extern void *calloc(size_t /*nmemb*/, size_t /*size*/);
   /*
    * allocates space for an array of nmemb objects, each of whose size is
    * 'size'. The space is initialised to all bits zero.
    * Returns: either a null pointer or a pointer to the allocated space.
    */

extern void free(void * /*ptr*/);
   /*
    * causes the space pointed to by ptr to be deallocated (i.e., made
    * available for further allocation). If ptr is a null pointer, no action
    * occurs. Otherwise, if ptr does not match a pointer earlier returned by
    * calloc, malloc or realloc or if the space has been deallocated by a call
    * to free or realloc, the behaviour is undefined.
    */
extern void *malloc(size_t /*size*/);
   /*
    * allocates space for an object whose size is specified by 'size' and whose
    * value is indeterminate.
    * Returns: either a null pointer or a pointer to the allocated space.
    */

extern void *realloc(void * /*ptr*/, size_t /*size*/);
   /*
    * changes the size of the object pointed to by ptr to the size specified by
    * size. The contents of the object shall be unchanged up to the lesser of
    * the new and old sizes. If the new size is larger, the value of the newly
    * allocated portion of the object is indeterminate. If ptr is a null
    * pointer, the realloc function behaves like a call to malloc for the
    * specified size. Otherwise, if ptr does not match a pointer earlier
    * returned by calloc, malloc or realloc, or if the space has been
    * deallocated by a call to free or realloc, the behaviour is undefined.
    * If the space cannot be allocated, the object pointed to by ptr is
    * unchanged. If size is zero and ptr is not a null pointer, the object it
    * points to is freed.
    * Returns: either a null pointer or a pointer to the possibly moved
    *          allocated space.
    */


extern void *bsearch(const void *key, const void * /*base*/,
              size_t /*nmemb*/, size_t /*size*/,
              int (* /*compar*/)(const void *, const void *));
   /*
    * searches an array of nmemb objects, the initial member of which is
    * pointed to by base, for a member that matches the object pointed to by
    * key. The size of each member of the array is specified by size.
    * The contents of the array shall be in ascending sorted order according to
    * a comparison function pointed to by compar, which is called with two
    * arguments that point to the key object and to an array member, in that
    * order. The function shall return an integer less than, equal to, or
    * greater than zero if the key object is considered, respectively, to be
    * less than, to match, or to be greater than the array member.
    * Returns: a pointer to a matching member of the array, or a null pointer
    *          if no match is found. If two members compare as equal, which
    *          member is matched is unspecified.
    */
extern void qsort(void * /*base*/, size_t /*nmemb*/, size_t /*size*/,
           int (* /*compar*/)(const void *, const void *));
   /*
    * sorts an array of nmemb objects, the initial member of which is pointed
    * to by base. The size of each object is specified by size.
    * The contents of the array shall be in ascending order according to a
    * comparison function pointed to by compar, which is called with two
    * arguments that point to the objects being compared. The function shall
    * return an integer less than, equal to, or greater than zero if the first
    * argument is considered to be respectively less than, equal to, or greater
    * than the second. If two members compare as equal, their order in the
    * sorted array is unspecified.
    */

extern int abs(int /*j*/);
   /*
    * computes the absolute value of an integer j. If the result cannot be
    * represented, the behaviour is undefined.
    * Returns: the absolute value.
    */
extern div_t div(int /*numer*/, int /*denom*/);
   /*
    * computes the quotient and remainder of the division of the numerator
    * numer by the denominator denom. If the division is inexact, the resulting
    * quotient is the integer of lesser magnitude that is the nearest to the
    * algebraic quotient. If the result cannot be represented, the behaviour is
    * undefined; otherwise, quot * demon + rem shall equal numer.
    * Returns: a structure of type div_t, comprising both the quotient and the
    *          remainder. the structure shall contain the following members,
    *          in either order.
    *          int quot; int rem;
    */
extern long int labs(long int /*j*/);
   /*
    * computes the absolute value of an long integer j. If the result cannot be
    * represented, the behaviour is undefined.
    * Returns: the absolute value.
    */
extern ldiv_t ldiv(long int /*numer*/, long int /*denom*/);
   /*
    * computes the quotient and remainder of the division of the numerator
    * numer by the denominator denom. If the division is inexact, the sign of
    * the resulting quotient is that of the algebraic quotient, and the
    * magnitude of the resulting quotient is the largest integer less than the
    * magnitude of the algebraic quotient. If the result cannot be represented,
    * the behaviour is undefined; otherwise, quot * demon + rem shall equal
    * numer.
    * Returns: a structure of type ldiv_t, comprising both the quotient and the
    *          remainder. the structure shall contain the following members,
    *          in either order.
    *          long int quot; long int rem;
    */


#ifdef __cplusplus
}
#endif

#endif

/* end of stdlib.h */
