#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int a, b, gcd;
	cout << "a and b: ";
	cin >> a >> b;
	__asm
	{
		mov eax, a
		mov ebx, b
rep1:
		cdq
		idiv ebx
		mov eax, ebx
		mov ebx, edx
		cmp ebx, 0
		jne rep1
		jmp fin
		cmp eax, ebx
		jne rep1
		jmp fin
fin:
		mov gcd, eax
		mov eax, a
		cdq
		idiv gcd
		mov a, eax
		mov eax, b
		idiv gcd
		mov b, eax
	}
	cout << "answer: " << a << "/" << b << endl;
	return 0;
}