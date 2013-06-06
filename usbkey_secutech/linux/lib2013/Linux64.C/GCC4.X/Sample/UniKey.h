// MFC declare
#define WORD 	unsigned short
#define DWORD unsigned long
#define BYTE 	unsigned char

#define MemorySize 4096
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
#define UNIKEY_CHECK_TIME_MODULE_NOW				36		// check if mow >START_TIME and now < END_TIME(or START_TIME+DURATION) use dongle time
#define UNIKEY_CHECK_TIME_MODULE_NOW_PC				37		// check if mow >START_TIME and now < END_TIME(or START_TIME+DURATION) use host time
//Logon Lock Function



// Error Code
#define SUCCESS							0	//Success
/*
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
#define EEROR_GENERATE_NEW_PASSWORD		29	//Generate new password Error
#define ERROR_READ_UPDATETAG			30	//Read UpdateTag error
#define ERROR_WRITE_UPDATETAG			31	//Write UpdateTag error
#define ERROR_ENCRYPT_FAILED			32  //Encrypt data error
#define ERROR_DECRYPT_FAILED			33  //Decrypt data error
#define ERROR_READ_TIME					34	//Read Error
#define ERROR_WRITE_TIME				35	//Write Error
#define ERROR_WRITE_TIME_MODULE			36	//Read Error
#define ERROR_COMPARE_TIME_MODULE		37	//Write Error
#define ERROR_TIME_MODULE_NOT_NULL		38	//Write Error
#define ERROR_TIME_MODULE_OVERDUR		39	//Write Error
#define ERROR_ALREADY_LOCKED			41  //Dongle Already Locked (when lock twice or open after lock)
#define ERROR_RECEIVE_NULL				0x100	//Receive null
#define ERROR_UNKNOWN_SYSTEM			0x102	//Unknown operating system
#define ERROR_UNKNOWN_ERROR				0xffff	//Unknown Error
*/
#define ERROR_NO_UNIKEY					200	//No UniKey dongle
#define ERROR_FOUND_INVALID_PASSWORD	201	//Found UniKey dongle, but Basic passwords are incorrect
#define ERROR_INVALID_PASSWORD_OR_ID	202	//Wrong password or UniKey HID
#define ERROR_SET_SOFTID				203	//Set UniKey ID wrong
#define ERROR_INVALID_ADDR_OR_SIZE		204	//Read/Write address or length is wrong
#define ERROR_UNKNOWN_COMMAND			205	//No such command
#define ERROR_NOTBELEVEL3				206	//Internal Error
#define ERROR_READ_MEMORY				207	//Read Error
#define ERROR_WRITE_MEMORY				208	//Write Error
#define ERROR_RANDOM					209	//Random number Error
#define ERROR_SEED						210	//Seed code Error
#define ERROR_CALCULATE					211	//Calculate Error
#define ERROR_NO_OPEN					212	//No open dongle before operating dongle
#define ERROR_OPEN_OVERFLOW				213	//Too many open dongles (>16)
#define ERROR_NOMORE					214	//No more dongle
#define ERROR_NEED_FIND					215	//No Find before FindNext
#define ERROR_MODULE					216	//License module error
#define ERROR_AR_BAD_COMMAND			217	//Arithmetic instruction Error
#define ERROR_AR_UNKNOWN_OPCODE			218	//Arithmetic operator Error
#define ERROR_AR_WRON_GBEGIN			219	//Const number can't use on first arithmetic instruction
#define ERROR_AR_WRONG_END				220	//Const number can't use on last arithmetic instruction
#define ERROR_AR_VALUE_OVERFLOW			221	//Const number > 63
#define ERROR_TOO_MUCH_THREAD			280	//Too many (>100) threads in the single process open the dongle
#define ERROR_INVALID_KEY				222	//The key in the key storage is wrong
#define ERROR_VERIFY_ADV_PASSWORD		223	//Advanced passwords (password3 and passowrd4) not verified
#define ERROR_INVALID_KEY_STORE			224	//Wrong key storage number
#define EEROR_GENERATE_NEW_PASSWORD		225	//Generate new password Error
#define ERROR_READ_UPDATETAG			226	//Read UpdateTag error
#define ERROR_WRITE_UPDATETAG			227	//Write UpdateTag error
#define ERROR_ENCRYPT_FAILED			228  //Encrypt data error
#define ERROR_DECRYPT_FAILED			229  //Decrypt data error
#define ERROR_READ_TIME					230	//Get UniKey time error
#define ERROR_WRITE_TIME				231	//Set UniKey time error
#define ERROR_WRITE_TIME_MODULE			232	//Write time module error
#define ERROR_COMPARE_TIME_MODULE		233	//The specific time is before the module¡¯s start time
#define ERROR_TIME_MODULE_NOT_NULL		234	//The real time module is not null, this error is returned when write once flag is set
#define ERROR_TIME_MODULE_OVERDUR		235	//The specific time is later than the module¡¯s end time, or the module is expired
#define ERROR_ALREADY_LOCKED			236  //Dongle Already Locked (when lock twice or open after lock)
#define ERROR_RECEIVE_NULL				0x100	//Receive null
#define ERROR_UNKNOWN_SYSTEM			0x102	//Unknown operating system
#define ERROR_UNKNOWN_ERROR				0xffff	//Unknown Error




// define the standard API

long  UniKey(WORD Function, WORD* handle, DWORD* lp1, DWORD* lp2, WORD* p1, WORD* p2, WORD* p3, WORD* p4, BYTE* buffer);
// Function,	function type
// handle,		Dongle handle
// lp1..p4,		Dongle variables
// buffer,		buffer pointer
