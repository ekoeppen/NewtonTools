/*
	File:		NewtonExceptions.h

	Contains:	Exception macros for Newton C++ Tools
	
	Written by:	The Newton C++ Tools group

	Copyright:	� 1992-1995 by Apple Computer, Inc.  All rights reserved.
	
*/

#ifndef __NEWTONEXCEPTIONS_H
#define __NEWTONEXCEPTIONS_H

/****************************************************************************************

	We support:

	newtonStyleExceptions
		... the exceptions thrown being "structured strings". 
		Can be used to build any standalone system ARMCpp compiler.


****************************************************************************************/

/****************************************************************************************
 *																						*
 *	NOTE: Only the following macros and functions should be used directly by your 		*
 *		  code. The rest of this file should be considered private implementation 		*
 *		  details.																		*
 *																						*
 *		DeclareException(name,super)													*
 *		DefineException(name,super,string)												*
 *		ExceptionDestructor																*
 *		VOLATILE(x)																		*
 *		DECLARE_VOLATILE(type, x)														*
 *		DECLARE_VOLATILE_INIT(type, x, value)											*
 *		Subexception(ExceptionName sub, ExceptionName super)							*
 *		Throw(ExceptionName name, void* data = 0, ExceptionDestructor destructor = 0 )	*
 *		ThrowMsg(char* msg)																*
 *		CurrentException()																*
 *		rethrow, throw1, throw2, throw3													*
 *		newton_try																		*
 *		newton_catch(what)																*
 *		cleanup																			*
 *		end_try																			*
 *		unwind_protoect																	*
 *		on_unwind																		*
 *		end_unwind																		*
 *		unwind_failed()																	*
 *																						*
 ****************************************************************************************/

