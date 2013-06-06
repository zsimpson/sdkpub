#include <windows.h>

// Function Code
#define UNIKEY_FIND			1	// Find UniKey                                              
#define UNIKEY_FIND_NEXT		2   	// Find next UniKey                                         
#define UNIKEY_LOGON			3 	// Open UniKey                                              
#define UNIKEY_LOGOFF		   	4	// Close UniKey                                             
#define UNIKEY_READ_MEMORY    		5	// Read UniKey                                              
#define UNIKEY_WRITE_MEMORY    		6	// Write UniKey                                             
#define UNIKEY_RANDOM	    		7	// Generate Random Number                                   
#define UNIKEY_SEED		    	8	// Generate Seed Code                                       
#define UNIKEY_WRITE_SOFTID		9	// Write Software ID                                        
#define UNIKEY_READ_SOFTID		10	// Read Software ID                                         
#define UNIKEY_SET_MODULE		11	// Set license module                                       
#define UNIKEY_CHECK_MODULE		12	// Check license module                                     
#define UNIKEY_WRITE_ARITHMETIC		13	// Write Arithmetic                                         
#define UNIKEY_CALCULATE1	    	14	// Calculate 1                                              
#define UNIKEY_CALCULATE2	    	15	// Calculate 2                                              
#define UNIKEY_CALCULATE3	    	16	// Calculate 3                                              
#define UNIKEY_MODULE_DECRASE		17	// Decrease license module Unit                             
#define UNIKEY_SET_NEW_PASSWORD		18	// Set New Password via a New Seed                          
#define UNIKEY_GENERATE_KEY		19	// Generate a New Key in specific Key Store                 
#define UNIKEY_ENCRYPT			20	// Encrypt the Buffer with a Specific Key                   
#define UNIKEY_DECRYPT			21	// Decrypt the Buffer with a Specific Key	                
#define UNIKEY_MD5			22	// Make an MD5 Digest for a Certain Content	                
#define UNIKEY_READ_UPDATETAG		23	// Read UpdateTag from a Specific Key                       
#define UNIKEY_WRITE_UPDATETAG		24	// Write UpdateTag to a Specific Key                        


// Error Code
#define SUCCESS				0	//Success
#define ERROR_NO_UNIKEY			3	//No UniKey dongle
#define ERROR_FOUND_INVALID_PASSWORD		4	//Found UniKey dongle, but Basic passwords are incorrect
#define ERROR_INVALID_PASSWORD_OR_ID	5	//Wrong password or UniKey HID
#define ERROR_SET_SOFTID		6	//Set UniKey ID wrong
#define ERROR_INVALID_ADDR_OR_SIZE	7	//Read/Write address or length is wrong
#define ERROR_UNKNOWN_COMMAND		8	//No such command
#define ERROR_NOTBELEVEL3		9	//Internal Error
#define ERROR_READ			10	//Read Error
#define ERROR_WRITE			11	//Write Error
#define ERROR_RANDOM			12	//Random number Error
#define ERROR_SEED			13	//Seed code Error
#define ERROR_CALCULATE			14	//Calculate Error
#define ERROR_NO_OPEN			15	//No open dongle before operating dongle
#define ERROR_OPEN_OVERFLOW		16	//Too many open dongles (>16)
#define ERROR_NOMORE			17	//No more dongle
#define ERROR_NEED_FIND			18	//No Find before FindNext
#define ERROR_MODULE_DECRASE		19	//MODULE_DECRASE Error
#define ERROR_AR_BAD_COMMAND		20	//Arithmetic instruction Error
#define ERROR_AR_UNKNOWN_OPCODE		21	//Arithmetic operator Error
#define ERROR_AR_WRON_GBEGIN		22	//Const number can't use on first arithmetic instruction
#define ERROR_AR_WRONG_END		23	//Const number can't use on last arithmetic instruction
#define ERROR_AR_VALUE_OVERFLOW		24	//Const number > 63
#define ERROR_TOO_MUCH_THREAD		25	//Too many (>100) threads in the single process open the dongle
#define ERROR_INVALID_KEY		26	//The key in the key storage is wrong
#define ERROR_VERIFY_ADV_PASSWORD	27	//Advanced passwords (password3 and passowrd4) not verified
#define ERROR_INVALID_KEY_STORE		28	//Wrong key storage number
#define EEROR_GENERATE_NEW_PASSWORD	29	//Generate new password Error
#define ERROR_READ_UPDATETAG		30	//Read UpdateTag Error
#define ERROR_WRITE_UPDATETAG		31	//Write UpdateTag Error
#define ERROR_RECEIVE_NULL		0x100	//Receive null
#define ERROR_UNKNOWN_SYSTEM		0x102	//Unknown operating system
#define ERROR_UNKNOWN_ERROR		0xffff	//Unknown Error


