/*
	File:		OSErrors.h

	Contains:	OS error codes

	Copyright:	� 1992-1996 by Apple Computer, Inc., all rights reserved.

	Derived from v62 internal.

		WARNING:	this file is a global errors file and must be
					FRAMable.  please use caution when adding
					anything other than new errors!
*/

#ifndef __OSERRORS_H
#define	__OSERRORS_H

#include 	"NewtErrors.h"

#ifndef FRAM
	#include "NewtonTypes.h"
	#if !defined(forDocker) && !defined(forNTK)
		#include "NewtonDebug.h"
		typedef NewtonErr	NameServerError;
	#endif
#endif

// This file contains the kinds of exceptions that the kernel generates.


#define kCall_In_Progress							(1)
#define kEnter_Monitor								(2)
#define kExit_From_Fault_Monitor					(3)				// fault monitor exit code
#define kSuspend_Task_Wait_For_Memory				(4)				// suspend this task on way out of monitor until memory becomes available
#define kSuspend_Task_On_Memory_Q					(5)				// suspend task on memory queue for fault monitors

#define kError_Base									(ERRBASE_OS)
#define kError_Bad_Domain_ObjectId					(kError_Base)
#define kError_Bad_PhysicalPage_ObjectId			(kError_Base - 1)
#define kError_Unexpected_Object_Type				(kError_Base - 2)
#define kError_No_Page_Table						(kError_Base - 3)
#define kError_Alloc_On_Uninitalized_Heap			(kError_Base - 4)
#define kError_Call_Not_Implemented					(kError_Base - 5)
#define kError_Bad_Parameters						(kError_Base - 6)
#define kError_No_Memory							(kError_Base - 7)
#define kError_Item_Not_Found						(kError_Base - 8)
#define kError_Could_Not_Create_Object				(kError_Base - 9)
#define kError_Must_Use_RPC							(kError_Base - 10)
#define kError_Bad_Object							(kError_Base - 11)
#define kError_Not_User_Call						(kError_Base - 12)
#define kError_Task_Does_Not_Exist					(kError_Base - 13)
#define kError_MsgDone_Not_Expected					(kError_Base - 14)
#define kError_Bad_ObjectId							(kError_Base - 15)
#define kError_Bad_Message_ObjectId					(kError_Base - 16)
#define kError_Message_Already_Posted				(kError_Base - 17)
#define kError_Cant_Cash_Token						(kError_Base - 18)
#define kError_Port_No_Longer_Exists				(kError_Base - 19)
#define kError_No_Message_Waiting					(kError_Base - 20)
#define kError_Message_Timed_Out					(kError_Base - 21)
#define kError_Bad_Semaphore_GroupId				(kError_Base - 22)
#define kError_Bad_Semaphore_Op_ListId				(kError_Base - 23)
#define kError_Semaphore_Group_No_Longer_Exists		(kError_Base - 24)
#define kError_Semaphore_Would_Cause_Block			(kError_Base - 25)
#define kError_Task_No_Longer_Exists				(kError_Base - 26)
#define kError_Task_Aborted							(kError_Base - 27)
#define kError_Cannot_Suspend_Blocked_Task			(kError_Base - 28)	// *** this will go away
#define kError_Bad_Register_Number					(kError_Base - 29)
#define kError_Bad_Monitor_Function					(kError_Base - 30)
#define kError_No_Such_Monitor						(kError_Base - 31)
#define kError_Not_A_Monitor						(kError_Base - 32)
#define kError_Size_To_Large_Copy_Truncated			(kError_Base - 33) // size was too large in shared memory call (copy truncated)
#define kError_SMem_Mode_Violation					(kError_Base - 34)
#define kError_Object_Not_Owned_By_Task				(kError_Base - 35)
#define kError_Object_Not_Assigned_To_Task			(kError_Base - 36)
#define kError_Im_Totally_Confused					(kError_Base - 37)
#define kError_Another_Task_Already_Blocking		(kError_Base - 38)
#define kError_Call_Aborted							(kError_Base - 39)
#define kError_Object_Already_Initialized			(kError_Base - 40)
#define kError_Nested_Collection					(kError_Base - 41)
#define kError_SharedMemMsg_No_Longer_Exists		(kError_Base - 42)
#define kError_Receiver_Did_Not_Do_RPC				(kError_Base - 43)
#define kError_Copy_Aborted							(kError_Base - 44)
#define kError_Bad_Signature						(kError_Base - 45)
#define kError_Call_Not_In_Progress					(kError_Base - 46)
#define kError_Token_Expected						(kError_Base - 47)
#define kError_Receiver_Object_No_Longer_Exists		(kError_Base - 48)
#define kError_Monitor_Not_Suspsended				(kError_Base - 49)
#define kError_Not_A_Fault_Monitor					(kError_Base - 50)
#define kError_No_Available_Page					(kError_Base - 51)
#define kError_Interrupt_Not_Enabled 				(kError_Base - 52)
#define kError_Interrupt_Not_Implemented 			(kError_Base - 53)
#define kError_Tric_Interrupt_Not_Enabled 			(kError_Base - 54)
#define kError_Tric_Interrupt_Not_Implemented 		(kError_Base - 55)
#define kError_UnResolvedFault				 		(kError_Base - 56)
#define kError_Call_Already_In_Progress		 		(kError_Base - 57)
#define kError_Offset_Beyond_Data			 		(kError_Base - 58)
#define kError_Bus_Access							(kError_Base - 59)
#define kError_Access_Permission					(kError_Base - 60)
#define kError_Permission_Violation			 		(kError_Base - 61)
#define kError_Duplicate_Object						(kError_Base - 62)
#define kError_Ill_Formed_Domain					(kError_Base - 63)
#define kError_Out_Of_Domains						(kError_Base - 64)
#define kError_Write_Protected						(kError_Base - 65)
#define kError_Timer_Expired						(kError_Base - 66)
#define kError_Not_Registered						(kError_Base - 67)
#define kError_Already_Registered					(kError_Base - 68)
#define kError_Reboot_Power_Fault					(kError_Base - 69)
#define kError_Reboot_Battery_Fault					(kError_Base - 70)
#define kError_Reboot_No_Card						(kError_Base - 72)
#define kError_RAMTable_Full						(kError_Base - 73)
#define kError_Unable_to_Satisfy_request			(kError_Base - 74)
#define kError_Sorry_System_Error					(kError_Base - 75)
#define kError_Sorry_System_Failure					(kError_Base - 76)
#define kError_New_System_Software					(kError_Base - 77)
#define kError_Resource_Claimed						(kError_Base - 78)
#define kError_Resource_Unclaimed					(kError_Base - 79)
#define kError_Reboot_Calibration_Missing			(kError_Base - 80)


