#ifndef __UNIKEY_H__
#define __UNIKEY_H__

#ifdef _WIN32
#include <windows.h>
#else
#define WORD 	unsigned short
#define DWORD   unsigned int
#define BYTE 	unsigned char
#endif

// 1. API reference
long UniKey_SetNETINILocation(WORD* pHandle, DWORD* pSetting1, DWORD* pSetting2, const char *szINIPath);
long UniKey_Find(WORD* pHandle, DWORD* pSetting1, DWORD* pSetting2);
long UniKey_Find_Next(WORD* pHandle, DWORD* pSetting1, DWORD* pSetting2);

long UniKey_User_Logon(WORD* pHandle, WORD* pPassword1, WORD* pPassword2);
long UniKey_Vender_Logon(WORD* pHandle, WORD* pPassword1, WORD* pPassword2, WORD* pPassword3, WORD* pPassword4);
long UniKey_Vendor_Logon(WORD* pHandle, WORD* pPassword1, WORD* pPassword2, WORD* pPassword3, WORD* pPassword4);
long UniKey_Logoff(WORD* pHandle);

long UniKey_Get_Version(WORD* pHandle, DWORD* pVersion);
long UniKey_Get_Type(WORD* pHandle, DWORD* type);

long UniKey_Lock(WORD* pHandle);
long UniKey_UnLock(WORD* pHandle);

long UniKey_Read_Memory(WORD* pHandle, WORD* pStartAddress, WORD* pBufferLength, BYTE* pBuffer);
long UniKey_Write_Memory(WORD* pHandle, WORD* pStartAddress, WORD* pBufferLength, BYTE* pBuffer);

long UniKey_Random(WORD* pHandle, WORD* pReturn1, WORD* pReturn2, WORD* pReturn3, WORD* pReturn4);
long UniKey_Seed(WORD* pHandle, DWORD* pSeed, WORD* pReturn1, WORD* pReturn2, WORD* pReturn3, WORD* pReturn4);

long UniKey_Write_SoftID(WORD* pHandle, DWORD* pSoftID);
long UniKey_Read_SoftID(WORD* pHandle, DWORD* pSoftID);

long UniKey_Set_Module(WORD* pHandle, WORD* pModule, WORD* pValue, WORD* pDecrease);
long UniKey_Get_Module(WORD* pHandle, WORD* pModule, WORD* pValue);
long UniKey_Check_Module(WORD* pHandle, WORD* pModule, WORD* pValue, WORD* pDecrease);
long UniKey_Module_Decrase(WORD* pHandle, WORD* pModule);
long UniKey_Module_Decrease(WORD* pHandle, WORD* pModule);

long UniKey_Write_Arithmetic(WORD* pHandle, WORD* pStartAddress, BYTE * pBuffer);
long UniKey_Calculate1(WORD* pHandle, DWORD* pStartAddress, DWORD* pModule, WORD* pRegA, WORD* pRegB, WORD* pRegC, WORD* pRegD); //start, seed, register
long UniKey_Calculate2(WORD* pHandle, DWORD* pStartAddress, DWORD* pSeed, WORD* pRegA, WORD* pRegB, WORD* pRegC, WORD* pRegD);
long UniKey_Calculate3(WORD* pHandle, DWORD* pStartAddress, DWORD* pModule, WORD* pRegA, WORD* pRegB, WORD* pRegC, WORD* pRegD);

long UniKey_Generate_New_Password(WORD* pHandle, DWORD* pSeed, WORD* pPassword1, WORD* pPassword2, WORD* pPassword3, WORD* pPassword4);
long UniKey_Generate_Key(WORD* pHandle, DWORD* pKeyNumber);
long UniKey_Generate_Key_Via_Seed(WORD* pHandle, DWORD* pKeyNumber, WORD* pSeed1, WORD* pSeed2, WORD* pSeed3, WORD* pSeed4);
long UniKey_Encrypt(WORD* pHandle, DWORD* pBufferLength, DWORD* pKeyNumber, BYTE *pBuffer);
long UniKey_Decrypt(WORD* pHandle, DWORD* pBufferLength, DWORD* pKeyNumber, BYTE *pBuffer);
long UniKey_MD5(WORD* pHandle, DWORD* pBufferLength, BYTE *pBuffer);

