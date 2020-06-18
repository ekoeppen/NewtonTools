/*
	File:		stdarg.h

	Contains:	va_arg list macros etc

	Written by:	Newton Tools Team
	
	Copyright:	� 1991-1992 by Apple Computer, Inc., all rights reserved.

*/

/********** Apple CFront USERS PLEASE NOTE! **********/
/* CFront doesn't accept expressions of the form ((struct foo {int x;}*) 0)->x.

	Solution:  In your code, somewhere before you say "va_arg(x, Type);"
				you must say "va_hack(Type);".
	Nasty side:  For the hack to work, Type must be a single word.  So, for
				example, if your list is a list of pointers, you can not
				say va_hack(MyStruct*).  You must define MyStructPtr and
				then you may successfully utter va_hack(MyStructPtr).

	Example:

	Boolean RSect(Rect *minRect, short count, Rect *r1, ...)
	{
		typedef Rect* RectPtr;

		RectPtr		curRectPtr;
		va_list		args;

		va_start(args, r1);

		if (condition to quit early) {
			va_end(args);
			return(false);
		}

		for (count--; count > 0; count--) {
			va_hack(RectPtr);
			curRectPtr = va_arg(args, RectPtr);
		}

		va_end(args);
		return(true);
	}


 */



#pragma force_top_level
#pragma include_only_once

#ifndef __STDARG_H
#define __STDARG_H

#if defined(__cplusplus) && defined(applec)
/* definitions for Apple's ARMCFront */
#define ___type
#define ___assert(x,y) 0
#endif

/*
 * stdarg.h declares a type and defines three macros, for advancing through a
 * list of arguments whose number and types are not known to the called
 * function when it is translated. A function may be called with a variable
 * number of arguments of differing types. Its parameter list contains one or
 * more parameters. The rightmost parameter plays a special role in the access
 * mechanism, and will be called parmN in this description.
 */

/* N.B. <stdio.h> is required to declare vfprintf() without defining      */
/* va_list.  Clearly the type __va_list there must keep in step.          */
typedef char *va_list[1];       /* see <stdio.h> */
   /*
    * an array type suitable for holding information needed by the macro va_arg
    * and the function va_end. The called function shall declare a variable
    * (referred to as ap) having type va_list. The variable ap may be passed as
    * an argument to another function.
    * Note: va_list is an array type so that when an object of that type
    * is passed as an argument it gets passed by reference.
    */

/* Note that ___type is a syntactic item a bit like the type qualifiers   */
/* 'static', 'register', 'const' etc except that it has no effect! Its    */
/* purpose is to indicate when a type is being introduced and thus        */
/* help (a bit) when the user gets the args to va_arg the wrong way round */

#if	defined(__cplusplus) && defined(applec)
/* definitions for Apple's ARMCFront with its HACK */

#define __alignof(type) \
   ((char *)&(((__align_##type##_struct*) 0)->__member2) - \
    (char *)0)
#define va_hack(type) \
   struct __align_##type##_struct { char __member1; type __member2; }

#else
#define __alignof(type) \
   ((char *)&(((struct{char __member1; \
                       ___type type __member2;}*) 0)->__member2) - \
    (char *)0)
#endif

#define __alignuptotype(ptr,type) \
   ((char *)((int)(ptr) + (__alignof(type)-1) & ~(__alignof(type)-1)))


#define va_start(ap,parmN) \
   ((void)(*(ap) = (char *)&(parmN) + sizeof(parmN)))
   /*
    * The va_start macro shall be executed before any access to the unnamed
    * arguments. The parameter ap points to an object that has type va_list.
    * The va_start macro initialises ap for subsequent use by va_arg and
    * va_end. The parameter parmN is the identifier of the rightmost parameter
    * in the variable parameter list in the function definition (the one just
    * before the , ...). If the parameter parmN is declared with the register
    * storage class the behaviour is undefined (Norcroft C gives diagnostic).
    * parmN shall not be affected by default argument conversions (Norcroft
    * C gives a diagnostic and would (July 1990) generate 'wrong' code).
    * Returns: no value.
    */

#define va_arg(ap,type) \
   (___assert((___typeof(___type type) & 0x481) == 0, \
              "Illegal type used with va_arg"), \
   *(___type type *)((*(ap)=__alignuptotype(*(ap),type)+sizeof(___type type))-\
                     sizeof(___type type)))
   /*
    * The va_arg macro expands to an expression that has the type and value of
    * the next argument in the call. The parameter ap shall be the same as the
    * va_list ap initialised by va_start. Each invocation of va_arg modifies
    * ap so that successive arguments are returned in turn. The parameter
    * 'type' is a type name such that the type of a pointer to an object that
    * has the specified type can be obtained simply by postfixing a * to
    * 'type'. If 'type' disagrees with the type of the actual next argument
    * (as promoted according to the default argument promotions), the behaviour
    * is undefined.
    * Returns: The first invocation of the va_arg macro after that of the
    *          va_start macro returns the value of the argument after that
    *          specified by parmN. Successive invocations return the values of
    *          the remaining arguments in succession.
    * Note: care is taken in va_arg so that illegal things like va_arg(ap,char)
    * which may seem natural but are illegal are caught. The special Norcroft
    * C keywords ___assert and ___typeof are used to do this: these keywords
    * are not intended for use by ordinary users.
    */

#define va_end(ap) ((void)(*(ap) = (char *)-256))
   /*
    * The va_end macro facilitates a normal return from the function whose
    * variable argument list was referenced by the expansion of va_start that
    * initialised the va_list ap. If the va_end macro is not invoked before
    * the return, the behaviour is undefined.
    * Returns: no value.
    * Note: this macro is careful to avoid compiler warning messages and uses
    * a -ve address to ensure address trap.
    */

#endif

/* end of stdarg.h */