// result codes
#define kStackError_Base 							(kError_Base - 200)
#define kStackError_StackTooSmall					(kStackError_Base)
#define kStackError_NoRoomForHeap					(kStackError_Base - 1)
#define kStackError_BogusStack						(kStackError_Base - 2)
#define kStackError_StackOverFlow					(kStackError_Base - 3)
#define kStackError_StackUnderFlow					(kStackError_Base - 4)
#define kStackError_AddressOutOfRange				(kStackError_Base - 5)
#define kStackError_BadDomain						(kStackError_Base - 6)


#define kRDMError_Base 								(kError_Base - 300)
#define kError_Unsupported_Request					(kRDMError_Base - 1)


#define kPackageError_Base 							(kError_Base - 400)
#define kError_Bad_Package							(kPackageError_Base - 1)
#define kError_Package_Already_Exists			    (kPackageError_Base - 2)
#define kError_Bad_Package_Version					(kPackageError_Base - 3)
#define kError_Unexpected_End_Of_Package			(kPackageError_Base - 4)
#define kError_Unexpected_End_Of_Pkg_Part			(kPackageError_Base - 5)
#define kError_PartType_Already_Registered			(kPackageError_Base - 6)
#define kError_PartType_Not_Registered				(kPackageError_Base - 7)
#define kError_No_Such_Package						(kPackageError_Base - 8)
#define kError_Newer_Package_Already_Exists			(kPackageError_Base - 9)
#define kError_Older_Package_Already_Exists			(kPackageError_Base - 10)
#define kError_Package_Busy							(kPackageError_Base - 11)
#define kError_XIP_Not_Possible						(kPackageError_Base - 12)


#define kCardError_Base								(kError_Base - 500)
#define kError_Unrecognized_Card 					(kCardError_Base - 1)
#define kError_Card_Not_Ready	 					(kCardError_Base - 2)
#define kError_Card_Bad_Power	 					(kCardError_Base - 3)
#define kError_Unspecified_Card_Error				(kCardError_Base - 4)
#define kError_Card_Reset							(kCardError_Base - 5)
#define kError_Card_Not_Initialized					(kCardError_Base - 6)
#define kError_Card_Service_Not_Installed			(kCardError_Base - 7)
#define kError_Card_Service_Not_Suspend				(kCardError_Base - 8)
#define kError_Card_Service_Not_Resume				(kCardError_Base - 9)
#define kError_No_Usable_Configurations				(kCardError_Base - 10)
#define kError_Format_Failed	 					(kCardError_Base - 11)
#define kError_Unformatted_WriteProtected_Card		(kCardError_Base - 12)

