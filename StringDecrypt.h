/*
		解密算法
*/
#ifndef STRING_DECRYPT_H__
#define STRING_DECRYPT_H__ 1

#include <stdio.h>
char EncodeTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
int __cdecl GetAlphaPos(char alpha)
{
	char *i;
	char szTmp = EncodeTable[0];
	for (i = &EncodeTable[0];; szTmp = *i)
	{
		if (!szTmp)
			return -1;
		if (szTmp == alpha)
			break;
		++i;
	}
	int nRet = i - &EncodeTable[0];
	return nRet;
}

#define _BYTE byte
signed int StringDecryptCore(const char *str, void **nResult)
{
	int nPos1 = 0;
	int nResult1 = 0;
	int nPos2 = 0;
	int nResult2 = 0;
	int nPos3 = 0;
	int nResult3 = 0;
	int nPos4 = 0;
	size_t nRetSize = 0;

	signed int nFlag = 0;
	int nLen = strlen(str) + 1;
	_BYTE *buffer = (_BYTE *)malloc(nLen*sizeof(char));
	memset(buffer, 0, nLen*sizeof(char));
	_BYTE *oldbuffer = buffer;
	if (*str)
	{
		int ptStr = (int)(str + 2); // 第一个字母的ansi数值加2
		do
		{
			if (nFlag)
				break;
			// 判断字母是否在字符表中
			nPos1 = GetAlphaPos(*(_BYTE *)(ptStr - 2));  //取第一个字母
			if (nPos1 < 0)
				break;
			nResult1 = nPos1 << 6;  // 算法一
			nPos2 = GetAlphaPos(*(_BYTE *)(ptStr - 1));  // 取第二个字母
			if (nPos2 < 0)
				return -1;
			nResult2 = (nPos2 + nResult1) << 6;  // 算法二
			if (*(_BYTE *)ptStr == 61)  // '='
			{
				nFlag = 1;
			}
			else
			{
				nPos3 = GetAlphaPos(*(_BYTE *)ptStr);	// 取第三个字母
				if (nPos3 < 0)
					return -1;
				nResult2 += nPos3;
			}
			// 算法三
			char ch = *(_BYTE *)(ptStr + 1);  // 取第四个字母
			nResult3 = nResult2 << 6;
			if (ch == 61)  // '='，等号为无效字符
			{
				++nFlag;
			}
			else
			{
				if (nFlag)
					return -1;
				nPos4 = GetAlphaPos(ch);
				if (nPos4 < 0)
					return -1;
				nResult3 += nPos4;
			}
			// 算法四，解码出三个字母
#define BYTE1(x) (((_BYTE*)&x)[1])
#define BYTE2(x) (((_BYTE*)&x)[2])
			if (nFlag < 3)
				*buffer++ = BYTE2(nResult3);
			if (nFlag < 2)
				*buffer++ = BYTE1(nResult3);
			if (nFlag < 1)
				*buffer++ = nResult3;
			ptStr += 4;
			//printf("%4d %4d %4d %4d\n", nPos1, nPos2, nPos3, nPos4);
		} while (*(_BYTE *)(ptStr - 2));
	}
	//printf("---------------------\n");
	nRetSize = buffer - oldbuffer;
	*nResult = realloc(oldbuffer, nRetSize);  //  97 70 7b 75 74 68 6d 88 6d 6d 6e 6a 49   ?p{uthm?mmnjI
	return nRetSize;
}

int StringDecrypt(const char *str)
{
	signed int nStrLen;
	int ptBuf = 0;
	nStrLen = StringDecryptCore(str, (void **)&ptBuf);
	for (int i = 0; i < nStrLen; ++i)
		*(_BYTE *)(i + ptBuf) = (*(_BYTE *)(i + ptBuf) - 36) ^ 0x25;
	return ptBuf;
}

#endif //STRING_DECRYPT_H__ 1