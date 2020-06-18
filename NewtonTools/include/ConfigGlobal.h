/*
	File:		ConfigGlobal.h

	Contains:	Global configutation flags for Newton

	Copyright:	� 1992-1996 by Apple Computer, Inc.  All rights reserved.

	Derived from v19 internal.

*/

#ifndef __CONFIGGLOBAL_H
#define __CONFIGGLOBAL_H


//--------------------------------------------------------------------------------
//	Newton Platform
//		Products: MP, MP100
//--------------------------------------------------------------------------------
#ifdef forJunior

	#define hasRunt						1
	#define hasARM						1
	#define hasARM6						1

	#define	hasUnicode					1

#ifndef forJapan
#ifndef forDebug
	// Save ROM space in debug versions by not having it.
	#define hasParaGraphRecognizer		1
#endif
#endif /* forJapan */

	#define hasRosettaRecognizer		1
	#define hasMondelloRecognizer		1
	#define hasShapeRecognizer			1

#endif /* forJunior */


//--------------------------------------------------------------------------------
//	Newton Platform
//		Products: MP110, MP120, MP130
//--------------------------------------------------------------------------------
#ifdef forLindy

	#define hasRunt						1
	#define hasARM						1
	#define hasARM6						1

	#define	hasUnicode					1

#ifndef forJapan
#ifndef forDebug
	// Save ROM space in debug versions by not having it.
	#define hasParaGraphRecognizer		1
#endif
#endif /* forJapan */

	#define hasRosettaRecognizer		1
	#define hasMondelloRecognizer		1
	#define hasShapeRecognizer			1

#endif /* forLindy */


//--------------------------------------------------------------------------------
//	Newton Platform
//		Products: K
//--------------------------------------------------------------------------------
#ifdef forK

	#define hasVoyager					1
	#define hasARM						1
	#define hasARM7						1

	#define	hasUnicode					1

	#define hasRosettaRecognizer		1
	#define hasMondelloRecognizer		1
	#define hasShapeRecognizer			1
	#define hasUnifiedDictionaries		1

	#define hasSoundIn					1

#endif /* forK */


//--------------------------------------------------------------------------------
//	Newton Platform
//		Products: KRunt
//--------------------------------------------------------------------------------
#ifdef forKRunt

	#define	forLindy					1

	#define hasRunt						1
	#define hasARM						1
	#define hasARM6						1

	#define	hasUnicode					1

	#define hasRosettaRecognizer		1
	#define hasMondelloRecognizer		1
	#define hasShapeRecognizer			1
	#define hasUnifiedDictionaries		1

#endif /* forKRunt */


//--------------------------------------------------------------------------------
//	Newton Platform
//		Products: Q
//--------------------------------------------------------------------------------
#ifdef forQ

	#define hasVoyager					1
	#define hasARM						1
	#define hasARM7						1

	#define	hasUnicode					1

#ifndef forJapan
#ifndef forDebug
	// Save ROM space in debug versions by not having it.
	#define hasParaGraphRecognizer		1
#endif
#endif /* forJapan */

	#define hasRosettaRecognizer		1
	#define hasMondelloRecognizer		1
	#define hasShapeRecognizer			1

	#define hasSoundIn					1
	#define hasInternalMic				1

#endif /* forQ */


//--------------------------------------------------------------------------------
//	Newton Platform
//		Products: NDP
//--------------------------------------------------------------------------------
#ifdef forNDP

	#define hasVoyager					1
	#define hasARM						1
	#define hasARM7						1

	#define	hasUnicode					1

#ifndef forJapan
#ifndef forDebug
	// Save ROM space in debug versions by not having it.
	#define hasParaGraphRecognizer		1
#endif
#endif /* forJapan */

	#define hasRosettaRecognizer		1
	#define hasMondelloRecognizer		1
	#define hasShapeRecognizer			1

	#define hasSoundIn					1
	#define hasInternalMic				1

#endif /* forNDP */


//--------------------------------------------------------------------------------
//	Locale
//--------------------------------------------------------------------------------
#ifdef forJapan
	#define	FOR_INTL				1
	#define	FOR_JAPAN				1
	#define	useLanguage				JAPAN
	#define	hasBubba				1
	#define hasShiftJISConversions	1
	#define	hasTEM					1
#endif

#ifdef forGerman
	#define	FOR_INTL				1
	#define	FOR_GERMAN				1
	#define	useLanguage				GERMAN
#endif

#ifdef forFrench
	#define	FOR_INTL				1
	#define	FOR_FRENCH				1
	#define	useLanguage				FRENCH
#endif


//--------------------------------------------------------------------------------
//	Windows platform
//		Products: NCK, NBU, NCU, NTK, NPI
//--------------------------------------------------------------------------------
#ifdef forWin32

	#define hasByteSwapping				1
	#define hasNoProtocols				1
	#define hasUnicode					1
	#define noPragmaSegment				1
	#define YYDEBUG						1
	#if defined(_DEBUG) && !defined(forDebug)
		#define forDebug 				1
	#endif

#endif /* forWin32 */


//--------------------------------------------------------------------------------
//	Macintosh platform
//		Products: NCK, NBU, NCU, NTK, NPI
//--------------------------------------------------------------------------------
#ifdef forMac

	#define hasNoProtocols				1
	#define hasUnicode					1
	#define	forUniversalMac				1
	#define	OLDROUTINENAMES				0

#endif /* forMac */


//--------------------------------------------------------------------------------
//	Newton Connection Utility et al.
//--------------------------------------------------------------------------------
#ifdef forDocker

	#ifdef forDebug
		#define debugLevel				2
	#endif

#endif /* forDocker */


//--------------------------------------------------------------------------------
//	Newton Backup Utility et al.
//--------------------------------------------------------------------------------
#ifdef forNCKLite

	#define	forDocker					1
	#define forGyroetteLite				TRUE

	#ifdef forDebug
		#define debugLevel				2
	#endif

#endif /* forNCKLite */


//--------------------------------------------------------------------------------
//	API control
//--------------------------------------------------------------------------------
#ifdef forPrivate
	// all public API's are also protected
	#define	forProtected				1
#endif

#ifdef forProtected
	// all protected API's are also private
	#define	forPublic					1
#endif


//--------------------------------------------------------------------------------
//	These are going away, so force the issue
//--------------------------------------------------------------------------------
#undef _ARM600
#undef hasJumpTable
#undef hasQD
#undef hasRecognition
#undef hasSkiaMemMgr
#undef __NOSKIA__
#undef cpuNewton
#undef linkedIn
#undef appleInternal
#undef hasROMExtensions
#undef hasSwedish
#undef hasRecognitionProtocol
#undef forJ1ROM
#undef forSenior
#undef hasCirrus
#undef hasRunt1
#undef hasRunt2
#undef hasByteWideStore
#undef hasFatManTablet
#undef _LCD_DRIVE


//--------------------------------------------------------------------------------
#ifdef hasVoyager
	#define	hasCirrus 1
	#define	forSenior 1
#endif

#ifdef hasARM
	#define	forARM 1
#endif


#endif /* __CONFIGGLOBAL_H */
