#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int a, n;
	cout << "input number: ";
	cin >> a;
	__asm
	{
	//	mov eax, 100101110b
		mov eax, a
		mov ecx, 2
		mov n, 0
rep1:
		inc n
		cdq
		idiv ecx
		cmp eax, 0
		je end1
		jmp rep1
end1:
	}
	cout << "answer: " << n << endl;
	return 0;
}