
//if(!defined(__stdcall)){//rem next 5 line if windows
//#define __stdcall 
//typedef unsigned char  BYTE;
//typedef unsigned short WORD;
//typedef unsigned long  DWORD;
//}else{//else            //rem next 1 line if not windows
#include <windows.h>
//}//endif


#ifdef __cplusplus
extern "C"{
#endif

long __stdcall UniKey_Find(WORD* pHandle, DWORD* pSetting1, DWORD* pSetting2);
long __stdcall UniKey_Find_Next(WORD* pHandle, DWORD* pSetting1, DWORD* pSetting2);
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
long __stdcall UniKey_Get_Module(WORD* pHandle, WORD* pModule, WORD* pValue);
long __stdcall UniKey_Check_Module(WORD* pHandle, WORD* pModule, WORD* pValue, WORD* pDecrease);
long __stdcall UniKey_Module_Decrase(WORD* pHandle, WORD* pModule);
long __stdcall UniKey_Write_Arithmetic(WORD* pHandle, WORD* pStartAddress, BYTE * pBuffer);
long __stdcall UniKey_Calculate1(WORD* pHandle, DWORD* pStartAddress, DWORD* pModule, WORD* pRegisterA, WORD* pRegisterB, WORD* pRegisterC, WORD* pRegisterD); //start, seed, register
long __stdcall UniKey_Calculate2(WORD* pHandle, DWORD* pStartAddress, DWORD* pSeed, WORD* pRegisterA, WORD* pRegisterB, WORD* pRegisterC, WORD* pRegisterD);
long __stdcall UniKey_Calculate3(WORD* pHandle, DWORD* pStartAddress, DWORD* pModule, WORD* pRegisterA, WORD* pRegisterB, WORD* pRegisterC, WORD* pRegisterD);
long __stdcall UniKey_Generate_New_Password(WORD* pHandle, DWORD* pSeed1, WORD* pPassword1, WORD* pPassword2, WORD* pPassword3, WORD* pPassword4);
long __stdcall UniKey_Generate_Key(WORD* pHandle, DWORD* pKeyNumber);
long __stdcall UniKey_Generate_Key_Via_Seed(WORD* handle, DWORD* pKeyNumber,WORD* pSeed1, WORD* pSeed2, WORD* pSeed3, WORD* pSeed4);
long __stdcall UniKey_Encrypt(WORD* pHandle, DWORD* pBufferLength, DWORD* pKeyNumber, BYTE *pBuffer);
long __stdcall UniKey_Decrypt(WORD* pHandle, DWORD* pBufferLength, DWORD* pKeyNumber, BYTE *pBuffer);
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
long __stdcall UniKey_Check_Time_Module(WORD* pHandle, DWORD* pModule, DWORD* pRemainDays, WORD* pYear, WORD* pMonth, WORD* pDay, WORD* pHour);
long __stdcall UniKey_Check_Time_Module_Now(WORD* pHandle, DWORD* pModule,DWORD* pRemainDays, WORD *pRemainHours);
long __stdcall UniKey_Check_Time_Module_Now_PC(WORD* pHandle, DWORD* pModule,DWORD* pRemainDays, WORD *pRemainHours);
long __stdcall UniKey_Get_Module_Start_Time(WORD* pHandle, DWORD* pModule, WORD* pYear, WORD* pMonth, WORD* pDay, WORD* pHour);
long __stdcall UniKey_Get_Module_End_Time(WORD* pHandle, DWORD* pModule, WORD* pYear, WORD* pMonth, WORD* pDay, WORD* pHour);

long __stdcall UniKey_Get_Version(WORD* pHandle, DWORD* lp1);
long __stdcall UniKey_Get_Dongle_Location(WORD* handle, DWORD* lp1);

long __stdcall UniKey_Get_Type(WORD* pHandle, DWORD* type);
#ifdef __cplusplus
} //  extern "C"{
#endif