#define kError_Card_Parser_ProcPtr					(kCardError_Base - 20)
#define kError_Card_Tuple_Unknown					(kCardError_Base - 21)
#define kError_Card_SubTuple_Unknown				(kCardError_Base - 22)
#define kError_Card_Tuple_Order						(kCardError_Base - 23)
#define kError_Card_Tuple_Size						(kCardError_Base - 24)
#define kError_Card_Tuple_NoLinkAndLink				(kCardError_Base - 25)
#define kError_Card_Tuple_LinkAndNoLink				(kCardError_Base - 26)
#define kError_Card_Tuple_LinkTarget				(kCardError_Base - 27)
#define kError_Card_Tuple_Version1					(kCardError_Base - 28)
#define kError_Card_Tuple_Version2					(kCardError_Base - 29)
#define kError_Card_Tuple_Jedec						(kCardError_Base - 30)
#define kError_Card_Checksum						(kCardError_Base - 31)
#define kError_Card_No_CIS							(kCardError_Base - 32)		// First tuple is 0xff
#define kError_Card_Blank_CIS						(kCardError_Base - 33)		// All 0's for 16 bytes
#define kError_Card_Bad_CIS							(kCardError_Base - 34)		// Bad CIS
#define kError_Card_Link_Target_C					(kCardError_Base - 35)

#define kFlashError_Base							(kCardError_Base - 50)
#define kError_Flash_Busy							(kFlashError_Base - 1)
#define kError_Flash_Not_Erasing					(kFlashError_Base - 2)
#define kError_Flash_Not_Erase_Suspend				(kFlashError_Base - 3)
#define kError_Flash_Suspend_Erase					(kFlashError_Base - 4)
#define kError_Flash_Erase_Failed					(kFlashError_Base - 5)
#define kError_Flash_Write_Failed					(kFlashError_Base - 6)
#define kError_Flash_Vpp_Low						(kFlashError_Base - 7)
#define kError_Flash_In_Sleep						(kFlashError_Base - 8)
#define kError_Flash_Not_Enough_Power				(kFlashError_Base - 9)
#define kError_Flash_Time_Out						(kFlashError_Base - 10)
#define kError_Flash_Unsupported_Configuration		(kFlashError_Base - 11)
#define kError_Flash_AddressOutOfRange				(kFlashError_Base - 12)
#define kError_No_Flash_In_MotherBoard				(kFlashError_Base - 13)

#define kATAError_Base								(kCardError_Base - 70)
#define kError_ATA_Address_Mark_Not_Found			(kATAError_Base)
#define kError_ATA_Track0_Not_Found					(kATAError_Base - 1)
#define kError_ATA_Aborted_Command					(kATAError_Base - 2)
#define kError_ATA_Media_Changed_Requested			(kATAError_Base - 3)
#define kError_ATA_Sector_Id_Not_Found				(kATAError_Base - 4)
#define kError_ATA_Media_Changed					(kATAError_Base - 5)
#define kError_ATA_Uncorrected_Error				(kATAError_Base - 6)
#define kError_ATA_Bad_Block_Detected				(kATAError_Base - 7)
#define kError_ATA_Unknown_Error					(kATAError_Base - 8)
#define kError_ATA_Busy								(kATAError_Base - 9)
#define kError_ATA_Not_Ready						(kATAError_Base - 10)
#define kError_ATA_No_DRQ							(kATAError_Base - 11)
#define kError_ATA_No_Partition						(kATAError_Base - 12)
#define kError_ATA_Bad_Partition					(kATAError_Base - 13)
#define kError_ATA_Partition_Checksum				(kATAError_Base - 14)


