#include <WINDOWS.H>
#include "StringDecrypt.h"
#include "StringEncrytion.h"

int main(int agrc, char** agrv)
{
	const CHAR *v1;
	const CHAR *v2;
	const CHAR *v3;
	const CHAR *v4;

	HMODULE v0 = GetModuleHandleA("Kernel32");
	if (v0)
	{
		// º”√‹
		v1 = (const CHAR *)StringEncry("VirtualQueryEx");
		// Ω‚√‹
		v1 = (const CHAR *)StringDecrypt("l3B7dXRobYhtbW5qSQ==");// VirtualAlloc
		int fun1 = (int)GetProcAddress(v0, v1);
		v2 = (const CHAR *)StringDecrypt("l3B7dXRobYd7ZGRJ");  // VirtualFree
		int fun2 = (int)GetProcAddress(v0, v2);
		v3 = (const CHAR *)StringDecrypt("l3B7dXRobZh0ZHuAhIFJ"); // VirtualQueryEx
		int fun3 = (int)GetProcAddress(v0, v3);
		v4 = (const CHAR *)StringDecrypt("l3B7dXRobZl7bnVkanWEgUk="); // VirtualProtectEx
		int fun4 = (int)GetProcAddress(v0, v4);
	}
	return 0;
}