// Error Code
#define SUCCESS																0					//Success
#define ERROR_UNIKEY_NOT_FOUND					200	//No UniKey dongle
#define ERROR_UNIKEY_INVALID_PASSWORD			201	//Found UniKey dongle, but basic password is wrong
#define ERROR_UNIKEY_INVALID_PASSWORD_OR_ID		202	//Wrong password or UniKey HID
#define ERROR_UNIKEY_SET_SOFTID_FAILED			203	//Set UniKey ID failed
#define ERROR_UNIKEY_INVALID_ADDR_OR_SIZE				204	//Read/Write address or length is wrong
#define ERROR_UNIKEY_UNKNOWN_COMMAND			205	//No such command
#define ERROR_UNIKEY_READ_MEMORY				207	//Read memory failed
#define ERROR_UNIKEY_WRITE_MEMORY				208	//Write memory failed
#define ERROR_UNIKEY_RANDOM						209	//Random number failed
#define ERROR_UNIKEY_SEED						210	//Get seed code failed
#define ERROR_UNIKEY_CALCULATE					211	//Calculate failed
#define ERROR_UNIKEY_NEED_OPEN					212	//Need open dongle before operating dongle
#define ERROR_UNIKEY_OPEN_OVERFLOW				213	//Too many open dongles (>16)
#define ERROR_UNIKEY_NOMORE						214	//No more dongle
#define ERROR_UNIKEY_NEED_FIND			215	//No Find before FindNext
#define ERROR_UNIKEY_MODULE						216	//License module error
#define ERROR_UNIKEY_AR_BAD_COMMAND				217	//Arithmetic instruction Error
#define ERROR_UNIKEY_AR_UNKNOWN_OPCODE			218	//Arithmetic operator Error
#define ERROR_UNIKEY_AR_WRON_GBEGIN				219	//Const number can't use on first arithmetic instruction
#define ERROR_UNIKEY_AR_WRONG_END				220	//Const number can't use on last arithmetic instruction
#define ERROR_UNIKEY_AR_VALUE_OVERFLOW			221	//Const number > 63
#define ERROR_UNIKEY_INVALID_KEY				222	//The key in the key storage is wrong
#define ERROR_UNIKEY_VERIFY_ADV_PASSWORD		223	//Advanced passwords (password3 and passowrd4) not verified
#define ERROR_UNIKEY_INVALID_KEY_STORE			224	//Wrong key storage number
#define ERROR_UNIKEY_GENERATE_NEW_PASSWORD		225	//Generate new password failed
#define ERROR_UNIKEY_READ_UPDATETAG				226	//Read UpdateTag failed
#define ERROR_UNIKEY_WRITE_UPDATETAG			227	//Write UpdateTag failed
#define ERROR_UNIKEY_ENCRYPT_FAILED				228	//Encrypt data failed
#define ERROR_UNIKEY_DECRYPT_FAILED				229	//Decrypt datafailed
#define ERROR_UNIKEY_READ_TIME					230	//Get UniKey time failed
#define ERROR_UNIKEY_WRITE_TIME					231	//Set UniKey time failed
#define ERROR_UNIKEY_WRITE_TIME_MODULE			232	//Write time module error
#define ERROR_UNIKEY_COMPARE_TIME_MODULE		233	//The specific time is before the module¡¯s start time
#define ERROR_UNIKEY_TIME_MODULE_NOT_NULL		234	//The real time module is not null, this error is returned when write once flag is set
#define ERROR_UNIKEY_TIME_MODULE_OVERDUR		235	//The specific time is later than the module¡¯s end time, or the module is expired
#define ERROR_UNIKEY_ALREADY_LOCKED				236	//Dongle Already Locked (when lock twice or open after lock)

