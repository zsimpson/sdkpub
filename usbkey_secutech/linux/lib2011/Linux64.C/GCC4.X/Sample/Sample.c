
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <dlfcn.h>

#define _TEST_NEW_API_

#ifdef _TEST_NEW_API_
/*********************TEST NEW API***********************/
#include "UniKeyFR.h"
void UniKeyTimeSample(WORD handle);
void UniKeySample()
{
	WORD handle[16], p1, p2, p3, p4;
	DWORD retcode, lp1, lp2;
	BYTE buffer[4096];
	WORD rc[4];
	int i, j;
	i=0; j=0;

	char cmd[] = "H=H^H, A=A*23, F=B*17, A=A+F, A=A+G, A=A<C, A=A^D, B=B^B, C=C^C, D=D^D";
	char cmd1[] = "A=A+B, A=A+C, A=A+D, A=A+E, A=A+F, A=A+G, A=A+H";
	char cmd2[] = "A=E|E, B=F|F, C=G|G, D=H|H";
	char str1[] = "abcdefghijklmnop";

	p1 = 1234;	// passwords
	p2 = 1234;
	p3 = 1234;
	p4 = 1234;

	//get version
	retcode = UniKey_Get_Version(&handle[0], &lp1);
	if (retcode)
	{
		printf("UniKey_Get_Version error code: %d \n", retcode);
		return;
	}
	printf("UniKey lib ver: %08X\n", lp1);

	// find dongle
	lp1 = 0, lp2 = 1;
	retcode = UniKey_Find(&handle[0], &lp1, &lp2);
	if (retcode)
	{
		printf("UniKey_Find error code: %d \n", retcode);
		return;
	}
	// return the hardware ID (HID)                             
	printf("Find UniKey: %08X\n", lp1);

	// open dongle
	retcode = UniKey_User_Logon(&handle[0], &p1, &p2);
	if (retcode)
	{
		printf("UniKey_User_Logon error code: %d \n", retcode);
		return;
	}

	retcode = UniKey_Vender_Logon(&handle[0], &p1, &p2, &p3, &p4);
	if (retcode)
	{
		printf("UniKey_Vender_Logon error code: %d \n", retcode);
		return;
	}

	// enumerate all the dongles
	i = 1;
	while (retcode == 0)
	{
		// find next dongle
		retcode = UniKey_Find_Next(&handle[i], &lp1, &lp2);
		if (retcode == ERROR_UNIKEY_NOMORE) break;
		if (retcode)
		{
			printf("UniKey_Find_Next error code: %d \n", retcode);
			break;
		}
		// open dongle
		retcode = UniKey_User_Logon(&handle[i], &p1, &p2);
		if (retcode)
		{
			printf("UniKey_User_Logon error code: %d \n", retcode);
			return;
		}
		retcode = UniKey_Vender_Logon(&handle[i], &p1, &p2, &p3, &p4);
		if (retcode)
		{
			printf("UniKey_Vender_Logon error code: %d \n", retcode);
			return;
		}
		i++;
		printf("Find UniKey: %08X\n", lp1);
	}
	printf("\n");

	for (j=0;j<i;j++)
	{
		strcpy((char*)buffer, "                                   ");

		p1 = 10;
		p2 = 5;
		strcpy((char*)buffer, "hello");
		
		// write dongle memory
		retcode = UniKey_Write_Memory(&handle[j], &p1, &p2, buffer);
		if (retcode)
		{
			printf("UniKey_Write_Memory error code: %d \n", retcode);
			return;
		}
		printf("Write: %s\n",buffer);

//		p1 = 4;
//		p2 = 26;
		memset(buffer, 0, 64);
		
		// read dongle memory
		retcode = UniKey_Read_Memory(&handle[j], &p1, &p2, buffer);
		if (retcode)
		{
			printf("UniKey_Read_Memory error code: %d \n", retcode);
			return;
		}
		printf("Read: %s\n", buffer);

		// random generation function
		retcode = UniKey_Random(&handle[j], &p1, &p2, &p3, &p4);
		if (retcode)
		{
			printf("UniKey_Random error code: %d \n", retcode);
			return;
		}
		printf("Random: %04X\n", p1);

		// seed function, you can use either hex or dec
		lp1 = 0x12345678;
		retcode = UniKey_Seed(&handle[j], &lp1, &p1, &p2, &p3, &p4);
		if (retcode)
		{
			printf("UniKey_Seed error code: %d \n", retcode);
			return;
		}
		printf("Seed: %04X %04X %04X %04X\n", p1, p2, p3, p4);
		rc[0] = p1;
		rc[1] = p2;
		rc[2] = p3;
		rc[3] = p4;

		// write SoftID
		lp1 = 0x88888888;
		retcode = UniKey_Write_SoftID(&handle[j], &lp1);
		if (retcode)
		{
			printf("UniKey_Write_SoftID error code: %d \n", retcode);
			return;
		}
		printf("Write SoftID: %08X\n", lp1);

		// read SoftID
		lp1 = 0;
		retcode = UniKey_Read_SoftID(&handle[j], &lp1);
		if (retcode)
		{
			printf("UniKey_Read_SoftID error code: %d \n", retcode);
			return;
		}
		printf("Read SoftID: %08X\n", lp1);

		// set license module
		p1 = 7;
		p2 = 0x2121;
		p3 = 0;
		retcode = UniKey_Set_Module(&handle[j], &p1, &p2, &p3);
		if (retcode)
		{
			printf("UniKey_Set_Module error code: %d \n", retcode);
			return;
		}
		printf("Set License MODULE 7 = %04X Decrease no allow\n", p2);

		// check license module
		p1 = 7;
		retcode = UniKey_Check_Module(&handle[j], &p1, &p2, &p3);
		if (retcode)
		{
			printf("UniKey_Check_Module error code: %d \n", retcode);
			return;
		}
		printf("Check MODULE 7: ");
		if (p2) printf("Allow   ");
			else printf("No Allow   ");
		if (p3) printf("Allow Decrease\n");
			else printf("Not Allow Decrease\n");

		// write user-defined algorithm
		p1 = 0;
		strcpy((char*)buffer, cmd);
		retcode = UniKey_Write_Arithmetic(&handle[j], &p1, buffer);
		if (retcode)
		{
			printf("UniKey_Write_Arithmetic error code: %d \n", retcode);
			return;
		}
		printf("Write Arithmetic 1\n");

		// calculation 1
		lp1 = 0;
		lp2 = 7;
		p1 = 5;
		p2 = 3;
		p3 = 1;
		p4 = 0xffff;
		retcode = UniKey_Calculate1(&handle[j], &lp1, &lp2, &p1, &p2, &p3, &p4);
		if (retcode)
		{
			printf("UniKey_Calculate1 error code: %d \n", retcode);
			return;
		}
		printf("Calculate 1 Input: p1=5, p2=3, p3=1, p4=0xffff\n");
		printf("Result = ((5*23 + 3*17 + 0x2121) < 1) ^ 0xffff = BC71\n");
		printf("Calculate 1 Output: p1=%x, p2=%x, p3=%x, p4=%x\n", p1, p2, p3, p4);

		// calculation 3
		p1 = 10;
		strcpy((char*)buffer, cmd1);
		retcode = UniKey_Calculate2(&handle[j], &lp1, &lp2, &p1, &p2, &p3, &p4);
		if (retcode)
		{
			printf("UniKey_Calculate2 error code: %d \n", retcode);
			return;
		}
		printf("Write Arithmetic 2\n");

		// Write Arithmetic 3
		p1 = 0;
		strcpy((char*)buffer, cmd1);
		retcode = UniKey_Write_Arithmetic(&handle[j], &p1, buffer);
		if (retcode)
		{
			printf("UniKey_Write_Arithmetic error code: %d \n", retcode);
			return;
		}
		// calculation3
		lp1 = 10;
		lp2 = 0x1234;
		p1 = 1;
		p2 = 2;
		p3 = 3;
		p4 = 4;
		retcode = UniKey_Calculate3(&handle[j], &lp1, &lp2, &p1, &p2, &p3, &p4);
		if (retcode)
		{
			printf("UniKey_Calculate3 error code: %d \n", retcode);
			return;
		}
		printf("Calculate 3 Input: p1=1, p2=2, p3=3, p4=4\n");
		printf("Result = %04x + %04x + %04x + %04x + 1 + 2 + 3 + 4 = %04x\n", rc[0], rc[1], rc[2], rc[3], (WORD)(rc[0]+rc[1]+rc[2]+rc[3]+10));
		printf("Calculate 3 Output: p1=%x, p2=%x, p3=%x, p4=%x\n", p1, p2, p3, p4);

		// Set License Module Decrease
		p1 = 9;
		p2 = 0x5;
		p3 = 1;
		retcode = UniKey_Set_Module(&handle[j], &p1, &p2, &p3);
		if (retcode)
		{
			printf("UniKey_Set_Module error code: %d \n", retcode);
			return;
		}

		//  write user-defined algorithm
		p1 = 17;
		strcpy((char*)buffer, cmd2);
		retcode = UniKey_Write_Arithmetic(&handle[j], &p1, buffer);
		if (retcode)
		{
			printf("UniKey_Write_Arithmetic error code: %d \n", retcode);
			return;
		}
		printf("Write Arithmetic 3\n");

		// Calculation3
		lp1 = 17;
		lp2 = 6;
		p1 = 1;
		p2 = 2;
		p3 = 3;
		p4 = 4;
		retcode = UniKey_Calculate3(&handle[j], &lp1, &lp2, &p1, &p2, &p3, &p4);
		if (retcode)
		{
			printf("UniKey_Calculate3 error code: %d \n", retcode);
			return;
		}
		printf("Show License Module from 6: p1=%x, p2=%x, p3=%x, p4=%x\n", p1, p2, p3, p4);

		// Decrease License Module
		p1 = 9;
		retcode = UniKey_Module_Decrase(&handle[j], &p1);
		if (retcode)
		{
			printf("UniKey_Module_Decrase error code: %d \n", retcode);
			return;
		}
		printf("Decrease module 9\n");

		// Calculation3
		lp1 = 17;
		lp2 = 6;
		p1 = 1;
		p2 = 2;
		p3 = 3;
		p4 = 4;
		retcode = UniKey_Calculate3(&handle[j], &lp1, &lp2, &p1, &p2, &p3, &p4);
		if (retcode)
		{
			printf("UniKey_Calculate3 error code: %d \n", retcode);
			return;
		}
		printf("Show Module from 6: p1=%x, p2=%x, p3=%x, p4=%x\n", p1, p2, p3, p4);

//------------------------------------
		// generate new password
		// if you really want to change password, please de-comment these codes
/*		lp1=1234;	
		retcode=UniKey(UNIKEY_SET_NEW_PASSWORD,&handle[j], &lp1, &lp2, &p1, &p2, &p3, &p4, buffer);
		if (retcode)
		{
			printf("error code: %d \n", retcode);
			return;
		}
		printf("Generate new passwords, seed: %d, p1: %d, p2: %d,p3: %d, p4: %d\n",lp1,p1,p2,p3,p4);
*/
//------------------------------
	// generate key
		lp1=1;		
		retcode=UniKey_Generate_Key(&handle[j], &lp1);
		if (retcode)
		{
			printf("error code: %d \n", retcode);
			return;
		}
		printf("generate key %d successed\n",lp1);
		
		// encrypt
		memset(buffer, 0, 64);
		strcpy((char*)buffer, str1);
		lp2=1;
		lp1=16;
		retcode=UniKey_Encrypt(&handle[j], &lp1, &lp2, buffer);
		if (retcode)
		{
			printf("error code: %d \n", retcode);
			return;
		}
		printf("encrypt successed, result: %s \n",buffer);
		
		// decrypt
		lp2=1;
		lp1=16;
		retcode=UniKey_Decrypt(&handle[j], &lp1, &lp2, buffer);
		if (retcode)
		{
			printf("error code: %d \n", retcode);
			return;
		}
		printf("decrypt successed, result: %s\n",buffer);	
		
		// MD5
		memset(buffer, 0, 64);
		strcpy((char*)buffer, str1);
		lp1=16;
		lp2=0;
		retcode=UniKey_MD5(&handle[j], &lp1, buffer);
		if (retcode)
		{
			printf("error code: %d \n", retcode);
			return;
		}
		printf("MD5 successed, result: %s\n",buffer);					
		
		// write UpdateTag
		//lp1=rand();
		//retcode=UniKey_Write_UpdateTag(&handle[j], &lp1);
		//if (retcode)
		//{
		//	printf("error code: %d \n", retcode);
		//	return;
		//}
		//printf("write UpdateTag: %x ",lp1);

		//UniKey Time
		
		UniKeyTimeSample(handle[j]);

		// read UpdateTag
		lp1=0;
		retcode=UniKey_Read_UpdateTag(&handle[j], &lp1);
		if (retcode)
		{
			printf("UniKey_Read_UpdateTag error code: %d \n", retcode);
			return;
		}
		printf("read UpdateTag: %x \n",lp1);			
				

		// close dongle
		retcode = UniKey_Logoff(&handle[j]);
		if (retcode)
		{
			printf("UniKey_Logoff error code: %d \n", retcode);
			return;
		}
		
		printf("logoff\n");
		//getch();
	}
}