/****************************************************************************************

	Exceptions are declared and defined using the DeclareException and
	NewDefineException macros. Both macros take the exception name as the
	first parameter and the exception's superclass as the second parameter.
	NewDefineException also takes a "structured string" as a third
	parameter to enforce a hierarchy under exception systems that can't
	work with C++ classes.

		DeclareException(exMyException, exRootException)
		NewDefineException(exMyException,exRootException,evt.ex.myException)

	An exception is signalled with the throw1, throw2, and throw3 macros.
	The throw1 macro takes an exception name and throws it in the manner
	appropriate to the underlying exception system being used.

		throw1(exMyException);

	The throw2 macro takes an arbitrary data value as a second parameter.
	This data can be used to aid in debugging. For instance, it could
	contain an error code.

		throw2(exMyException, 1234);

	If the data you are throwing is heap data that needs to be disposed of
	after the exception has been handled, you can use the throw3 macro and
	specify a destructor function.

		throw3(exMyException, myHeapData, DestroyHeapDataFn);

	There is a Throw function, which takes three arguments: an exception
	name, a void* for accompanying data, and a pointer to a deallocation
	function for the data (NULL for none).

		Throw(exMyException, (void*) 1234, 0);

	In C++. the second and third arguments default to zero, so you can just
	say

		Throw(exMyException);

	WARNING: When running under a system that supports throwing and catching
	exceptions based on data type, the Throw function will attempt to
	convert the exception name (the first parameter, which is a string) to
	an object of the appropriate type. It does this by comparing the
	exception name against all known exception types. This process can make
	the Throw function slow (because of the comparisons that are required)
	or faulty (if the exception name doesn't correspond to  any of the
	known exception types). For these reasons, use of the Throw function is
	discouraged. Instead, use the throw1, throw2, and throw3 macros
	whenever you can.

	There is ThrowMsg function that takes a char* and throws an
	exMsgException with the given string as the data.  This is good for
	random debugging messages.

		ThrowMsg("Random debugging message");

	Exception handlers are introduced with newton_try and ended with
	end_try.  Within a handler are newton_catch clauses that specify the
	exception names they handle. A newton_catch clause will catch the
	specified exception or any of its subexceptions.  Inside a newton_catch
	clause, the current exception can be accessed with CurrentException().

		newton_try
		{
			DoSomeStuff;
		}
		newton_catch (exBlahError)
		{
			printf("Couldn't do stuff: %s.", CurrentException()->name);
		}
		end_try;

	A newton_catch clause can throw the current exception again using
	the rethrow macro.

		newton_catch (exBlahError)
		{
			blahErrors++;
			rethrow;
		}

	A newton_catch_all clause may appear after the newton_catch clauses (if
	any). If no newton_catch clause matches the current exception, the
	newton_catch_all clause will catch the exception.

		TSomething foo;

		newton_try
		{
			DoSomeStuff;
		}
		newton_catch (exBlahError)
		{
			printf("Couldn't do stuff: %s.", CurrentException()->name);
		}
		newton_catch_all
		{
			exception_occurred = true;
		}
		end_try;

	A cleanup clause may appear after the newton_catch clauses (if any).  If
	no newton_catch clause matches the current exception, the cleanup
	clause will be run before the next handler is tried. This makes cleanup
	clauses identical to newton_catch_all clauses, except that cleanup
	clauses implicitly rethrow the exception.

		TSomething foo;

		newton_try
		{
			DoSomeStuff;
		}
		cleanup
		{
			foo.~TSomething();
		}
		end_try;

	If the compiler being used doesn't provide the appropriate support, you
	have to call destructors yourself in cases like the above.  Of course,
	this is error-prone. You can determine if the compiler you're using
	destructs objects when unwinding the stack by using the
	hasAutoDestructOnException preprocessor symbol. Thus, your exception
	handling code could look like:

		TSomething foo;

	#if defined(hasAutoDestructOnException)
		newton_try
	#endif
		{
			DoSomeStuff;
		}
	#if defined(hasAutoDestructOnException)
		cleanup
		{
			foo.~TSomething();
		}
		end_try;
	#endif

	Finally, the unwind_protect construct allows the specification of code
	that must be run whether or not an exception occurs.

		unwind_protect
		{
			OpenAFile();
			DoSomethingWithTheFile();
		}
		on_unwind
		{
			CloseTheFile();
		}
		end_unwind;

	Within an on_unwind block, you can determine whether an exception
	occurred by using unwind_failed(). If an exception occurred, it will
	automatically be rethrown at the end of the on_unwind clause.

	Sometimes you may need to combine unwind_protect with try/catch:

		newton_try
		{
			unwind_protect
			{
				OpenAFile();
				DoSomethingWithTheFile();
			}
			on_unwind
			{
				CloseTheFile();
			}
			end_unwind;
		}
		newton_catch (exMyError)
		{
			printf("Couldn't DoSomethingWithTheFile!");
		}
		end_try;

	CAUTION

	There is a subtle problem that can occur when the compiler assigns local
	variables to registers. If you modify the variable inside of a try
	block preceding code that could possibly throw an exception, and you
	need to access that variable after the try block has exited, you must
	declare that variable as volatile. Example:

		DECLARE_VOLATILE(int, x);
		x = 0;
		newton_try
		{
			...
			x = 1;
			... exception thrown here ...

		}
		newton_catch (exMyError)
		{
			...x...				// x used here...

		end_try;

		...x...					// ... and/or x used here.


	If you don't declare x as volatile, it might be kept in a register. When
	the exception is thrown, the state of the register is restored to the
	value it had when the try block was entered. Thus, x would hold 0 instead
	of 1 like we expected.


****************************************************************************************/


#define newtonStyleExceptions 1


/*
** Bring in any appropriate header files
*/

typedef long int _excptn_buf[22];
#ifdef __cplusplus
extern "C"	int __xxx_XS001_(_excptn_buf  ebuf ) ;
#else
extern	int __xxx_XS001_(_excptn_buf  ebuf ) ;
#endif


/*
** Set hasVolatileKeyword
*/

#if defined(__arm)
	#define hasVolatileKeyword 1
#endif


/*
** Define the DeclareException, DefineException, and NewDefineException macros
*/
	#define DeclareException(name, super) extern const ExceptionName name
	#define DefineException(name, string) const ExceptionName name = #string
	#define NewDefineException(name, super, string) const ExceptionName name = #string

	#define DeclareBaseException(exname) DeclareException(exname,CNewtonException)
	#define DefineBaseException(exname, string) NewDefineException(exname,CNewtonException,string)



/*
** Define the VOLATILE, DECLARE_VOLATILE, and DECLARE_VOLATILE_INIT macros
*/

#ifndef VOLATILE
	#ifdef __arm
		/*
		** if you remove the '(void)&dummy_volatile_;' you�ll get warnings to help find all
		** uses of this obsolete macro
		*/
		#define VOLATILE(x) do { const void* dummy_volatile_ = &x; (void)&dummy_volatile_; } while (0)
	#else
		/* just the same as MacApp; this worked for the old ARM6C, too */
		#define VOLATILE(a) ((void) &a)
	#endif

#endif /* VOLATILE */

