/*
 *  UniKeyFR.h
 *  unikeytest
 *
 *  Created by Darryl on 14-5-20.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */


//if(!defined(__stdcall)){//rem next 5 line if windows
#define __stdcall 
typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
//}else{//else            //rem next 1 line if not windows
//#include <windows.h>
//}//endif


#ifdef __cplusplus
extern "C"{
#endif
	
	long __stdcall UniKey_Find(WORD* pHandle, DWORD* pPassword1, DWORD* pPassword2);
	long __stdcall UniKey_Find_Next(WORD* pHandle, DWORD* pPassword1, DWORD* pPassword2);
	long __stdcall UniKey_Lock(WORD* pHandle);
	long __stdcall UniKey_UnLock(WORD* pHandle);
	long __stdcall UniKey_User_Logon(WORD* pHandle, WORD* pPassword1, WORD* pPassword2);
	long __stdcall UniKey_Vender_Logon(WORD* pHandle, WORD* pPassword1, WORD* pPassword2, WORD* pPassword3, WORD* pPassword4);
	long __stdcall UniKey_Logoff(WORD* pHandle);
	long __stdcall UniKey_Read_Memory(WORD* pHandle, WORD* pStartAddress, WORD* pBufferLength, BYTE* pBuffer);
	long __stdcall UniKey_Write_Memory(WORD* pHandle, WORD* pStartAddress, WORD* pBufferLength, BYTE* pBuffer);
	long __stdcall UniKey_Random(WORD* pHandle, WORD* pReturn1, WORD* pReturn2, WORD* pReturn3, WORD* pReturn4);
	long __stdcall UniKey_Seed(WORD* pHandle, DWORD* pSeed, WORD* pReturn1, WORD* pReturn2, WORD* pReturn3, WORD* pReturn4);
	long __stdcall UniKey_Write_SoftID(WORD* pHandle, DWORD* pSoftID);
	long __stdcall UniKey_Read_SoftID(WORD* pHandle, DWORD* pSoftID);
	long __stdcall UniKey_Set_Module(WORD* pHandle, WORD* pModule, WORD* pValue, WORD* pDecrease);
	long __stdcall UniKey_Check_Module(WORD* pHandle, WORD* pModule, WORD* pValue, WORD* pDecrease);
	long __stdcall UniKey_Write_Arithmetic(WORD* pHandle, WORD* pStartAddress, BYTE * pBuffer);
	long __stdcall UniKey_Calculate1(WORD* pHandle, DWORD* lp1, DWORD* lp2, WORD* p1, WORD* p2, WORD* p3, WORD* p4); //start, seed, register
	long __stdcall UniKey_Calculate2(WORD* pHandle, DWORD* lp1, DWORD* lp2, WORD* p1, WORD* p2, WORD* p3, WORD* p4);
	long __stdcall UniKey_Calculate3(WORD* pHandle, DWORD* lp1, DWORD* lp2, WORD* p1, WORD* p2, WORD* p3, WORD* p4);
	long __stdcall UniKey_Module_Decrase(WORD* pHandle, WORD* p1);
	long __stdcall UniKey_Generate_New_Password(WORD* pHandle, DWORD* pSeed1, WORD* pPassword1, WORD* pPassword2, WORD* pPassword3, WORD* pPassword4);
	long __stdcall UniKey_Generate_Key(WORD* pHandle, DWORD* pKeyNumber);
	long __stdcall UniKey_Encrypt(WORD* pHandle, DWORD* pKeyNumber, DWORD* pBufferLength, BYTE *pBuffer);
	long __stdcall UniKey_Decrypt(WORD* pHandle, DWORD* pKeyNumber, DWORD* pBufferLength, BYTE *pBuffer);
	long __stdcall UniKey_MD5(WORD* pHandle, DWORD* pBufferLength, BYTE *pBuffer);
	long __stdcall UniKey_Write_UpdateTag(WORD* pHandle, DWORD* pUpdateTag);
	long __stdcall UniKey_Read_UpdateTag(WORD* pHandle, DWORD* pUpdateTag);
	long __stdcall UniKey_Set_Time(WORD* pHandle, DWORD* pYear, DWORD* pMonth, WORD* pDay, WORD* pHour, WORD* pMinute, WORD* pSecond);
	long __stdcall UniKey_Set_Time_Now(WORD* pHandle);
	long __stdcall UniKey_Get_Time(WORD* pHandle, DWORD* pYear, DWORD* pMonth, WORD* pDay, WORD* pHour, WORD* pMinute, WORD* pSecond);
	long __stdcall UniKey_Erase_Time_Module(WORD* pHandle, DWORD* pModule);
	long __stdcall UniKey_Set_Time_Module_Start_Time(WORD* pHandle, DWORD* pModule, WORD* pYear, WORD* pMonth, WORD* pDay, WORD* pHour);
	long __stdcall UniKey_Set_Time_Module_Start_Time_Now(WORD* pHandle, DWORD* pModule);
	long __stdcall UniKey_Set_Time_Module_Start_Time_Now_PC(WORD* pHandle, DWORD* pModule);
	long __stdcall UniKey_Set_Time_Module_End_Time(WORD* pHandle, DWORD* pModule, WORD* pYear, WORD* pMonth, WORD* pDay, WORD* pHour);
	long __stdcall UniKey_Set_Time_Module_Duration(WORD* pHandle, DWORD* pModule, DWORD* pDays, WORD* pHours);
	long __stdcall UniKey_Check_Time_Module(WORD* pHandle, DWORD* pModule, DWORD* lp2,WORD* pYear, WORD* pMonth, WORD* pDay, WORD* pHour);
	long __stdcall UniKey_Check_Time_Module_Now(WORD* pHandle, DWORD* pModule, DWORD* lp2, WORD* p1);
	long __stdcall UniKey_Check_Time_Module_Now_PC(WORD* pHandle, DWORD* pModule, DWORD* lp2, WORD* p1);
	
	long __stdcall UniKey_Get_Version(WORD* pHandle, DWORD* lp1);
	long __stdcall UniKey_Get_Dongle_Location(WORD* handle, DWORD* lp1);
	
#ifdef __cplusplus
} //  extern "C"{
#endif

