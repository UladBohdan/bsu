//Dubkou p.42 #11
//the shortest word

#include <iostream>

using namespace std;

int main()
{
	int mn=50, n, pos[50], last=0;
	char a[50];
	cout << "string with spaces: ";
	gets(a);
	n=strlen(a);
	__asm
	{
		lea edi, a
		lea ebx, pos
		mov ecx, n
		mov [edi+ecx], ' '
		inc ecx
		inc n
		mov [edi+ecx], '\0'
		mov al, ' '
	rep1:
		repne scasb
		jz topos
		jecxz end1
	topos:
		mov edx, n
		sub edx, ecx
		sub edx, last
		dec edx
		mov esi, n
		sub esi, ecx
		mov last, esi
		cmp edx, 0
		jle rep1
		cmp mn, edx
		jle rep1
		mov mn, edx
		jmp rep1
	end1:		
	}
	cout << "length of the shortest word: " << mn << endl;
	return 0;
}