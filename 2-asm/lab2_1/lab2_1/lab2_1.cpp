#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int a, b, s, ev, temp, dig;
	bool sym=false;
	cout << "number: ";
	cin >> a;
	temp=a;
	__asm
	{
		mov s, 0
		mov ev, 0
again1:
		mov eax, temp
		mov ecx, 10
		cdq
		idiv ecx
		add s, edx
		mov temp, eax
		mov eax, edx
		mov ecx, 2
		cdq
		idiv ecx
		cmp edx, 0
		je incev1
		jmp M1
M1:
		cmp temp, 0
		jne again1
		jmp end1
incev1:
		inc ev
		jmp M1
end1:
	}
	cout << "sum of digits: " << s << endl;
	cout << "number of even digits: " << ev << endl;
	temp=a;
	__asm
	{
		mov b, 0
		mov ecx, 10
again2:
		mov eax, temp
		cdq
		idiv ecx
		mov dig, edx
		mov temp, eax
		mov eax, b
		imul ecx
		add eax, dig
		mov b, eax
		mov eax, temp
		cmp eax, 0
		jne again2

		mov eax, a
		cmp eax, b
		jne end2
		mov sym, 1
end2:
	}
	cout << (sym ? "Symmetric." : "Not symmetric.") << endl;
	return 0;
}