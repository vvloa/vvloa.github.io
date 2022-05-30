#include <stdio.h>
#include "stdafx.h"

#include <iostream>
#include "md5.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

using std::cout; using std::endl;
/*
// C prototype : void StrToHex(unsigned char *pbDest, unsigned char *pbSrc, int nLen)
// parameter(s): [OUT] pbDest - 输出缓冲区
// [IN] pbSrc - 字符串
// [IN] nLen - 16进制数的字节数(字符串的长度/2)
// return value:
// remarks : 将字符串转化为16进制数
*/
void StrToHex(unsigned char *pbDest, unsigned char *pbSrc, int nLen)
{
	char h1, h2;
	unsigned char s1, s2;
	int i;

	for (i = 0; i<nLen; i++)
	{
		h1 = pbSrc[2 * i];
		h2 = pbSrc[2 * i + 1];

		s1 = toupper(h1) - 0x30; //十六进制 0x30   ,    dec十进制 48	,   图形 0
		if (s1 > 9)
			s1 -= 7;

		s2 = toupper(h2) - 0x30;
		if (s2 > 9)
			s2 -= 7;

		pbDest[i] = s1 * 16 + s2;
	}
}



void sub_45BEB0(char* md5_str, char a2[32]){
	char s2[] = "0123456789abcdeflq@";
	char tem1,tem2;
	for (int i = 0; i < 0x10; i++){
		tem1 = md5_str[i];
		tem1 = tem1 >> 4;
		tem1 = tem1 & 0xf;
		tem1 = s2[tem1];
		a2[2 * i] = tem1;

		tem2 = md5_str[i];
		tem2 = tem2 & 0xf;
		tem2 = tem2 & 0xff;
		tem2 = s2[tem2];

		a2[2 * i + 1] = tem2;
	}

}
unsigned int __fastcall sub_45C09C(char *a1, unsigned int a2, char len)
{
	signed int v3; // ebx@2
	int v4; // esi@3
	unsigned int v5; // edx@4
	int v6; // esi@4
	char v7; // eax@5
	char* v9; // [sp-4h] [bp-14h]@3
	unsigned __int8 v10; // [sp+9h] [bp-7h]@5
	char v11; // [sp+Ah] [bp-6h]@5
	char v12; // [sp+Bh] [bp-5h]@4
	char *v13; // [sp+Ch] [bp-4h]@4

	v9 = a1;
	v12 = len;
	v13 = v9;
	v5 = 0;
	v6 = 0;
	do
	{
		v7 = *((char *)v13 + v6++);
		v11 = 8;
		v10 = 1;
		do
		{
			if (v10 & (unsigned __int8)(v5 ^ v7))
			{
				v5 = (unsigned int)(unsigned __int8)(v5 ^ 0x18) >> 1;
				v5 = v5 | 0x80;
			}
			else
			{
				v5 = (unsigned int)(unsigned __int8)v5 >> 1;
			}
			v7 = (unsigned int)(unsigned __int8)v7 >> 1;
			--v11;
		} while (v11);
		--v12;
	} while (v12);
	return v5;
}