// NetUniKey Error Code
#define NET_UNIKEY_ERROR_BASE				100							// net unikey error base
#define NET_UNIKEY_MEMORY_ERROR				NET_UNIKEY_ERROR_BASE+1		// memory allocation error
#define NET_UNIKEY_SEND_ERROR				NET_UNIKEY_ERROR_BASE+2		// send error
#define NET_UNIKEY_RECEIVE_ERROR				NET_UNIKEY_ERROR_BASE+3		// receive error
#define NET_UNIKEY_MESSAGE_WRONG			NET_UNIKEY_ERROR_BASE+4		// communication message is modified
#define NET_UNIKEY_SETUP_SOCKET_ERROR		NET_UNIKEY_ERROR_BASE+5		// setup socket error
#define NET_UNIKEY_CLIENT_EXSIT				NET_UNIKEY_ERROR_BASE+6		// the client already exists, per this mode
#define NET_UNIKEY_TOO_MANY_CLIENT			NET_UNIKEY_ERROR_BASE+7		// the number of client reach the limitation
#define NET_UNIKEY_IN_BLACKLIST				NET_UNIKEY_ERROR_BASE+8		// the client is in the black list
#define NET_UNIKEY_OUT_WHITELIST			NET_UNIKEY_ERROR_BASE+9		// the client is not in the white list
#define NET_UNIKEY_MESSAGE_CHANGE			NET_UNIKEY_ERROR_BASE+10	// the message packet was changed
#define NET_UNIKEY_AREADY_START				NET_UNIKEY_ERROR_BASE+11	// the server has already started
#define NET_UNIKEY_SOCKET_INIT_FAILED		NET_UNIKEY_ERROR_BASE+12	// cannot initialize the socket
#define NET_UNIKEY_SOCKET_BIND_FAILED		NET_UNIKEY_ERROR_BASE+13	// cannot bind the port with the socket
#define NET_UNIKEY_SOCKET_LISTEN_FAILED		NET_UNIKEY_ERROR_BASE+14	// cannot start listening with the socket
#define NET_UNIKEY_START_UDP_SERVER_FAILED	NET_UNIKEY_ERROR_BASE+15	// start udp server failed
#define	NET_UNIKEY_TOO_LONG_MESSAGE			NET_UNIKEY_ERROR_BASE+16	// too long message
#define NET_UNIKEY_NOT_WORKING				NET_UNIKEY_ERROR_BASE+17	// cannot connect remote netunikey server	
#define NET_UNIKEY_DISCARD_BY_SERVER		NET_UNIKEY_ERROR_BASE+18	// the client is discarded by the server


////////////////////////////////////////////////////////////////////////
/////add new code, can use old API UniKey() ; 

// function keywords
#define UNIKEY_FIND					1		// Find UniKey
#define UNIKEY_FIND_NEXT		    2   	// Find next UniKey
#define UNIKEY_LOGON				3 		// Open UniKey 
#define UNIKEY_LOGOFF			    4		// Close UniKey
#define UNIKEY_READ_MEMORY			5		// Read UniKey
#define UNIKEY_WRITE_MEMORY		    6		// Write UniKey
#define UNIKEY_RANDOM		    	7		// Generate Random Number
#define UNIKEY_SEED					8		// Generate Seed Code
#define UNIKEY_WRITE_SOFTID			9		// Write Software ID
#define UNIKEY_READ_SOFTID			10		// Read Software ID
#define UNIKEY_SET_MODULE			11		// Set Module
#define UNIKEY_CHECK_MODULE			12		// Check Module
#define UNIKEY_WRITE_ARITHMETIC		13		// Write Arithmetic
#define UNIKEY_CALCULATE1		    14		// Calculate 1
#define UNIKEY_CALCULATE2		    15		// Calculate 2
#define UNIKEY_CALCULATE3		    16		// Calculate 3
#define UNIKEY_MODULE_DECRASE		17		// Decrease Module Unit
#define UNIKEY_SET_NEW_PASSWORD		18		// Set New Password via a New Seed
#define UNIKEY_GENERATE_KEY			19		// Generate a New Key in specific Key Store
#define UNIKEY_ENCRYPT				20		// Encrypt the Buffer with a Specific Key
#define UNIKEY_DECRYPT				21		// Decrypt the Buffer with a Specific Key
#define UNIKEY_MD5					22		// Make an MD5 Digest for a Certain Content
#define UNIKEY_READ_UPDATETAG		23		// Read UpdateTag from a Specific Key
#define UNIKEY_WRITE_UPDATETAG		24		// Write UpdateTag to a Specific Key
#define UNIKEY_GET_MODULE			25		// p1 [in] Number [p3] out Value

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


