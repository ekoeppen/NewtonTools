/*
	File:		NewtErrors.h

	Contains:	base values for error codes and common errors

	Copyright:	� 1992-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v5 (8/27/96) internal of NewtErrorsExternal.h.

*/


#ifndef __NEWTERRORS_H
#define __NEWTERRORS_H



/*
		Contains base error codes and common errors

		All error codes should run progressively negative off your base

*/


// ---------------  Error bases�  ---------------

#define		ERRBASE_COMMON				(-7000)		// Common errors		(see below)
#define		ERRBASE_NEWT				(-8000)		// Newt errors
#define		ERRBASE_OS					(-10000)	// OS errors
#define		ERRBASE_APPLETALK			(-12000)	// AppleTalk errors
#define		ERRBASE_UTILITYCLASSES		(-14000)	// UtilityClass errors
#define		ERRBASE_COMMTOOL			(-16000)	// CommTool errors
#define		ERRBASE_SERIAL				(-18000)	// SerialTool errors
#define		ERRBASE_MNP					(-20000)	// MNP errors
#define		ERRBASE_FAX					(-22000)	// FAX errors
#define		ERRBASE_TAPI				(-23000)	// TAPI errors
#define		ERRBASE_MODEM				(-24000)	// Modem errors
#define 	ERRBASE_COMMMGR				(-26000)	// CommMgr errors
#define		ERRBASE_DOCKER				(-28000)	// Docker errors
#define		ERRBASE_SOUND				(-30000)	// Sound errors
#define		ERRBASE_COMPRESSION			(-32000)	// Compression errors
#define		ERRBASE_MEMORY				(-34000)	// Memory errors
#define		ERRBASE_TRANSPORT			(-36000)	// Transport errors
#define		ERRBASE_SHARPIR				(-38000)	// Sharp IR errors
#define		ERRBASE_IRDA				(-38500)	// IrDA errors
#define		ERRBASE_ONLINESERVICES		(-40000)	// Online service errs
#define		ERRBASE_EMAIL				(-42000)	// Online service errs
#define		ERRBASE_PRINTING			(-44000)	// Printing errors
#define		ERRBASE_BLACKBIRD			(-46000)	// TSI BlackBird errors (Obsolete)
#define		ERRBASE_MESSAGINGENABLER	(-46000)	// Messaging Enabler errors
#define		ERRBASE_FRAMES				(-48000)	// Frames errors
#define		ERRBASE_WIZARD				(-50000)	// Wizard errors
#define		ERRBASE_GRAPHICS			(-52000)	// Graphics errors
#define		ERRBASE_COMMSCRIPT			(-54000)	// CommScripting errors
#define		ERRBASE_TABLET				(-56000)	// Tablet errors
#define		ERRBASE_PAGEDTSTORE			(-58000)	// Alien store device errors
#define		ERRBASE_INET				(-60000)	// InetTool/NIE errors

#define		ERRBASE_PRODUCTSPECIFIC		(-1000000)	// Product specific errors (none-Apple errors)
													// -1000000 -> -1999999

// ---------------  Common errors�  -------------

#ifndef noErr
#define 	noErr						0
#endif

#ifndef kNoMemory
#define 	kNoMemory					(ERRBASE_COMMON)
#endif

#endif // __NEWTERRORS_H