void UniKeyTimeSample(WORD handle){
	int i;
	WORD  p1, p2, p3, p4;
	DWORD ret, lp1, lp2;
	//ret = UniKey_Set_Time_Now(&handle);
	//if(ret){
	//	printf("UniKey_Set_Time_Now error code: %d \n", ret);
	//	return;
	//}
	ret = UniKey_Get_Time(&handle, &lp1, &lp2, &p1, &p2, &p3, &p4);
	if(ret){
		printf("UniKey_Get_Time_Now error code: %d \n", ret);
		return;
	}
	printf("Get Time: %02d-%02d-%02d  %02d:%02d:%02d\n", lp1, lp2, p1, p2, p3, p4);
		lp1 = 1;
		ret = UniKey_Erase_Time_Module(&handle, &lp1);
		if(ret){
			printf("UniKey_Get_Time_Now error code: %d \n", ret);
			return;
		}
		else
			printf("Erease time success!\n");
		
		ret = UniKey_Set_Time_Module_Start_Time_Now(&handle, &lp1);
		if(ret){
			printf("UniKey_Get_Time_Now error code: %d \n", ret);
			return;
		}
		else
			printf("Set_Time_Module_Start_Time_Now success!\n");
		lp1=1;
		lp2 = 10; // duration is10 Day
		p1  = 6; // and 6hour
		ret = UniKey_Set_Time_Module_Duration(&handle, &lp1, &lp2, &p1);
		if(ret){
			printf("UniKey_Get_Time_Now error code: %d \n", ret);
			return;
		}
		lp1=1;
		ret = UniKey_Check_Time_Module_Now(&handle, &lp1,&lp2,&p1);
		if(ret){
			printf("UniKey_Check_Time_Module_Now MuduleNo=%d  Error code: %d.\n", lp1, ret);
			return;
		}else{
			printf("UniKey_Check_Time_Module_Now MuduleNo=%d  Success.\n", lp1);
			printf("UniKey_Check_Time_Module_Now remain %d days and %d hours\n", lp2,p1);
		}
		
		if(1){ // test fail for overdure
			ret = UniKey_Get_Time(&handle, &lp1, &lp2, &p1, &p2, &p3, &p4);
			if(ret){
				printf("UniKey_Get_Time_Now error code: %d \n", ret);
				return;
			}
			p4 = p2;
			p3 = p1;
			p2 = lp2;
			p1 = lp1;
			lp1 = 1;
			p3 += 1; // emulate 1day later
			p4 += 1; // and 1 hour later
			ret = UniKey_Check_Time_Module(&handle, &lp1, &lp2 , &p1, &p2, &p3, &p4);
			if(ret){
				printf("UniKey_Check_Time_Module  error code: %d \n", ret);
				return;
			}
			else
				printf("remain %d days and %d hours\n", lp2,p1);
	}
}

