//Dubkou p.42 #7
//removes spaces

#include <iostream>

using namespace std;

int main()
{
	char a[50], b[50];
	int n;
	cout << "string with spaces: ";
	gets(a);
	n=strlen(a);
	__asm
	{
		lea ebx, b
		cld
		mov ecx, n
		mov al, ' '
		lea edi, a
beg1:
		or al, 0
		cmp ecx, 0
		je end1
		rep scasb
		jnz repsp
		jmp beg1
repsp:
		mov dl, byte ptr[edi-1]
		mov [ebx], dl
		inc ebx
		jmp beg1
end1:
		mov [ebx], '\0'
		mov ecx, n
		lea edi, a
		lea esi, b
		rep movsb
	}
	cout << "without spaces: ";
	puts(a);
	return 0;
}