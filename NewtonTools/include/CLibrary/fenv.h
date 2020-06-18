/*
	File:		fenv.h

	Contains:	Portable SANE environment

	Written by:	Ali Sazegari et al

	Copyright:	� 1993 by Apple Computer, Inc., all rights reserved.

*/

/*******************************************************************************
*													 	
*	File fenv.h - ARM x00 version,							
*													 
*	A collection of functions designed to provide access to the floating	
*	point environment for numerical programming. It is modeled after the 
*	Numerical C Extensions Group�s requirements ( NCEG / X3J11.1 ).	
*													 *
*	The file <fenv.h> declares many functions in support of numerical
*	programming.  It provides a set of environmental controls similar to
*	the ones found in <SANE.h>.  Programs that test flags or run under
*	non-default modes must do so under the effect of an enabling	
*	"fenv_access" pragma.								
*												
*	Note that the rounding mode maskes are dummies, because ARM has round  
*	bits in each instruction.							
*												
*	Copyright � 1993,95 Apple Computer, Inc.  All rights reserved.		
*												
*	Written by Ali Sazegari, started on October 1992.		
*	Adapted by Jerome Coonen
*   Adapted for Newton C++ Tools by John Arkley 1995
*																						
*******************************************************************************/

#ifndef __FENV_H
#define __FENV_H

#ifdef __cplusplus
extern "C" {
#endif

/*	The typedef fenv_t is a type for representing the entire floating-point
	environment in a single object.							*/

typedef	long int	fenv_t;

/*	The typedef fexcept_t is a type for representing the floating-point
	exception flag state collectively.							*/

typedef	long int	fexcept_t;

/*	Definitions of floating-point exception macros					*/

enum
	{
	FE_INEXACT   = 0x00000010,	/*	inexact					*/
	FE_DIVBYZERO = 0x00000002,	/*	divide-by-zero				*/
	FE_UNDERFLOW = 0x00000008,	/*	underflow					*/
	FE_OVERFLOW  = 0x00000004,	/*	overflow					*/
	FE_INVALID   = 0x00000001	/*	invlalid					*/
	};

/*	The bitwise OR of all exception macros						*/

#define	FE_ALL_EXCEPT	( FE_INEXACT | FE_DIVBYZERO | FE_UNDERFLOW | FE_OVERFLOW | FE_INVALID )

/*	Definitions of rounding direction macros						*/

enum
	{
	FE_TONEAREST  = 0x00000000,
	FE_TOWARDZERO = 0x00000000,
	FE_UPWARD     = 0x00000000,
	FE_DOWNWARD   = 0x00000000
	};

/*	Definition of pointer to IEEE default environment object			*/

extern fenv_t _FE_DFL_ENV;			/* default environment object		*/
#define FE_DFL_ENV &_FE_DFL_ENV		/* pointer to default environment	*/


/*	The following functions provide access to the exception flags.  The "int"
	input argument can be constructed by bitwise ORs of the exception macros:
	for example: FE_OVERFLOW | FE_INEXACT.						*/

/*	The function "feclearexcept" clears the supported exceptions represented
	by its argument.										*/

void feclearexcept ( int excepts );

/*	The function "fegetexcept" stores a representation of the exception
	flags indicated by the argument "excepts" through the pointer argument
	"flagp".											*/

void fegetexcept ( fexcept_t *flagp, int excepts );

/*	The function "feraiseexcept" raises the supported exceptions
	represented by its argument.								*/

void feraiseexcept ( int excepts );

/*	The function "fesetexcept" sets or clears the exception flags indicated
	by the int argument "excepts" according to the representation in the
	object pointed to by the pointer argument "flagp".  The value of
	"*flagp" must have been set by a previous call to "fegetexcept".
	This function does not raise exceptions; it just sets the state of
	the flags.											*/

void fesetexcept ( const fexcept_t *flagp, int excepts );

/*	The function "fetestexcept" determines which of the specified subset of
	the exception flags are currently set.  The argument "excepts" specifies
	the exception flags to be queried as a bitwise OR of the exception
	macros.  This function returns the bitwise OR of the exception macros
	corresponding to the currently set exceptions included in "excepts".	*/

int fetestexcept ( int excepts );



/*	The following functions provide control of rounding direction modes.	*/

/*	The function "fegetround" returns the value of the rounding direction
	macro which represents the current rounding direction.			*/

int fegetround ( void );

/*	The function "fesetround" establishes the rounding direction represented
	by its argument.	It returns nonzero if and only if the argument matches
	a rounding direction macro.  If not, the rounding direction is not
	changed.											*/

int fesetround ( int round );



/*	The following functions manage the floating-point environment---
	exception flags and dynamic modes---as one entity.				*/

/*	The function "fegetenv" stores the current floating-point environment
	in the object pointed to by its pointer argument "envp".			*/

void fegetenv ( fenv_t *envp );

/*	The function "feholdexcept" saves the current environment in the object
	pointed to by its pointer argument "envp", clears the exception flags,
	and clears floating-point exception enables.  This function supersedes
	the SANE function "procentry", but it does not change the current
	rounding direction mode.								*/

int feholdexcept ( fenv_t *envp );

/*	The function "fesetenv" installs the floating-point environment
	environment represented by the object pointed to by its argument
	"envp".  The value of "*envp" must be set by a call to "fegetenv" or
	"feholdexcept", by an implementation-defined macro of type "fenv_t",
	or by the use of the pointer macro FE_DFL_ENV as the argument.		*/

void fesetenv ( const fenv_t *envp );

/*	The function "feupdateenv" saves the current exceptions into its
	automatic storage, installs the environment represented through its
	pointer argument "envp", and then re-raises the saved exceptions.
	This function, which supersedes the SANE function "procexit", can be
	used in conjunction with "feholdexcept" to write routines which hide
	spurious exceptions from their callers.						*/

void feupdateenv ( const fenv_t * envp );

#ifdef __cplusplus
}
#endif

#endif