int main()
{
	int nRetCode = 0;
	UniKeySample();
		//system("pause");
	return nRetCode;
}

#else

#include "UniKey.h"

int main()
{
	WORD handle[16], p1, p2, p3, p4, retcode;
	DWORD lp1, lp2;
	BYTE buffer[MemorySize];
	WORD rc[4];
	int i, j;

	char cmd[] = "A=A^E,B=B^F,C=C^G,D=D^H";

	p1 = 1234;	// passwords
	p2 = 1234;
	p3 = 1234;
	p4 = 1234;

	// find dongle
	retcode = UniKey(UNIKEY_FIND, &handle[0], &lp1, &lp2, &p1, &p2, &p3, &p4, buffer);
	if (retcode)
	{
		printf("error code: %d \n", retcode);
		return 1;
	}
	// return the hardware ID (HID)                             
	printf("Find UniKey: %08X\n", lp1);
	
	// open dongle
	retcode = UniKey(UNIKEY_LOGON, &handle[0], &lp1, &lp2, &p1, &p2, &p3, &p4, buffer);
	if (retcode)
	{
		printf("error code: %d \n", retcode);
		return 1;
	}


	// enumerate all the dongles
	i = 1;
	while (retcode == 0)
	{
		retcode = UniKey(UNIKEY_FIND_NEXT, &handle[i], &lp1, &lp2, &p1, &p2, &p3, &p4, buffer);
		if (retcode == ERROR_NOMORE) break;
		if (retcode)
		{
			printf("error code: %d \n", retcode);
			return 1;
		}

		retcode = UniKey(UNIKEY_LOGON, &handle[i], &lp1, &lp2, &p1, &p2, &p3, &p4, buffer);
		if (retcode)
		{
			printf("error code: %d \n", retcode);
			return 1;
		}

		i++;
		printf("Find UniKey: %08X\n", lp1);
	}
	printf("\n");

	for (j=0;j<i;j++)
	{
		p1 = 3;
		p2 = 6;
		sprintf((char*)buffer, "Hello%d",j);
		
		// write dongle memory
		retcode = UniKey(UNIKEY_WRITE_MEMORY, &handle[j], &lp1, &lp2, &p1, &p2, &p3, &p4, buffer);
		if (retcode)
		{
			printf("error code: %d \n", retcode);
			return 1;
		}
		printf("Write: Hello\n");

		p1 = 3;
		p2 = 6;
		memset(buffer, 0, 64);
		
		// read dongle memory
		retcode = UniKey(UNIKEY_READ_MEMORY, &handle[j], &lp1, &lp2, &p1, &p2, &p3, &p4, buffer);
		if (retcode)
		{
			printf("error code: %d \n", retcode);
			return 1;
		}
		printf("Read: %s\n", buffer);

		// random generation function
		retcode = UniKey(UNIKEY_RANDOM, &handle[j], &lp1, &lp2, &p1, &p2, &p3, &p4, buffer);
		if (retcode)
		{
			printf("error code: %d \n", retcode);
			return 1;
		}
		printf("Random: %04X\n", p1);

		// seed function, you can use either hex or dec
		lp1 = 0x12345678;
		retcode = UniKey(UNIKEY_SEED, &handle[j], &lp1, &lp2, &p1, &p2, &p3, &p4, buffer);
		if (retcode)
		{
			printf("error code: %d \n", retcode);
			return 1;
		}
		printf("Seed: %04X %04X %04X %04X\n", p1, p2, p3, p4);
		rc[0] = p1;
		rc[1] = p2;
		rc[2] = p3;
		rc[3] = p4;

 // set license module
        p1 = 0;
        p2 = 1234;
        p3 = 0;
        retcode = UniKey(UNIKEY_SET_MODULE, &handle[j], &lp1, &lp2, &p1, &p2, &p3, &p4, buffer);
        if (retcode)
        {
            printf("set module error code: %d \n", retcode);
            return 0;
        }
        printf("Set License MODULE 7 = %d Decrease no allow\n", p2);


/*		// write user-defined algorithm
		p1 = 0;
		strcpy((char*)buffer, cmd);
		printf("alg: %s \n",buffer);
		retcode = UniKey(UNIKEY_WRITE_ARITHMETIC, &handle[j], &lp1, &lp2, &p1, &p2, &p3, &p4, buffer);
		if (retcode)
		{
			printf("error code: %8x \n", retcode);
			return 1;
		}
		printf("Write Arithmetic 1\n");
*/
		// calculation 1
		lp1 = 0;
		lp2 = 0;
		p1 = 0;
		p2 = 0;
		p3 = 0;
		p4 = 0;
		retcode = UniKey(UNIKEY_CALCULATE1, &handle[j], &lp1, &lp2, &p1, &p2, &p3, &p4, buffer);
		if (retcode)
		{
			printf("error code: %d \n", retcode);
			return 1;
		}
		printf("Calculate Output: p1=%x, p2=%x, p3=%x, p4=%x\n", p1, p2, p3, p4);
		
		// close dongle
		retcode = UniKey(UNIKEY_LOGOFF, &handle[j], &lp1, &lp2, &p1, &p2, &p3, &p4, buffer);
		if (retcode)
		{
			printf("error code: %d \n", retcode);
			return 1;
		}
		printf("\n");
		
		
//		getch();
	}
}
#endif