DWORD main()
{
	/*
	int i;
	unsigned char encrypt[] = "admin";//21232f297a57a5a743894a0e4a801fc3
	unsigned char decrypt[16];
	MD5_CTX md5;
	MD5Init(&md5);
	MD5Update(&md5, encrypt, strlen((char *)encrypt));
	MD5Final(&md5, decrypt);
	printf("加密前:%s\n加密后:", encrypt);
	for (i = 0; i<16; i++)
	{
		printf("%02x", decrypt[i]);
	}

	getchar();
	*/
	unsigned char decrypt[16];
	unsigned char uname[] = "admin";
	unsigned char str_110512[] = "110512";
	MD5_CTX md5;
	MD5Init(&md5);
	MD5Update(&md5, uname, strlen((char *)uname));
	MD5Final(&md5, decrypt);
	char s3[33] = { 0 };
	sub_45BEB0((char*)decrypt, s3);


	MD5_CTX md52;
	MD5Init(&md52);
	MD5Update(&md52, str_110512, strlen((char *)str_110512));
	MD5Final(&md52, decrypt);
	char s4[33] = { 0 };
	sub_45BEB0((char*)decrypt, s4);

	char s5[65];
	strcpy(s5, s3);
	int len = strlen(s5) + strlen(s4) + 1;
	strcat_s(s5, len, s4);


	MD5Init(&md52);
	MD5Update(&md52, (unsigned char*)s5, strlen((char *)s5));
	MD5Final(&md52, decrypt);

	char s6[33] = { 0 };
	sub_45BEB0((char*)decrypt, s6);

	char str_110512_1[3] = { 0 }, str_110512_2[3] = { 0 }, str_110512_3[3] = { 0 };
	strncpy(str_110512_1, (const char *)str_110512, 2);
	strncpy(str_110512_2, (const char *)str_110512+2, 2);
	strncpy(str_110512_3, (const char *)str_110512+4, 2);

	int str_110512_int1 = atoi(str_110512_1);
	int str_110512_int2 = atoi(str_110512_2);
	int str_110512_int3 = atoi(str_110512_3);

	char str_110512_bin1[9] = { 0 }, str_110512_bin2[9] = { 0 }, str_110512_bin3[9] = { 0 };

	int i, j, num;
	unsigned ask = 0x80;


	for (i = 0; i < 8; i++)
	{
		str_110512_bin1[i] = (str_110512_int1 & ask) ? '1' : '0';
		ask = ask >> 1;
	}
	ask = 0x80;
	for (i = 0; i < 8; i++)
	{
		str_110512_bin2[i] = (str_110512_int2 & ask) ? '1' : '0';
		ask = ask >> 1;
	}
	ask = 0x80;
	for (i = 0; i < 8; i++)
	{
		str_110512_bin3[i] = (str_110512_int3 & ask) ? '1' : '0';
		ask = ask >> 1;
	}


	char str_110512_bin1_1[9] = { 0 }, str_110512_bin1_2[9] = { 0 }, str_110512_bin1_3[9] = { 0 };
	strncpy(str_110512_bin1_1, str_110512_bin1 + 1, 7);
	strncpy(str_110512_bin1_2, str_110512_bin2 + 4, 4);
	strncpy(str_110512_bin1_3, str_110512_bin3 + 3, 5);

	char local5[65];
	strcpy(local5, str_110512_bin1_1);
	len = strlen(local5) + strlen(str_110512_bin1_2) + 1;
	strcat_s(local5, len, str_110512_bin1_2);
	len = strlen(local5) + strlen(str_110512_bin1_3) + 1;
	strcat_s(local5, len, str_110512_bin1_3);

	char s8[64] = { 0 };
	char local31[3] = {0};
	int dl = local5[2];
	s8[0] = dl;

	char local33[3] = { 0 };
	dl = local5[3];
	s8[1] = dl;


	dl = local5[4];
	s8[2] = dl;


	dl = local5[8];
	s8[3] = dl;


	dl = local5[9];
	s8[4] = dl;


	dl = local5[0xc];
	s8[5] = dl;


	dl = local5[0xd];
	s8[6] = dl;


	dl = local5[0xe];
	s8[7] = dl;
	// 30 31 30 31 30 31 31 30                          01010110
	int a = strtol(s8, NULL, 2);

	char s9[10] = { 0 };
	itoa(a, s9,16);

	ZeroMemory(s8, 64);
	dl = local5[0];
	s8[0] = dl;

	dl = local5[1];
	s8[1] = dl;

	dl = local5[5];
	s8[2] = dl;

	dl = local5[6];
	s8[3] = dl;

	dl = local5[7];
	s8[4] = dl;

	dl = local5[0xa];
	s8[5] = dl;

	dl = local5[0xb];
	s8[6] = dl;

	dl = local5[0xf];
	s8[7] = dl;

	int b = strtol(s8, NULL, 2);

	char s10[60] = { 0 };
	itoa(b, s10, 16);

	strcat_s(s10, s9);




	char s101[10] = { 0 };
	char s102[10] = { 0 };
	strcpy(s101, s10);
	strcpy(s102, s10);
	strcat_s(s10, s3);
	//  025535D8  33 34 35 36 35 39 34 66 38 30 33 62 33 38 30 61  3456594f803b380a
	//  025535E8  34 31 33 39 36 65 64 36 33 64 63 61 33 39 35 30  41396ed63dca3950
	//	025535F8  33 35 34 32                                      3542

	// 字符串变为ascii 码
	//0019FB30  34 56 59 4F 80 3B 38 0A 41 39 6E D6 3D CA 39 50  4VYO€;8.A9n??P
	// 0019FB40  35 42                                            5B

	char s11[20] = { 0 };
	char s12[3] = { 0 };
	int c = 0;

	StrToHex((unsigned char *)s11, (unsigned char *)s10, 18);

	int len10 = strlen(s10) / 2;

	int d = sub_45C09C(s11, 0xff, len10);

	char s13[30] = { 0 };
	itoa(d, s13, 16);
	i = 0;
	while (s13[i])
	{
		c = s13[i];
		s13[i] = toupper(c);
		i++;
	}
	strcat_s(s101, s13);



	char s14[60] = { 0 };
	MD5Init(&md52);
	MD5Update(&md52, (unsigned char *)s101, strlen((char *)s101));
	MD5Final(&md52, decrypt);
	sub_45BEB0((char*)decrypt, s14);

	char s15[30] = { 0 };
	s15[0] = s14[7];
	s15[1] = s14[8];

	char local_51[65];
	strcpy(local_51, s3);
	int len1 = strlen(local_51) + strlen(s4) + 1;
	strcat_s(local_51, len1, s6);



	// sub_45cc42
	char local_51_s[65] = { 0 };
	StrToHex((unsigned char *)local_51_s, (unsigned char *)local_51, strlen(local_51)/2);

	int len_local_51 = strlen(local_51) / 2;

	int e = sub_45C09C(local_51_s, 0xff, len_local_51);
	char local_12[10] = { 0 };
	itoa(e, local_12, 16);


	char local_52[65];
	strcpy(local_52, s4);
	len1 = strlen(local_52) + strlen(s6) + 1;
	strcat_s(local_52, len1, s6);


	// sub_45cc42
	char local_52_s[65] = { 0 };
	StrToHex((unsigned char *)local_52_s, (unsigned char *)local_52, strlen(local_52)/2);

	int len_local_52 = strlen(local_52) / 2;

	int f = sub_45C09C(local_52_s, 0xff, len_local_52);
	char local_13[10] = { 0 };
	itoa(f, local_13, 16);



	/////////////////////////// 解密 
	char s20[40] = { 0 };
	strcpy(s20, s13);
	strcat_s(s20, strlen(s102) + strlen(s20) + 1, s102);
	strcat_s(s20, strlen(s20) + strlen(s15) + 1, s15);


	char local_54[10] = { 0 };
	local_54[0] = s6[7];
	int local_54_int = atoi(local_54);

	strcat_s(s20, strlen((char*)local_54) + strlen(s20) + 1, (char*)local_54);


	char local_55[10] = { 0 };
	local_55[0] = s6[0xE];
	int local_55_int = atoi(local_55);

	strcat_s(s20, strlen((char*)local_55) + strlen(s20) + 1, (char*)local_55);
	strcat_s(s20, strlen((char*)local_12) + strlen(s20) + 1, (char*)local_12);

	char local_56[10] = { 0 };
	local_56[0] = s6[0x17];
	int local_56_int = atoi(local_56);

	strcat_s(s20, strlen((char*)local_56) + strlen(s20) + 1, (char*)local_56);

	char local_57[10] = { 0 };
	local_57[0] = s6[0xB];
	int local_57_int = atoi(local_57);

	strcat_s(s20, strlen((char*)local_57) + strlen(s20) + 1, (char*)local_57);
	strcat_s(s20, strlen((char*)local_13) + strlen(s20) + 1, (char*)local_13);

	i = 0;
	while (s20[i])
	{
		c = s20[i];
		s20[i] = toupper(c);
		i++;
	}

	printf("%s", s20);


	system("pause");
	return 0;

}