/* Function Decryption

1.Find a UniKey dongle (UNIKEY_FIND)

Description
To check if a specific UniKey is attached to the USB port.  

Parameters
Parameter	Meaning
function	[in]UNIKEY_FIND
*p1		[in]Password  1
*p2		[in]Password  2
*p3		[in]Password  3 (optional)
*p4		[in]Password  4 (optional)
*lp1		[out] Hardware ID

Return values
Marco			Value	Meaning
SUCCESS			0	Success
ERROR_NO_UniKey		3	No UniKey dongle
ERROR_INVALID_PASSWORD	4	Found UniKey dongle, but Basic passwords are incorrect
ERROR_UNKNOWN_SYSTEM	0x102	Unknown operating system


2.Find the Next UniKey dongle (UNIKEY_FIND_NEXT)

Description
To check if another UniKey is attached to the USB port.

Parameters
Parameter	Meaning
function	[in]UNIKEY_FIND_NEXT
*p1		[in]Password  1
*p2		[in]Password  2
*p3		[in]Password  3 (optional)
*p4		[in]Password  4 (optional)
*lp1		[out] Hardware ID

Return values
Marco			Value	Meaning
SUCCESS			0	Success
ERROR_NO_UniKey		3	No UniKey dongle
ERROR_INVALID_PASSWORD	4	Found UniKey dongle, but Basic passwords are incorrect
ERROR_NOMORE		17	No more dongle
ERROR_NEED_FIND		18	No Find before FindNext


3.Open the UniKey dongle (UNIKEY_LOGON)

Description 
To open a UniKey dongle with specified passwords or hardware ID.  

Parameters
Parameter	Meaning
function	[in]UNIKEY_LOGON
*p1		[in]Password  1
*p2		[in]Password  2
*p3		[in]Password  3 (optional)
*p4		[in]Password  4 (optional)
*lp1		[in]Hardware ID(optional)
*handle		[out]Dongle handle

Return values
Marco				Value	Meaning
SUCCESS				0	Success
ERROR_NO_UniKey			3	No UniKey dongle
ERROR_INVALID_PASSWORD		4	Found UniKey dongle, but Basic passwords are incorrect
ERROR_INVALID_PASSWORD_OR_ID	5	Wrong password or UniKey HID
ERROR_OPEN_OVERFLOW		16	Too many open dongles (>16)
ERROR_TOO_MUCH_THREAD		25	Too many (>100) threads in the single process open the dongle


4.Close the UniKey dongle (UNIKEY_LOGOFF)

Description
To close a UniKey dongle with a specific handle.

Parameters
Parameter	Meaning
function	[in] UNIKEY_LOGOFF
*handle		[in] Dongle handle

Return 	values
Marco		Value	Meaning
SUCCESS		0	Success
ERROR_NO_UniKey	3	No UniKey dongle
ERROR_NO_OPEN	15	No open dongle before operating dongle


5.Read the UniKey dongle (UNIKEY_READ_MEMORY)

Description 
To read the contents of the Memory.  

Parameters
Parameter	Meaning
function	[in] UNIKEY_READ_MEMORY
*handle		[in] Dongle handle
*p1		[in]Offset of Memory
*p2		[in] Number of bytes to read
buffer		[out] Pointer to the buffer containing the data to be read

Return values
Marco				Value	Meaning
SUCCESS				0	Success
ERROR_INVALID_ADDR_OR_SIZE	7	Read/Write address or length is wrong
ERROR_READ			10	Read Error
ERROR_NO_OPEN			15	No open dongle before operating dongle


6.Write to the UniKey dongle (UNIKEY_WRITE_MEMORY)

Description
To write data to the memory

Parameters
Parameter	Meaning
function	[in] UNIKEY_WRITE_MEMORY
*handle		[in] Dongle handle
*p1		[in] Offset of the memory
*p2		[in] Number of bytes to write
buffer		[in] Pointer to the buffer containing the data to be written

Return values
Marco				Value	Meaning
SUCCESS				0	Success
ERROR_INVALID_ADDR_OR_SIZE	7	Read/Write address or length is wrong
ERROR_WRITE			11	Write Error
ERROR_NO_OPEN			15	No open dongle before operating dongle
ERROR_VERIFY_ADV_PASSWORD	27	Advanced passwords (password3 and passowrd4) not verified

Note: To write the last 2k memory, you need verify all the 4 passwords to get the full permission to the dongle. 


7. Generate a Random Number (UNIKEY_RANDOM)

Description
To generate a random number from the dongle.

Parameters
Parameter	Meaning
function	[in] UNIKEY_RANDOM
*handle		[in] Dongle handle
*p1		[out] Random number

Return values	
Marco		Value	Meaning
SUCCESS		0	Success
ERROR_NO_OPEN	15	No open dongle before operating dongle
ERROR_RANDOM	12	Random number Error


8. Generate Seed Code Return Values (UNIKEY_SEED)

Description
To get return codes from the input of a seed code.

Parameters
Parameter	Meaning
function	[in] UNIKEY_SEED
*handle		[in] Dongle handle
*lp1		[in] Seed Code
*p1		[out] Return Code 1
*p2		[out] Return Code 2
*p3		[out] Return Code 3
*p4		[out] Return Code 4

Return values
Marco		Value	Meaning
SUCCESS		0	Success
ERROR_NO_OPEN	15	No open dongle before operating dongle
ERROR_SEED	13	Seed code Error


9. Write the Soft ID (UNIKEY_WRITE_SOFTID)

Description 
To write the user defined SoftID.

Parameters	
Parameter	Meaning
function	[in] UNIKEY_WRITE_SOFTID
*handle		[in] Dongle handle
*lp1		[in] Soft ID

Return values
Marco		Value	Meaning
SUCCESS		0	Success
ERROR_NO_OPEN	15	No open dongle before operating dongle
ERROR_SET_ID	6	Set UniKey ID wrong


10. Read Soft ID (UNIKEY_READ_SOFTID)

Description
To read the user defined SoftID.

Parameters	
Parameter	Meaning
function	[in] UNIKEY_READ_SOFTID
*handle		[in] Dongle handle
*lp1		[out] Soft ID

Return values	
Marco		Value	Meaning
SUCCESS		0	Success
ERROR_NO_OPEN	15	No open dongle before operating dongle


11. Set a UniKey license license module (UNIKEY_SET_MODULE)

Description
To write a value to a specific UniKey license license module and set the Decrement attribute. 

Parameters	
Parameter	Meaning
function	[in] UNIKEY_SET_MODULE
*handle		[in] Dongle handle
*p1		[in] license license module Number
*p2		[in] license license module Unit Value
*p3		[in] If decreasing is allowed (1 = allowed, 0 = not allowed)

Return values
Marco			Value	Meaning
SUCCESS			0	Success
ERROR_NO_OPEN		15	No open dongle before operating dongle
ERROR_MODULE_DECRASE	19	MODULE_DECRASE Error

Remarks
A successful operation will result in license license module unit # "*p1" storing value "*p2" and the Decrement attribute set to "0" or "1". 


12. Check a UniKey license license module (UNIKEY_CHECK_MODULE)

Description
To read the attributes of a specific UniKey license license module.

Parameters	
Parameter	Meaning
function	[in] UNIKEY_CHECK_MODULE
*handle		[in] Dongle handle
*p1		[in] license license module Number
*p2		[out] Validity (1 = license license module value is not zero)
*p3		[out] Decrement attribute (1 = license license module can be decreased)


Return values
Marco			Value	Meaning
SUCCESS			0	Success
ERROR_NO_OPEN		15	No open dongle before operating dongle
ERROR_MODULE_DECRASE	19	MODULE_DECRASE Error

Remarks
A successful operation will result in "*p2" populated in the value from the Validity (1 = license module value is not zero), and "*p3" populated with the value from the Decrement attribute (1 = license module can be decreased). ÐÞ¸Ä£¡


13. Write Arithmetic (UNIKEY_WRITE_ARITHMETIC)

Description
To write user-defined mathematical algorithms.  

Parameters 	
Parameter	Meaning
function	[in] UNIKEY_WRITE_ARITHMETIC
*handle		[in] Dongle handle
*p1		[in] Offset of first instruction
buffer		[in] Pointer to the algorithm command string

Return values
Marco			Value	Meaning
SUCCESS			0	Success
ERROR_NO_OPEN		15	No open dongle before operating dongle
ERROR_AR_BAD_COMMAND	20	Arithmetic instruction Error
ERROR_AR_UNKNOWN_OPCODE	21	Arithmetic operator Error
ERROR_AR_WRON_GBEGIN	22	Const number can't use on first arithmetic instruction
ERROR_AR_WRONG_END	23	Const number can't use on last arithmetic instruction
ERROR_AR_VALUE_OVERFLOW	24	Const number > 63

Remarks	
A successful operation will result in the user-defined algorithm populated with the algorithm command string from the buffer.


14.  Calculate 1 (UNIKEY_CALCULATE1)

Description
To return the results of a calculation performed in UniKey, using input provided by the developer and the CALCULATE1 function.

Parameters	
Parameter	Meaning
function	[in] CALCULATE1
*handle		[in] Dongle handle
*lp1		[in] Start point of calculation
*lp2		[in] license module number
*p1		[in, out] Register A
*p2		[in, out] Register B
*p3		[in, out] Register C
*p4		[in, out] Register D

Return values
Marco			Value	Meaning
SUCCESS			0	Success
ERROR_RANDOM		12	Random number Error
ERROR_CALCULATE		14	Calculate Error
ERROR_NO_OPEN		15	No open dongle before operating dongle
ERROR_AR_BAD_COMMAND	20	Arithmetic instruction Error
ERROR_AR_UNKNOWN_OPCODE	21	Arithmetic operator Error
ERROR_AR_WRON_GBEGIN	22	Const number can't use on first arithmetic instruction
ERROR_AR_WRONG_END	23	Const number can't use on last arithmetic instruction
ERROR_AR_VALUE_OVERFLOW	24	Const number > 63

Remarks
When the calculation starts, the values of other internal registers are listed in the table below.
Internal Register	Meaning
E			HiWord of hardware ID 
F			LoWord of hardware ID 
G			Value stored in license module *lp2
H			Random number 

Examples
If the internal algorithm is A = B + C, 
Then the call result is *p1 = *p2 + *p3. 
For example: The internal algorithm is A = A + G,
If *p1 = 0, then when returning you may guess the content of license module *p1 = *lp2. Though you cannot read the content of license modules directly, you may determine the content by algorithm. If possible, you had better check the content with an algorithm, not only compare in the program.


15. Calculate 2 (UNIKEY_CALCULATE2)

Description
To return the results of a calculation performed in UniKey, using input provided by the developer and the CALCULATE2 function.

Parameters
Parameter	Meaning
function	[in] UNIKEY_CALCULATE2
*handle		[in] Dongle handle
*lp1		[in] Start point of calculation
*lp2		[in] Seed Code (32-bit)
*p1		[in, out] Register A
*p2		[in, out] Register B
*p3		[in, out] Register C
*p4		[in, out] Register D

Return values
Marco			Value	Meaning
SUCCESS			0	Success
ERROR_SEED		13	Seed code Error	
ERROR_CALCULATE		14	Calculate Error
ERROR_NO_OPEN		15	No open dongle before operating dongle
ERROR_AR_BAD_COMMAND	20	Arithmetic instruction Error
ERROR_AR_UNKNOWN_OPCODE	21	Arithmetic operator Error
ERROR_AR_WRON_GBEGIN	22	Const number can't use on first arithmetic instruction
ERROR_AR_WRONG_END	23	Const number can't use on last arithmetic instruction
ERROR_AR_VALUE_OVERFLOW	24	Const number > 63

Remarks
When performing calculation 2, the initial values of register E, F, G and H are the return values of seed code *lp2, to make it simple, UniKey calls function SEED with seed code *lp2, and writes the return values to register E, F, G and H for next operation.
Internal Register	Meaning
E			Seed Result 1
F			Seed Result 2
G			Seed Result 3
H			Seed Result 4



16. Calculate 3 (UNIKEY_CALCULATE3)

Description  
To return results of a calculation performed in UniKey, using input provided by the developer and the CALCULATE3 function.

Parameters	
Parameter	Meaning
function	[in] UNIKEY_CALCULATE3
*handle		[in] Dongle handle
*lp1		[in] Start point of calculation
*lp2		[in] license module number
*p1		[in, out] Register A
*p2		[in, out] Register B
*p3		[in, out] Register C
*p4		[in, out] Register D

Return values	
Marco			Value	Meaning
SUCCESS			0	Success
ERROR_RANDOM		12	Random number Error
ERROR_CALCULATE		14	Calculate Error
ERROR_NO_OPEN		15	No open dongle before operating dongle
ERROR_AR_BAD_COMMAND	20	Arithmetic instruction Error
ERROR_AR_UNKNOWN_OPCODE	21	Arithmetic operator Error
ERROR_AR_WRON_GBEGIN	22	Const number can't use on first arithmetic instruction
ERROR_AR_WRONG_END	23	Const number can't use on last arithmetic instruction
ERROR_AR_VALUE_OVERFLOW	24	Const number > 63

Remarks
When performing calculation 3, the initial values of register E, F, G and H are the content of license module *lp2 and *lp2+1/2/3
Internal Register	Meaning
E			Value in license module *lp2
F			Value in license module (*lp2 + 1)
G			Value in license module (*lp2 + 2)
H			Value in license module (*lp2 + 3)

Examples
When calls calculation 3 with *lp2 = 0, the initial values of register E, F, G and H are:
E = Value of license module 0
F = Value of license module 1
G = Value of license module 2
F = Value of license module 3
Note: The address will return to "0" when the license module address call exceeds 128. For example:  Calculation 3 with *lp2 = 126, the initial values of register E, F, G and H are:
E = Value of license module 126
F = Value of license module 127
G = Value of license module 0
H = Value of license module 1


17. Decrease license module Unit (UNIKEY_MODULE_DECRASE)

Description
To decrease the value in a specified UniKey license module by "1".

Parameters	
Parameter	Meaning
function	[in] UNIKEY_MODULE_DECRASE
*handle		[in] Dongle handle
*p1		[in] license module number

Return values 	
Marco			Value	Meaning
SUCCESS			0	Success
ERROR_NO_OPEN		15	No open dongle before operating dongle
ERROR_MODULE_DECRASE	19	license module Decrease Error

Remarks
Please call UNIKEY_CHECK_MODULE to check if the license module is valid firstly.


18£® Set a New Password via a New Seed (UNIKEY_SET_NEW_PASSWORD)

Description
To generate a new password via a seed code. The mapping from the seed code to the password is only one way. Without the seed, you cannot generate the same password.

Parameters	
Parameter	Meaning
function	[in] UNIKEY_SET_NEW_PASSWORD
*handle		[in] Dongle handle
*lp1		[in] Seed Code (32-bit)
*p1		[out] New password 1
*p2		[out] New password 2
*p3		[out] New password 3
*p4		[out] New password 4

Return values 	
Marco				Value	Meaning
SUCCESS				0	Success
ERROR_NO_OPEN			15	No open dongle before operating dongle
ERROR_VERIFY_ADV_PASSWORD	27	Advanced passwords (password3 and passowrd4) not verified
EE_GENERATE_NEW_PASSWORD	29	Generate new password Error

Remarks
A file recording the new SEED and PASSWORDs will be created in the working path, and help the software vendor to recall everything. The passwords can be distributed to ordinary developers!

Note:
1. The dongle will be automatically closed after a new set of passwords are generated.
2. The dongle will be fully formatted when a new password generated
3. A file including new password and seed will be created in the working directory.


19£® Generate a New Key in specific Key Store (UNIKEY_GENERATE_KEY)

Description
To generate a new key in the specific key storage. 

Parameters	
Parameter	Meaning
function	[in] UNIKEY_GENERATE_KEY
*handle		[in] Dongle handle
*lp1		[in] Key Storage Number

Return values 	
Marco			Value	Meaning
SUCCESS			0	Success
ERROR_NO_OPEN		15	No open dongle before operating dongle
ERROR_INVALID_KEY_STORE	28	Wrong key storage number

Remarks
This function will delete the original key in the key storage first, and generate a new key.


20. Encrypt the Buffer with a Specific Key (UNIKEY_ENCRYPT)

Description
To encrypt a mount of memory with a key.

Parameters
Parameter	Meaning
function	[in] UNIKEY_ENCRYPT
*handle		[in] Dongle handle
*lp1		[in] Number of bytes to encrypt
*lp2		[in] Key Storage Number
*buffer		[in] Pointer to the data to be encrypted
		[out] Pointer to the encrypted data

Return values 	
Marco			Value	Meaning
SUCCESS			0	Success
ERROR_NO_OPEN		15	No open dongle before operating dongle
ERROR_INVALID_KEY_STORE	28	Wrong key storage number

Remarks
This function does only encryption operation, but no compression functions are involved.


21£® Decrypt the Buffer with a Specific Key (UNIKEY_DECRYPT)

Description
To encrypt a mount of memory with a key.

Parameters	
Parameter	Meaning
function	[in] UNIKEY_DECRYPT
*handle		[in] Dongle handle
*lp1		[in] Number of bytes to encrypt
*lp2		[in] Key Storage Number
*buffer		[in] Pointer to the data to be decrypted
		[out] Pointer to the decrypted data

Return values 	
Marco			Value	Meaning
SUCCESS			0	Success
ERROR_NO_OPEN		15	No open dongle before operating dongle
ERROR_INVALID_KEY_STORE	28	Wrong key storage number
 

22£® Make an MD5 Digest for a Certain Content (UNIKEY_MD5)
		
Description
Make an MD5 digest for a mount of memory.

Parameters	
Parameter	Meaning
function	[in] UNIKEY_MD5
*handle		[in] Dongle handle
*lp1		[in] Number of bytes to encrypt
*lp2		[in] Key Storage Number
*buffer		[in] Pointer to the data to be digested[out] Pointer to the digested data

Return value: 	
Marco			Value	Meaning
SUCCESS			0	Success
ERROR_NO_OPEN		15	No open dongle before operating dongle
ERROR_INVALID_KEY_STORE	28	Wrong key storage number
 

23£® Read UpdateTag from a Specific Key(UNIKEY_READ_UPDATETAG)
		
Description
Read UpdateTag from a specific dongle

Parameters	
Parameter	Meaning
function	[in] UNIKEY_READ_UPDATETAG
*handle		[in] Dongle handle
*lp1		[out] UpdateTag

Return value: 	
Marco			Value	Meaning
SUCCESS			0	Success
ERROR_NO_OPEN		15	No open dongle before operating dongle
ERROR_READ_UPDATETAG	30	Read UpdateTag Error


24£® Write UpdateTag from a Specific Key(UNIKEY_WRITE_UPDATETAG)
		
Description
Write UpdateTag into a specific dongle

Parameters	
Parameter	Meaning
function	[in] UNIKEY_WRITE_UPDATETAG
*handle		[in] Dongle handle
*lp1		[in] UpdateTag

Return value: 	
Marco			Value	Meaning
SUCCESS			0	Success
ERROR_NO_OPEN		15	No open dongle before operating dongle
ERROR_WRITE_UPDATETAG	31	Write UpdateTag Error
*/

#define UniKeyMemorySize	4096	// memory size

// for Static library, please use this declaration
extern long UniKey(WORD function, WORD* handle, DWORD* lp1,  DWORD* lp2, WORD* p1, WORD* p2, WORD* p3, WORD* p4, BYTE* buffer);


// for dynamic library, please use this declaration
//EXTERN_C __declspec(dllexport) long __stdcall UniKey(WORD Function, WORD* handle, DWORD* lp1, DWORD* lp2, WORD* p1, WORD* p2, WORD* p3, WORD* p4, BYTE* buffer);