#ifndef DECLARE_VOLATILE
	/*
	**	This way is sometimes better. Usage:
	**
	**		volatile int foo;
	**
	**	becomes:
	**
	**		DECLARE_VOLATILE(int, foo);
	**
	**	The advantage of DECLARE_VOLATILE is that it allows you to use
	**	the volatile keyword if it exists. The disadvantage is that it
	**	can't be used in C code more than once in the same block on a
	**	compiler that doesn't have the volatile keyword.
	**
	**	DECLARE_VOLATILE_INIT is a handy macro that will also initialize
	**	a variable when it's declared.
	*/

	#ifdef hasVolatileKeyword
		#define DECLARE_VOLATILE(type, var) type volatile var

		#ifdef __cplusplus
		#define DECLARE_VOLATILE_INIT(type, var, expr) type volatile var(expr)
		#else
		#define DECLARE_VOLATILE_INIT(type, var, expr) type volatile var = (expr)
		#endif
	#else
		#define DECLARE_VOLATILE(type, var) type var; VOLATILE(var)
		#define DECLARE_VOLATILE_INIT(type, var, expr) type var = expr; VOLATILE(var)
	#endif
#endif


/*
** undef to get rid of extraneous def's
*/
#undef Throw
#undef Catch


typedef char* ExceptionName;
typedef ExceptionName ExceptionNamePtr;
typedef void (*ExceptionDestructor)(void*);

#ifdef __cplusplus

	extern "C"	void	Throw(ExceptionName name, void* data = NULL, ExceptionDestructor destructor = NULL);
	extern "C"	void	ThrowMsg(char* msg);
	extern "C"	int		Subexception(ExceptionName sub, ExceptionName super);

#else

	void	Throw(ExceptionName name, void* data, ExceptionDestructor destructor);
	void	ThrowMsg(char* msg);
	int		Subexception(ExceptionName sub, ExceptionName super);

#endif

#ifdef __cplusplus


	#define CurrentException()				(&_info.exception)

	#define rethrow							::NextHandler(&_info)
	#define throw1(ex)						::Throw(ex)
	#define throw2(ex, data)				::Throw(ex, (void*) (data))
	#define throw3(ex, data, destructor)	::Throw(ex, (void*) (data), (ExceptionDestructor) destructor)

	#define newton_try														\
		do {																\
			ExceptionHandler _info;											\
			_info.header.catchType = kExceptionHandler;						\
			if (__xxx_XS001_(_info.state) == 0 && (::AddExceptionHandler((CatchHeader*) &_info), 1))	\

	#define newton_catch(what)												\
			else if (::Subexception(_info.exception.name, (what)))			\

	#define newton_catch_all												\
			else if (1)														\

	#define cleanup															\
			else if (1) for (; 1; rethrow)									\

	#define end_try															\
			else rethrow;													\
			::ExitHandler(&_info);											\
		} while(0)															\

	#define unwind_protect													\
		do {																\
			ExceptionHandler _info;											\
			_info.header.catchType = kExceptionHandler;						\
			int _failed = 0;												\
			if (__xxx_XS001_(_info.state) == 0 && (::AddExceptionHandler((CatchHeader*) &_info), 1)) {	\

	#define on_unwind														\
				::ExitHandler(&_info);										\
			}																\
			else {															\
				_failed = 1;												\
			}																\

	#define end_unwind														\
			if (unwind_failed()) rethrow;									\
		} while (0)															\

	#define unwind_failed()													\
		(_failed != 0)														\

		/* Get ... of these once everyone's using newton_try, newton_catch, rethrow */
	#define try newton_try
	#define catch newton_catch
	#define throw rethrow


#else	/* !__cplusplus */

	/*
	** This section appears to be identical to the newtonStyleExceptions
	** section, except that global functions are not prefixed with "::".
	*/

	#define CurrentException()				(&_info.exception)

	#define rethrow							NextHandler(&_info)

#ifdef __cplusplus
	#define throw1(ex)						Throw(ex)
	#define throw2(ex, data)				Throw(ex, (void*) (data))
	#define throw3(ex, data, destructor)	Throw(ex, (void*) (data), (ExceptionDestructor) destructor)
#else
	#define throw1(ex)						Throw(ex, (void*) 0,		(ExceptionDestructor) 0)
	#define throw2(ex, data)				Throw(ex, (void*) (data),	(ExceptionDestructor) 0)
	#define throw3(ex, data, destructor)	Throw(ex, (void*) (data),	(ExceptionDestructor) destructor)