long UniKey_Read_UpdateTag(WORD* pHandle, DWORD* pUpdateTag);
long UniKey_Write_UpdateTag(WORD* pHandle, DWORD* pUpdateTag);


// 2. UniKey Time only API
long UniKey_Get_Time(WORD* pHandle, DWORD* pYear, DWORD* pMonth, WORD* pDay, WORD* pHour, WORD* pMinute, WORD* pSecond);
long UniKey_Set_Time(WORD* pHandle, DWORD* pYear, DWORD* pMonth, WORD* pDay, WORD* pHour, WORD* pMinute, WORD* pSecond);
long UniKey_Set_Time_Now(WORD* pHandle);
long UniKey_Erase_Time_Module(WORD* pHandle, DWORD* pModule);
long UniKey_Set_Time_Module_Start_Time(WORD* pHandle, DWORD* pModule, WORD* pYear, WORD* pMonth, WORD* pDay, WORD* pHour);
long UniKey_Set_Time_Module_Start_Time_Now(WORD* pHandle, DWORD* pModule);
long UniKey_Set_Time_Module_Start_Time_Now_PC(WORD* pHandle, DWORD* pModule);
long UniKey_Set_Time_Module_End_Time(WORD* pHandle, DWORD* pModule, WORD* pYear, WORD* pMonth, WORD* pDay, WORD* pHour);
long UniKey_Set_Time_Module_Duration(WORD* pHandle, DWORD* pModule, DWORD* pYear, WORD* pDay);
long UniKey_Check_Time_Module(WORD* pHandle, DWORD* pModule, DWORD* pRemainDays, WORD* pYear, WORD* pMonth, WORD* pDay, WORD* pHour);
long UniKey_Check_Time_Module_Now(WORD* pHandle, DWORD* pModule, DWORD* pRemainDays, WORD *pRemainHours);
long UniKey_Check_Time_Module_Now_PC(WORD* pHandle, DWORD* pModule, DWORD* pRemainDays, WORD *pRemainHours);
long UniKey_Get_Module_Start_Time(WORD* pHandle, DWORD* pModule, WORD* pYear, WORD* pMonth, WORD* pDay, WORD* pHour);
long UniKey_Get_Module_End_Time(WORD* pHandle, DWORD* pModule, WORD* pYear, WORD* pMonth, WORD* pDay, WORD* pHour);

// 3¡¢Network Functions
long UniKey_Get_Dongle_Location(WORD* pHandle, DWORD* pIPAddress);
long UniKey_Get_Cli_Num(WORD* pHandle, DWORD* cnt);
long UniKey_Get_Max_Num(WORD* pHandle, WORD* cnt);
long UniKey_Set_Max_Num(WORD *pHandle, WORD *cnt);

// 4¡¢define the standard API
long UniKey(WORD Function, WORD* handle, DWORD* lp1, DWORD* lp2, WORD* p1, WORD* p2, WORD* p3, WORD* p4, BYTE* buffer);


// function keywords
#define UNIKEY_FIND									1		// Find UniKey
#define UNIKEY_FIND_NEXT		    				2   	// Find next UniKey
#define UNIKEY_LOGON								3 		// Open UniKey 
#define UNIKEY_LOGOFF			    				4		// Close UniKey
#define UNIKEY_READ_MEMORY							5		// Read UniKey
#define UNIKEY_WRITE_MEMORY		    				6		// Write UniKey
#define UNIKEY_RANDOM		    					7		// Generate Random Number
#define UNIKEY_SEED									8		// Generate Seed Code
#define UNIKEY_WRITE_SOFTID							9		// Write Software ID
#define UNIKEY_READ_SOFTID							10		// Read Software ID
#define UNIKEY_SET_MODULE							11		// Set Module
#define UNIKEY_CHECK_MODULE							12		// Check Module
#define UNIKEY_WRITE_ARITHMETIC						13		// Write Arithmetic
#define UNIKEY_CALCULATE1		    				14		// Calculate 1
#define UNIKEY_CALCULATE2		    				15		// Calculate 2
#define UNIKEY_CALCULATE3		    				16		// Calculate 3
#define UNIKEY_MODULE_DECRASE						17		// Decrease Module Unit
#define UNIKEY_MODULE_DECREASE						17		// Decrease Module Unit
#define UNIKEY_SET_NEW_PASSWORD						18		// Set New Password via a New Seed
#define UNIKEY_GENERATE_KEY							19		// Generate a New Key in specific Key Store
#define	UNIKEY_SET_KEY								222		// set/write the 128-bit key
#define UNIKEY_ENCRYPT								20		// Encrypt the Buffer with a Specific Key
#define UNIKEY_DECRYPT								21		// Decrypt the Buffer with a Specific Key
#define UNIKEY_MD5									22		// Make an MD5 Digest for a Certain Content
#define UNIKEY_READ_UPDATETAG						23		// Read UpdateTag from a Specific Key
#define UNIKEY_WRITE_UPDATETAG						24		// Write UpdateTag to a Specific Key
#define UNIKEY_GET_MODULE							25		// p1 [in] Number [p3] out Value