// Error Code
#define SUCCESS																0					//Success
#define ERROR_UNIKEY_NOT_FOUND					200	//No UniKey dongle
#define ERROR_UNIKEY_INVALID_PASSWORD			201	//Found UniKey dongle, but basic password is wrong
#define ERROR_UNIKEY_INVALID_PASSWORD_OR_ID		202	//Wrong password or UniKey HID
#define ERROR_UNIKEY_SET_SOFTID_FAILED			203	//Set UniKey ID failed
#define ERROR_INVALID_ADDR_OR_SIZE				204	//Read/Write address or length is wrong
#define ERROR_UNIKEY_UNKNOWN_COMMAND			205	//No such command
#define ERROR_UNIKEY_READ_MEMORY				207	//Read memory failed
#define ERROR_UNIKEY_WRITE_MEMORY				208	//Write memory failed
#define ERROR_UNIKEY_RANDOM						209	//Random number failed
#define ERROR_UNIKEY_SEED						210	//Get seed code failed
#define ERROR_UNIKEY_CALCULATE					211	//Calculate failed
#define ERROR_UNIKEY_NEED_OPEN					212	//Need open dongle before operating dongle
#define ERROR_UNIKEY_OPEN_OVERFLOW				213	//Too many open dongles (>16)
#define ERROR_UNIKEY_NOMORE						214	//No more dongle
#define ERROR_UNIKEY_UNIKEYNEED_FIND			215	//No Find before FindNext
#define ERROR_UNIKEY_MODULE						216	//License module error
#define ERROR_UNIKEY_AR_BAD_COMMAND				217	//Arithmetic instruction Error
#define ERROR_UNIKEY_AR_UNKNOWN_OPCODE			218	//Arithmetic operator Error
#define ERROR_UNIKEY_AR_WRON_GBEGIN				219	//Const number can't use on first arithmetic instruction
#define ERROR_UNIKEY_AR_WRONG_END				220	//Const number can't use on last arithmetic instruction
#define ERROR_UNIKEY_AR_VALUE_OVERFLOW			221	//Const number > 63
#define ERROR_UNIKEY_INVALID_KEY				222	//The key in the key storage is wrong
#define ERROR_UNIKEY_VERIFY_ADV_PASSWORD		223	//Advanced passwords (password3 and passowrd4) not verified
#define ERROR_UNIKEY_INVALID_KEY_STORE			224	//Wrong key storage number
#define EEROR_UNIKEY_GENERATE_NEW_PASSWORD		225	//Generate new password failed
#define ERROR_UNIKEY_READ_UPDATETAG				226	//Read UpdateTag failed
#define ERROR_UNIKEY_WRITE_UPDATETAG			227	//Write UpdateTag failed
#define ERROR_UNIKEY_ENCRYPT_FAILED				228	//Encrypt data failed
#define ERROR_UNIKEY_DECRYPT_FAILED				229	//Decrypt datafailed
#define ERROR_UNIKEY_READ_TIME					230	//Get UniKey time failed
#define ERROR_UNIKEY_WRITE_TIME					231	//Set UniKey time failed
#define ERROR_UNIKEY_WRITE_TIME_MODULE			232	//Write time module error
#define ERROR_UNIKEY_COMPARE_TIME_MODULE		233	//The specific time is before the module°Øs start time
#define ERROR_UNIKEY_TIME_MODULE_NOT_NULL		234	//The real time module is not null, this error is returned when write once flag is set
#define ERROR_UNIKEY_TIME_MODULE_OVERDUR		235	//The specific time is later than the module°Øs end time, or the module is expired
#define ERROR_UNIKEY_ALREADY_LOCKED				236	//Dongle Already Locked (when lock twice or open after lock)
// NetUniKey Error Code
#define NET_UNIEKY_ERROR_BASE				100							// net unikey error base
#define NET_UNIKEY_MEMORY_ERROR				NET_UNIEKY_ERROR_BASE+1		// memory allocation error
#define NET_UNIKEY_SEND_ERROR				NET_UNIEKY_ERROR_BASE+2		// send error
#define NET_UNIEY_RECEIVE_ERROR				NET_UNIEKY_ERROR_BASE+3		// receive error
#define NET_UNIKEY_MESSAGE_WRONG			NET_UNIEKY_ERROR_BASE+4		// communication message is modified
#define NET_UNIKEY_SETUP_SOCKET_ERROR		NET_UNIEKY_ERROR_BASE+5		// setup socket error
#define NET_UNIKEY_CLIENT_EXSIT				NET_UNIEKY_ERROR_BASE+6		// the client already exists, per this mode
#define NET_UNIKEY_TOO_MANY_CLIENT			NET_UNIEKY_ERROR_BASE+7		// the number of client reach the limitation
#define NET_UNIKEY_IN_BLACKLIST				NET_UNIEKY_ERROR_BASE+8		// the client is in the black list
#define NET_UNIKEY_OUT_WHITELIST			NET_UNIEKY_ERROR_BASE+9		// the client is not in the white list
#define NET_UNIKEY_MESSAGE_CHANGE			NET_UNIEKY_ERROR_BASE+10	// the message packet was changed
#define NET_UNIKEY_AREADY_START				NET_UNIEKY_ERROR_BASE+11	// the server has already started
#define NET_UNIKEY_SOCKET_INIT_FAILED		NET_UNIEKY_ERROR_BASE+12	// cannot initialize the socket
#define NET_UNIKEY_SOCKET_BIND_FAILED		NET_UNIEKY_ERROR_BASE+13	// cannot bind the port with the socket
#define NET_UNIKEY_SOCKET_LISTEN_FAILED		NET_UNIEKY_ERROR_BASE+14	// cannot start listening with the socket
#define NET_UNIKEY_START_UDP_SERVER_FAILED	NET_UNIEKY_ERROR_BASE+15	// start udp server failed
#define	NET_UNIKEY_TOO_LONG_MESSAGE			NET_UNIEKY_ERROR_BASE+16	// too long message
#define NET_UNIKEY_NOT_WORKING				NET_UNIEKY_ERROR_BASE+17	// cannot connect remote netunikey server	
#define NET_UNIKEY_DISCARD_BY_SERVER		NET_UNIEKY_ERROR_BASE+18	// the client is discarded by the server