#endif

	#define newton_try														\
		do {																\
			ExceptionHandler _info;											\
			_info.header.catchType = kExceptionHandler;						\
			if (__xxx_XS001_(_info.state) == 0 && (AddExceptionHandler((CatchHeader*) &_info), 1))	\

	#define newton_catch(what)												\
			else if (Subexception(_info.exception.name, (what)))			\

	#define newton_catch_all												\
			else if (1)														\

	#define cleanup															\
			else if (1) for (; 1; rethrow)									\

	#define end_try															\
			else rethrow;													\
			ExitHandler(&_info);											\
		} while(0)															\

	#define unwind_protect													\
		do {																\
			ExceptionHandler _info;											\
			int _failed = 0;												\
			_info.header.catchType = kExceptionHandler;						\
			VOLATILE(_failed);												\
			if (__xxx_XS001_(_info.state) == 0 && (AddExceptionHandler((CatchHeader*) &_info), 1))	\

	#define on_unwind														\
			else {															\
				_failed = 1;												\
			}																\

	#define end_unwind														\
			if (unwind_failed()) rethrow;									\
			ExitHandler(&_info);											\
		} while (0)															\

	#define unwind_failed()													\
		(_failed != 0)														\

	/* Get ... of these once everyone's using newton_try, newton_catch, rethrow */
	#define try newton_try
	#define catch newton_catch
	#define throw rethrow

#endif



#ifndef __cplusplus
typedef struct Exception Exception;
#endif

struct Exception
{
	ExceptionNamePtr		name;
	void*					data;
	ExceptionDestructor		destructor;
};




	#ifndef __cplusplus
	typedef struct CatchHeader CatchHeader;
	#endif

	struct CatchHeader
	{
		int				catchType;				/* e.g., kExceptionHandler */
		CatchHeader*	next;
	};


	#ifndef __cplusplus
	typedef struct ExceptionHandler ExceptionHandler;
	#endif

	struct ExceptionHandler
	{
		CatchHeader	header;
		_excptn_buf	state;
		Exception	exception;
	};


	#ifndef __cplusplus
	typedef struct ExceptionCleanup ExceptionCleanup;
	#endif

	struct ExceptionCleanup
	{
		CatchHeader		header;
		void*			object;
		void			(*function)(void*);
	};


	#ifndef __cplusplus
	typedef struct ExceptionGlobals ExceptionGlobals;
	#endif

	struct ExceptionGlobals
	{
		CatchHeader*	firstCatch;
	};


	#ifdef __cplusplus
	extern "C" {
	#endif

	void	AddExceptionHandler(CatchHeader *i);
	void	ExitHandler(ExceptionHandler *i);
	void	NextHandler(ExceptionHandler *i);

	#ifdef __cplusplus
	}
	#endif




DeclareBaseException(evRootEvent);
DeclareException(exRootException, evRootEvent);
DeclareException(exSkia, exRootException);
DeclareException(exMsgException, exRootException);
DeclareException(exDivideByZero, exRootException);

/* ARM aborts */
DeclareException(exAbort, exRootException);
DeclareException(exBusError, exAbort);
DeclareException(exAlignment, exAbort);
DeclareException(exIllegalInstr, exAbort);
DeclareException(exPermissionViolation, exAbort);
DeclareException(exWriteProtected, exAbort);
DeclareException(exOutOfStack, exAbort);



	/*
	 *	Kinds of cleanup handlers
	 *	Assembly language depends on these enums.  Step lightly.
	 */

	enum
	{
		 kExceptionHandler				= 0,	/* try ... */
		 kExceptionCleanup				= 1,	/* unwind_protect ... */
		 kExceptionCleanupDone			= 2,	/* unwind_protect (already performed) */
		 kExceptionMonitorBoundary		= 3,	/* marks start of monitor stack */
		 kExceptionNonUserBoundary		= 4		/* unhandled exception in (e.g.) IRQ code */
	};


	#ifdef forARM

		#ifdef __cplusplus
			extern "C" void* GetGlobals(void);
			extern "C" void SetGlobals(void* structure);
		#else
			extern void* GetGlobals(void);
			extern void SetGlobals(void* structure);
		#endif

		#define gFirstCatch			(((ExceptionGlobals*) ((unsigned long) GetGlobals() - sizeof(ExceptionGlobals)))->firstCatch)

	#endif	/* forArm */


	#ifdef __cplusplus
	extern "C" {
	#endif

	void	RemoveExceptionHandler(CatchHeader *i);

	#ifdef __cplusplus
	}
	#endif


#endif /* __NEWTONEXCEPTIONS_H */