#define kStoreError_Base 							(kError_Base - 600)
#define kSError_ObjectOverRun						(kStoreError_Base)		/* attempt to read or write outside object bounds */
#define kSError_BadBufferPtr						(kStoreError_Base - 1)	/* was "bad object id" in heap-object-store world */
#define kSError_BadCardAccess						(kStoreError_Base - 2)
#define kSError_BadStorageType						(kStoreError_Base - 3)
#define kSError_StoreNotFound						(kStoreError_Base - 4)
#define kSError_WriteProtected						(kStoreError_Base - 5)	/* user has protected the store */
#define kSError_ObjectNotFound						(kStoreError_Base - 6)	/* non-existent object */
#define kSError_BlockFull							(kStoreError_Base - 7)	/* flash internal condition (means "try somewhere else") */
#define kSError_NotVirgin							(kStoreError_Base - 8)	/* (internal condition) retry write somewhere else */
#define kSError_WriteError							(kStoreError_Base - 9)	/* one or more bits failed to assert */
#define kSError_NoMoreObjects						(kStoreError_Base - 10)	/* flash internal condition (TFlashBlock::NextObject ran out of objects) */
#define kSError_EraseInProgress						(kStoreError_Base - 11)	/* flash internal condition: erase in progress */
#define kSError_CardFull							(kStoreError_Base - 12)	/* flash internal condition: no more blocks left on the card */
#define kSError_NoMoreBlocks						(kStoreError_Base - 13)	/* flash internal condition: no more blocks left in search */
#define kSError_LogFull								(kStoreError_Base - 14)	/* flash log is full ("cannot happen") */
#define kSError_NeedsFormat							(kStoreError_Base - 15)	/* card needs to be formatted */
#define kSError_BadPSSID							(kStoreError_Base - 16)	/* totally martian PSSID */
#define	kSError_StoreFull							(kStoreError_Base - 17)	/* we're tapped-out */
#define kSError_BadBattery							(kStoreError_Base - 18) /* missing or low battery on SRAM card */
#define	kSError_NotInTransaction					(kStoreError_Base - 19)	/* attempt to modify store w/o a transaction in effect */
#define	kSError_TransactionAborted					(kStoreError_Base - 20)	/* transaction was aborted */
#define	kSError_WPButNeedsRepair					(kStoreError_Base - 21) /* needs recovery, but card is write protected */
#define kSError_ObjectTooBig						(kStoreError_Base - 22)	/* object too big for store */

#define	kError_ReservedBlock_Base					(kError_Base - 700)
#define kError_ReservedBlock_InvalidObject			(kError_ReservedBlock_Base - 0) /* ~valid flag for object */

#define	kError_DMA_Base								(kError_Base - 800)
#define kError_DMA_Mode								(kError_DMA_Base - 0)
#define kError_DMA_Bus_Access						(kError_DMA_Base - 1)
#define kError_DMA_Buffer_Not_Exist					(kError_DMA_Base - 2)
#define kError_DMA_Addr_Word_Aligned				(kError_DMA_Base - 3)
#define kError_DMA_Count_Word_Aligned				(kError_DMA_Base - 4)
#define kError_DMA_Count_Size						(kError_DMA_Base - 5)
#define kError_DMA_Offset_Size						(kError_DMA_Base - 6)
#define kError_DMA_PCMCIA_Ready						(kError_DMA_Base - 20)
#define kError_DMA_PCMCIA_Input_Ack					(kError_DMA_Base - 21)
#define kError_DMA_PCMCIA_Write_Protect				(kError_DMA_Base - 22)
#define kError_DMA_PCMCIA_Time_Out					(kError_DMA_Base - 23)


/*	----------------------------------------------------------------
**
**	Results of CheckSafeHeap() and SSafeHeapPage::Check()
**	 (various ways that heaps go wrong that we want to check)
**
*/
#define kSafeHeapError_Base							(kError_Base - 900)
#define kSafeHeapError_OddBlockSize					(kSafeHeapError_Base - 0)
#define kSafeHeapError_BlockOutOfRange				(kSafeHeapError_Base - 1)
#define kSafeHeapError_PreferredFreeNotFound 		(kSafeHeapError_Base - 2)
#define kSafeHeapError_FreeAccountingError 			(kSafeHeapError_Base - 3)
#define kSafeHeapError_AccountingError 				(kSafeHeapError_Base - 4)
#define kSafeHeapError_BlockTooBig					(kSafeHeapError_Base - 5)
#define kSafeHeapError_BadPriorPtr					(kSafeHeapError_Base - 6)
#define kSafeHeapError_BadLastPtrInPrior			(kSafeHeapError_Base - 7)
#define kSafeHeapError_BadLastPtrInLast				(kSafeHeapError_Base - 8)




#define kNameAlreadyRegistered	kError_Already_Registered
#define kNoSuchNameRegistered	kError_Not_Registered

#if !defined(FRAM) && !defined(forDocker) && !defined(forNTK)
#define FailOnErr(str, result) if ((result) != noErr) DebugStr((str))
#define	EXCEPTION(x)	DebugStr(#x)
#endif

#endif
