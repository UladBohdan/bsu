// Dubkou p.24 #1

//ASM BINARY SEARCH

#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int n, b, l=0, r, pos, a[20];
	bool exist=false;
	cout << "array size: ";
	cin >> n;
	r=n-1;
	cout << "input an array: ";
	for (int i=0; i<n; i++)
		cin >> a[i];
	cout << "input a number to search in array: ";
	cin >> b;	
	__asm
	{
rep1:
		mov eax, l	
		add eax, r
		xor ebx, ebx

		cdq
		mov ecx, 2
		idiv ecx
		mov ebx, eax
		mov eax, a[ebx*4]
		// Current position is now in ebx, value - in eax
		
		cmp eax, b
		je end_ex
		cmp eax, b
		jg divr1
		jmp mull1
divr1:
		mov r, ebx
		jmp cont
mull1:
		mov l, ebx
		jmp cont
cont:
		mov eax, l
		cmp eax, r
		je check_eq
		
		mov eax, l
		mov edx, r
		dec edx
		cmp eax, edx
		je oneless

		jmp rep1
check_eq:
		mov eax, a[ebx*4]
		cmp eax, b
		je end_ex
		jmp end_fin
oneless:
		mov ebx, l
		mov eax, a[ebx*4]
		cmp eax, b
		je end_ex
		inc ebx
		mov eax, a[ebx*4]
		cmp eax, b
		je end_ex
		jmp end_fin
end_ex:
		mov exist, 1
		mov pos, ebx
		inc pos
end_fin:
	}
	if (exist)
		cout << "Exists! on position " << pos << endl;
	else
		cout << "No element in array." << endl;
	return 0;
}