//Real Time Clock Functions [if no comment, (lp1 = module index)]
#define UNIKEY_GET_TIME								26		// read rtc time (lp1,lp2,p1,p2,p3,p4 = year,month,day,hour,minute,second)
#define UNIKEY_SET_TIME								27		// write rtc time (lp1,lp2,p1,p2,p3,p4 = year,month,day,hour,minute,second)
#define UNIKEY_SET_TIME_NOW							28		// write rtc time use host time
#define UNIKEY_ERASE_TIME_MODULE					29		// ERASE TIME MODULE to NULL,
#define UNIKEY_SET_TIME_MODULE_START_TIME			30		// write rtc time module start time(p1,p2,p3,p4 = year,month,day,hour)
#define UNIKEY_SET_TIME_MODULE_START_TIME_NOW		31		// write rtc time module start time use dongle time
#define UNIKEY_SET_TIME_MODULE_START_TIME_NOW_PC	32		// write rtc time module start time use host time 
#define UNIKEY_SET_TIME_MODULE_END_TIME				33		// write rtc time module end time (p1,p2,p3,p4 = year,month,day,hour)
#define UNIKEY_SET_TIME_MODULE_DURATION				34		// write rtc time module duration (lp2,p1 = day,hour)=24*day+hour
#define UNIKEY_CHECK_TIME_MODULE					35		// check if a time >START_TIME and the time < END_TIME(or START_TIME+DURATION) (p1,p2,p3,p4 = year,month,day,hour)
#define UNIKEY_CHECK_TIME_MODULE_NOW				36		// check if now >START_TIME and now < END_TIME(or START_TIME+DURATION) use dongle time
#define UNIKEY_CHECK_TIME_MODULE_NOW_PC				37		// check if now >START_TIME and now < END_TIME(or START_TIME+DURATION) use host time
#define UNIKEY_GET_MODULE_START_TIME				38		// get module start time
#define UNIKEY_GET_MODULE_END_TIME					39		// get module end time

#define UNIKEY_LOCK									41		// Lock a dongle
#define UNIKEY_UNLOCK								42		// Lock a dongle

//Unikey Type
#define UNIKEY_GET_TYPE								100		// get the Unikey type 
#define UNIKEY_TYPE_TIME							101		// TIME_UNIKEY
#define UNIKEY_TYPE_PRO								102		// PRO_UNIKEY
#define UNIKEY_TYPE_STD								103		// STD_UNIKEY 

// Network Function
#define NET_UNIKEY_SET_NUM_CLIENT					225 	// set the number of client for netunikey
#define NET_UNIKEY_GET_NUM_CLIENT					226 	// get the number of client for netunikey

#define UNKEY_GET_CLI_NUM							101		//get cli num now
#define UNKEY_GET_MAX_NUM							226		//GET MAX NUM

