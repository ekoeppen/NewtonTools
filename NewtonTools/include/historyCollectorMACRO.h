/*
	File:		historyCollectorMACRO.h

	Contains:	interface definitions for tracing routines

	Copyright:	� 1992-1997 by Apple Computer, Inc., all rights reserved.
	
	Derived from v3** (3/21/97) internal
		
*/

#ifndef __HISTORYCOLLECTORMACRO_H
#define __HISTORYCOLLECTORMACRO_H

#ifdef kDB__pHISTORYCOLLECT

#ifndef __TRACEEVENTS_H
#include "TraceEvents.h"
#endif

//	----	----	----	----	----	----	----	----	
#define	BEGIN_TRACE_DECLARATIONS( _strTRACE_NAME, _ulSIZEBUF, _ulNUMDESC, _pTeventcollectorRET , _parrSeventtracecausedescRET ) \
{ \
	TEventCollector	* _pTeventcollector_ ;  	\
	EventTraceCauseDesc	*_parrSeventtracecausedesc_ ;  \
	int	_ul_currDescIndex = 0;	\
	 	\
	_pTeventcollectorRET = nil; 	\
	_parrSeventtracecausedescRET = nil; 	\
	 	\
	_parrSeventtracecausedesc_ = 	 new EventTraceCauseDesc [ _ulNUMDESC  ];  	\
	if ( ! _parrSeventtracecausedesc_  ) 	\
		goto lbl_beginFail; 	\
 	\
	_pTeventcollector_ =  (TEventCollector *) NewByName ( "TEventCollector", "THistoryCollector");  	\
	if ( ! _pTeventcollector_ ) 	\
	{ 	\
		delete [  ] _parrSeventtracecausedesc_ ; 	\
		goto lbl_beginFail; 	\
	} 	\
 	\
	_pTeventcollectorRET = _pTeventcollector_; 	\
	_parrSeventtracecausedescRET = _parrSeventtracecausedesc_; 	\
	 	\
	_pTeventcollector_ ->Init (sizeof(unsigned long),	\
														"\t%bd: \t0x%bx, \t0x%hx" ,	\
														 (char *)_strTRACE_NAME , _ulSIZEBUF, eLockedBuffer); 	
		

//	----	----	----	----	----	----	----	----	
#define	END_TRACE_DECLARATIONS( _xxx  ) 	\
		_pTeventcollector_->AddDescriptions ( _parrSeventtracecausedesc_ , _ul_currDescIndex  ); 	\
lbl_beginFail:				\
	;									\
} 										\

//	----	----	----	----	----	----	----	----	
#define	TRACE_RELEASE(  _pTeventcollector2FREE , _parrTeventtracecausedesc2FREE )	\
	if ( _pTeventcollector2FREE )		\
	{	\
		_pTeventcollector2FREE -> Delete();	\
		_pTeventcollector2FREE = nil;	\
	}	\
	if ( _parrTeventtracecausedesc2FREE )	\
	{	\
		delete [  ] _parrTeventtracecausedesc2FREE ; 	\
		_parrTeventtracecausedesc2FREE = nil;	\
	}
 	
//	----	----	----	----	----	----	----	----	
#define	DEFINE_TRACE_ENTRY(   _ubID,  _strDESC )	\
	_parrSeventtracecausedesc_ [  _ul_currDescIndex ]  . cause = _ubID;	\
	_parrSeventtracecausedesc_ [  _ul_currDescIndex++ ]  . description =  _strDESC; 
	
//	----	----	----	----	----	----	----	----	
#define	TRACE_MESSAGE(  _pTeventcollector_ , _ubID, _ubBYTEDATUM, _usSHORTDATUM ) \
		if (_pTeventcollector_) _pTeventcollector_ -> Add((ULong) (((UChar) (_ubID) << 24) + ((UChar) (_ubBYTEDATUM) << 16) + ((UShort) ((_usSHORTDATUM) & 0xffff))));

#define	TRACE_FUNCTION(  _pTeventcollector_  ) 	if (_pTeventcollector_) _pTeventcollector_ -> AddAddress();


#else 	//kDB__pHISTORYCOLLECT

#define	BEGIN_TRACE_DECLARATIONS( _strTRACE_NAME, _ulSIZEBUF, _ulNUMDESC, _pTeventcollectorRET , _parrSeventtracecausedescRET )	
#define	END_TRACE_DECLARATIONS( _xxx  ) 	
#define	TRACE_RELEASE(  _pTeventcollector2FREE , _parrTeventtracecausedesc2FREE )	
#define	DEFINE_TRACE_ENTRY(   _ubID,  _strDESC )	
#define	TRACE_MESSAGE(  _pTeventcollector_ , _ubID, _ubBYTEDATUM, _usSHORTDATUM ) 	
#define	TRACE_FUNCTION(  _pTeventcollector_  )	

#endif	//kDB__pHISTORYCOLLECT

#endif //__HISTORYCOLLECTORMACRO_H
