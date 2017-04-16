// Dubkou p.42 #3
// palindrom

#include <iostream>

using namespace std;

int main()
{
	char a[20];
	int n, pal=1;
	cout << "your string: ";
	gets(a);
	n=strlen(a);
	__asm
	{
		lea esi, a
		mov eax, n
		cmp eax, 1
		je finish
		mov ecx, 2
		cdq
		idiv ecx
		mov ecx, eax
		mov edx, n
		dec edx
	substr:
		mov al, [esi]
		mov bl, [esi+edx]
		cmp al, bl
		jne notpal
		inc esi
		dec edx
		dec edx
		loop substr
		jmp finish
	notpal:
		mov pal, 0
		jmp finish
	finish:
	}
	cout << (pal==1 ? "palindrom" : "not palindrom" ) << endl;
	return 0;
}