// Error Codes
#define SUCCESS										0	//Success
#define ERROR_UNIKEY_NOT_FOUND						200	//No UniKey Dongle
#define ERROR_UNIKEY_INVALID_PASSWORD				201	//Found UniKey Dongle, But Basic Password Is Wrong
#define ERROR_UNIKEY_INVALID_PASSWORD_OR_ID			202	//Wrong Password Or UniKey HID
#define ERROR_UNIKEY_SET_SOFTID_FAILED				203	//Set UniKey ID Failed
#define ERROR_UNIKEY_INVALID_ADDR_OR_SIZE			204	//Read/Write Address Or Length Is Wrong
#define ERROR_UNIKEY_UNKNOWN_COMMAND				205	//No Such Command
#define ERROR_UNIKEY_NOTBELEVEL3                    206 // Internal Error
#define ERROR_UNIKEY_READ_MEMORY					207	//Read Memory Failed
#define ERROR_UNIKEY_WRITE_MEMORY					208	//Write Memory Failed
#define ERROR_UNIKEY_RANDOM							209	//Random Number Failed
#define ERROR_UNIKEY_SEED							210	//Get Seed Code Failed
#define ERROR_UNIKEY_CALCULATE						211	//Calculate Failed
#define ERROR_UNIKEY_NEED_OPEN						212	//Need Open Dongle Before Operating Dongle
#define ERROR_UNIKEY_OPEN_OVERFLOW					213	//Too Many Open Dongles (>16)
#define ERROR_UNIKEY_NOMORE							214	//No More Dongle
#define ERROR_UNIKEY_NEED_FIND						215	//No Find Before FindNext
#define ERROR_UNIKEY_MODULE							216	//License Module Error
#define ERROR_UNIKEY_AR_BAD_COMMAND					217	//Arithmetic Instruction Error
#define ERROR_UNIKEY_AR_UNKNOWN_OPCODE				218	//Arithmetic Operator Error
#define ERROR_UNIKEY_AR_WRONG_BEGIN					219	//Const Number Can't Use On First Arithmetic Instruction
#define ERROR_UNIKEY_AR_WRONG_END					220	//Const Number Can't Use On Last Arithmetic Instruction
#define ERROR_UNIKEY_AR_VALUE_OVERFLOW				221	//Const Number > 63
#define ERROR_UNIKEY_INVALID_KEY					222	//The Key In The Key Storage Is Wrong
#define ERROR_UNIKEY_VERIFY_ADV_PASSWORD			223	//Advanced Passwords (Password3 and Passowrd4) Not Verified
#define ERROR_UNIKEY_INVALID_KEY_STORE				224	//Wrong Key Storage Number
#define ERROR_UNIKEY_GENERATE_NEW_PASSWORD			225	//Generate New Password Failed
#define ERROR_UNIKEY_READ_UPDATETAG					226	//Read UpdateTag Failed
#define ERROR_UNIKEY_WRITE_UPDATETAG				227	//Write UpdateTag Failed
#define ERROR_UNIKEY_ENCRYPT_FAILED					228	//Encrypt Data Failed
#define ERROR_UNIKEY_DECRYPT_FAILED					229	//Decrypt Data Failed
#define ERROR_UNIKEY_READ_TIME						230	//Get UniKey Time Failed
#define ERROR_UNIKEY_WRITE_TIME						231	//Set UniKey Time Failed
#define ERROR_UNIKEY_WRITE_TIME_MODULE				232	//Write Time Module Error
#define ERROR_UNIKEY_COMPARE_TIME_MODULE			233	//The Specific Time Is Before The Module¡¯s Start Time
#define ERROR_UNIKEY_TIME_MODULE_NOT_NULL			234	//The Real Time Module Is Not Null, This Error is returned when write once flag is set
#define ERROR_UNIKEY_TIME_MODULE_OVERDUR			235	//The Specific Time Is Later Than The Module's End Time, Or The Module Is Expired
#define ERROR_UNIKEY_ALREADY_LOCKED					236	//Dongle Already Locked (When Lock Twice Or Open After Lock)

// UniKey Drive Special Error Codes
#define ERROR_UNIKEY_MAX_USERS						237 //Dongle Already Max Users Logoned 
#define ERROR_UNIKEY_MAX_KEYS						238 //Dongle Already Max Keys, Need To Delete And The Regenerate  
#define ERROR_UNIKEY_KEY_INDEX						239 //Dongle Over Keyindex, No Key To  Delete
#define ERROR_UNIKEY_FS_FILE_NAME					240	//Wrong Or Invalid File Name 
#define ERROR_UNIKEY_FS_NO_FILE						241	//No Such File Name
#define ERROR_UNIKEY_FS_FILE_OFFSET					242	//Offset Of File Error
#define ERROR_UNIKEY_FS_UNKONW						243	//Unknown Error
#define ERROR_UNIKEY_FS_NO_MEMORY					244	//Not Enough Free Memory
#define ERROR_UNIKEY_FS_FILE_EXIST					245	//File Already Existed