//Logon Lock Function
#define UNIKEY_LOCK									41		// Lock a dongle
#define UNIKEY_UNLOCK								42		// Lock a dongle


// Error Code
#define SUCCESS							0	//Success
#define ERROR_NO_UNIKEY					3	//No UniKey dongle
#define ERROR_FOUND_INVALID_PASSWORD	4	//Found UniKey dongle, but Basic passwords are incorrect
#define ERROR_INVALID_PASSWORD_OR_ID	5	//Wrong password or UniKey HID
#define ERROR_SET_SOFTID				6	//Set UniKey ID wrong
#define ERROR_INVALID_ADDR_OR_SIZE		7	//Read/Write address or length is wrong
#define ERROR_UNKNOWN_COMMAND			8	//No such command
#define ERROR_NOTBELEVEL3				9	//Internal Error
#define ERROR_READ_MEMORY				10	//Read Error
#define ERROR_WRITE_MEMORY				11	//Write Error
#define ERROR_RANDOM					12	//Random number Error
#define ERROR_SEED						13	//Seed code Error
#define ERROR_CALCULATE					14	//Calculate Error
#define ERROR_NO_OPEN					15	//No open dongle before operating dongle
#define ERROR_OPEN_OVERFLOW				16	//Too many open dongles (>16)
#define ERROR_NOMORE					17	//No more dongle
#define ERROR_NEED_FIND					18	//No Find before FindNext
#define ERROR_MODULE					19	//License module error
#define ERROR_AR_BAD_COMMAND			20	//Arithmetic instruction Error
#define ERROR_AR_UNKNOWN_OPCODE			21	//Arithmetic operator Error
#define ERROR_AR_WRON_GBEGIN			22	//Const number can't use on first arithmetic instruction
#define ERROR_AR_WRONG_END				23	//Const number can't use on last arithmetic instruction
#define ERROR_AR_VALUE_OVERFLOW			24	//Const number > 63
#define ERROR_TOO_MUCH_THREAD			25	//Too many (>100) threads in the single process open the dongle
#define ERROR_INVALID_KEY				26	//The key in the key storage is wrong
#define ERROR_VERIFY_ADV_PASSWORD		27	//Advanced passwords (password3 and passowrd4) not verified
#define ERROR_INVALID_KEY_STORE			28	//Wrong key storage number
#define ERROR_GENERATE_NEW_PASSWORD		29	//Generate new password Error
#define ERROR_READ_UPDATETAG			30	//Read UpdateTag error
#define ERROR_WRITE_UPDATETAG			31	//Write UpdateTag error
#define ERROR_ENCRYPT_FAILED			32  //Encrypt data error
#define ERROR_DECRYPT_FAILED			33  //Decrypt data error
#define ERROR_READ_TIME					34	//Get UniKey time error
#define ERROR_WRITE_TIME				35	//Set UniKey time error
#define ERROR_WRITE_TIME_MODULE			36	//Write time module error
#define ERROR_COMPARE_TIME_MODULE		37	//The specific time is before the module¡¯s start time
#define ERROR_TIME_MODULE_NOT_NULL		38	//The real time module is not null, this error is returned when write once flag is set
#define ERROR_TIME_MODULE_OVERDUR		39	//The specific time is later than the module¡¯s end time, or the module is expired
#define ERROR_ALREADY_LOCKED			41  //Dongle Already Locked (when lock twice or open after lock)
#define ERROR_RECEIVE_NULL				0x100	//Receive null
#define ERROR_UNKNOWN_SYSTEM			0x102	//Unknown operating system
#define ERROR_UNKNOWN_ERROR				0xffff	//Unknown Error
//**/
//*/
// define the standard API
extern "C" long __stdcall UniKey(WORD Function, WORD* handle, DWORD* lp1, DWORD* lp2, WORD* p1, WORD* p2, WORD* p3, WORD* p4, BYTE* buffer);
// Function,	function type
// handle,		Dongle handle
// lp1..p4,		Dongle variables
// buffer,		buffer pointer

