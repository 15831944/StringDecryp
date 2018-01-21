/*
		加密算法
		原程序中没有加密算法，通过枚举法实现的加密算法，效率较低
*/
#ifndef STRING_ENCRYTION_H__
#define STRING_ENCRYTION_H__ 1

#include "StringDecrypt.h"

int StringEncry(const char *str)
{
	printf("枚举法加密，加密很慢，请稍后。。。\n");
	int nStrLen = strlen(str);
	byte* buffer = (byte*)malloc((nStrLen + 1)*sizeof(char));
	memset(buffer, 0, (nStrLen + 1)*sizeof(char));
	memcpy(buffer, str, nStrLen*sizeof(char));
	for (int i = 0; i < nStrLen + 1; i++)
	{
		//*(byte*)(buf + i) = (*(byte*)(buf + i)) ^ 0x25 + 36;  // 错误,^的优先级比+低。
		*(byte*)(buffer + i) = ((*(byte*)(buffer + i)) ^ 0x25) + 36;
	}
	//printf("%s:%s\n", str, buffer);
	int nResult3 = 0;
	((byte*)&nResult3)[0] = buffer[2];
	((byte*)&nResult3)[1] = buffer[1];
	((byte*)&nResult3)[2] = buffer[0];

	// 枚举
	for (int nStart = 0; nStart <= nStrLen; nStart += 3)
	{
		char data[5] = "";
		int nCount = 0;
		for (int i = 0; i < 64; i++)
		{
			for (int j = 0; j < 64; j++)
			{
				for (int k = 0; k < 64; k++)
				{
					for (int m = 0; m < 64; m++)
					{
						nCount++;
						data[0] = EncodeTable[i];
						data[1] = EncodeTable[j];
						data[2] = EncodeTable[k];
						data[3] = EncodeTable[m];
						const char* pRet = (const char*)StringDecrypt(data);
						if (pRet)
						{
							if (nStrLen - nStart <= 0)
							{
								if (pRet[0] == 0)
								if (pRet[1] == 0)
								if (pRet[2] == 0)
								{
									data[2] = '=';
									data[3] = '=';
									free((void*)pRet);
									printf("%s", data);
									goto Next;
								}
								free((void*)pRet);
								continue;
							}
							if (nStrLen - nStart < 2) //没有越界
							{
								if (pRet[0] == str[nStart])
								if (pRet[1] == 0)
								{
									data[3] = '=';
									free((void*)pRet);
									printf("%s", data);
									goto Next;
								}
							}

							if (nStrLen - nStart <3) //没有越界
							{
								if (pRet[0] == str[nStart])
								if (pRet[1] == str[nStart + 1])
								if (pRet[2] == 0)
								{
									free((void*)pRet);
									printf("%s", data);
									goto Next;
								}
							}

							if ((nStart + 2) <= nStrLen - 1) //没有越界
							{
								if (pRet[0] == str[nStart])
								if (pRet[1] == str[nStart + 1])
								if (pRet[2] == str[nStart + 2])
								{
									free((void*)pRet);
									printf("%s", data);
									goto Next;
								}
							}
							free((void*)pRet);
						}
					}
				}
			}
		}
	Next:
		int nFlag = 0;
		//printf("\n次数统计 %d \n", nCount);
	}
	printf("\n加密算法结束\n");
	return 0;
}

#endif //STRING_ENCRYTION_H__