#define ERROR_UNIKEY_FS_ERR_SYS_UNINIT				246	//File Sys Is Not Initialized
#define ERROR_UNIKEY_FS_ERR_OPEN_FILE				247	//Can't Open File
#define ERROR_UNIKEY_NO_ENCYYPT						248	//No Secure Drive
#define ERROR_UNIKEY_PASSWORD						249	//Password Error
#define ERROR_UNIKEY_USERLOCK						250	//User Has Been Locked
#define ERROR_UNIKEY_LOGOUT							251	//ERRO_LOGOUT
#define ERROR_UNIKEY_UNKNOW							252	//ERRO_UNKNOW

#define ERROR_UNIKEY_WRITE_ARITHMETIC               253 //Dongle Write Arithmetic is ERROR
#define ERROR_UNIKEY_PARAMETER                      254
#define ERROR_UNIKEY_TOO_MUCH_THREAD                255 //Too many (>100) threads in the single process open the dongle
#define ERROR_UNIKEY_GET_TYPE		                256

//add by liuzq 2015
#define ERROR_UNIKEY_FILE_LOCK_OPEN	                260	//open lock file error
#define ERROR_UNIKEY_FILE_LOCK_CLOSE	            261	//close lock file error


// NetUniKey Error Codes (Network Function Error Code)*/
#define NET_UNIKEY_ERROR_BASE						100							// NetUniKey Error Base
#define NET_UNIKEY_MEMORY_ERROR						NET_UNIKEY_ERROR_BASE + 1	// Memory Allocation Error
#define NET_UNIKEY_SEND_ERROR						NET_UNIKEY_ERROR_BASE + 2	// Send Error
#define NET_UNIKEY_RECEIVE_ERROR					NET_UNIKEY_ERROR_BASE + 3	// Receive Error
#define NET_UNIKEY_MESSAGE_WRONG					NET_UNIKEY_ERROR_BASE + 4	// Communication Message Is Modified
#define NET_UNIKEY_SETUP_SOCKET_ERROR				NET_UNIKEY_ERROR_BASE + 5	// Setup Socket Error
#define NET_UNIKEY_CLIENT_EXSIT						NET_UNIKEY_ERROR_BASE + 6	// The Client Already Exists, Per This Mode
#define NET_UNIKEY_TOO_MANY_CLIENT					NET_UNIKEY_ERROR_BASE + 7	// The Number Of Client Reach The Limitation
#define NET_UNIKEY_IN_BLACKLIST						NET_UNIKEY_ERROR_BASE + 8	// The Client Is In The Black List
#define NET_UNIKEY_OUT_WHITELIST					NET_UNIKEY_ERROR_BASE + 9	// The Client Is Not In The White List
#define NET_UNIKEY_MESSAGE_CHANGE					NET_UNIKEY_ERROR_BASE + 10	// The Message Packet Was Changed
#define NET_UNIKEY_AREADY_START						NET_UNIKEY_ERROR_BASE + 11	// The Server Has Already Started
#define NET_UNIKEY_SOCKET_INIT_FAILED				NET_UNIKEY_ERROR_BASE + 12	// Cannot Initialize The Socket
#define NET_UNIKEY_SOCKET_BIND_FAILED				NET_UNIKEY_ERROR_BASE + 13	// Cannot Bind The Port With The Socket
#define NET_UNIKEY_SOCKET_LISTEN_FAILED				NET_UNIKEY_ERROR_BASE + 14	// Cannot Start Listening With The Socket
#define NET_UNIKEY_START_UDP_SERVER_FAILED			NET_UNIKEY_ERROR_BASE + 15	// Start Udp Server Failed
#define	NET_UNIKEY_TOO_LONG_MESSAGE					NET_UNIKEY_ERROR_BASE + 16	// Too Long Message
#define NET_UNIKEY_NOT_WORKING						NET_UNIKEY_ERROR_BASE + 17	// Cannot Connect Remote Netunikey Server	
#define NET_UNIKEY_DISCARD_BY_SERVER				NET_UNIKEY_ERROR_BASE + 18	// The Client Is Discarded By The Server
#define NET_UNIKEY_SERVER_RESOURCE_INADEQUACY		NET_UNIKEY_ERROR_BASE + 19	// by lzm
#define NET_UNIKEY_INIFILE_NOT_EXISTS				NET_UNIKEY_ERROR_BASE + 20  // ZhaoHJ: 2015-08-13, INI file not exists


#endif // #ifndef __UNIKEY_H__