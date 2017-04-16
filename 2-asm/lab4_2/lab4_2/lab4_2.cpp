// byte edition

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
	int n, m;
	unsigned int tb=0; // tb - for max 32 elements
	cout << "matrix height and width ( n*m<=32 ): ";
	cin >> n >> m;
	cout << "input matrix: " << endl;
	int deg=1, tmp;
	srand(time(NULL));
	for (int i=0; i<n*m; i++)
	{
	//	cin  >> tmp;
		tmp=rand()%2;
		cout << tmp << " ";
		if (i%m==m-1) cout << endl; 

		tb+=(tmp*deg);
		deg<<=1;
	}
	if (!tb)
	{
		cout << "zero matrix." << endl;
		return 0;
	}
	int ans=0, cur=0;
	__asm // rows
	{
		mov eax, tb
		xor esi, esi // max
rep1:
		inc cur
		mov ecx, m
		xor ebx, ebx //max len
	rep2:		
		inc ebx
		mov edx, eax
		and edx, 1b
		shr eax, 1
		imul ebx, edx
		cmp ebx, esi
		jle cont2
		mov esi, ebx
		mov edx, cur
		mov ans, edx
	cont2:
		loop rep2

		mov edi, cur
		cmp edi, n
		jne rep1
	}
	cout << "Row with max sequence of 1: " << ans << endl;
	__asm // cols
	{
		mov cur, 0
		xor esi, esi // max
rep1x:
		inc cur
		mov ecx, n
		xor ebx, ebx //max len
	rep2x:		
		inc ebx
		mov edx, tb
		mov eax, ecx
		dec eax
		imul eax, m
		add eax, cur
		dec eax
		mov edi, 1

	shiftedi:
		cmp eax, 0
		je endshift
		shl edi, 1
		dec eax
		jmp shiftedi

	endshift:		
		and edx, edi
		
		cmp edx, 0
		je contx
		mov edx, 1
	contx:
		imul ebx, edx
		cmp ebx, esi
		jle cont2x
		mov esi, ebx
		mov edx, cur
		mov ans, edx
	cont2x:
		loop rep2x

		mov edi, cur
		cmp edi, m
		jne rep1x
	}
	cout << "Col with max sequence of 1: " << ans << endl;
	int q[40], qpos=0, shifted=1, qsize=0;
	__asm // number of areas
	{
		mov ans, 0
		mov cur, 0
global1:
		mov eax, tb
		mov ecx, cur
	getcurbit:
		cmp ecx, 0
		je endgetbit
		shr eax, 1
		dec ecx
		jmp getcurbit
	endgetbit:
		and eax, 1	// now current bit in eax

		cmp eax, 0
		jne finishloop
		// bit==0 and should be added to queue
		lea ebx, q
		mov eax, qpos
		imul eax, 4
		add ebx, eax
		mov eax, cur
		mov [ebx], eax
		inc ans
		inc qsize
		jmp queuenotempty

	finishloop:
		inc cur
		mov ecx, n
		imul ecx, m
		cmp cur, ecx
		je end2
		jmp global1

queuenotempty:	// finishloop to return
		mov eax, qpos
		inc qpos
		imul eax, 4
		lea ebx, q
		add ebx, eax
		mov esi, [ebx]	// in esi: bit we work with
		// now make this bit 1 in TB
		mov edi, 1
		mov ecx, esi
	shiftedi2:
		cmp ecx, 0
		je endshiftedi2
		shl edi, 1
		dec ecx
		jmp shiftedi2
	endshiftedi2:
		or tb, edi   

		// now cheching and trying to add esi+-1 & esi+-m to queue
try1:
		mov eax, esi
		cdq
		mov ebx, m
		idiv ebx	//in edx: (esi mod m)
		cmp edx, 0
		je try2
		// checking -1
		mov eax, esi
		dec eax
		mov edi, tb
	getbit3:
		cmp eax, 0
		je endgetbit3
		shr edi, 1
		dec eax
		jmp getbit3
	endgetbit3:
		and edi, 1
		cmp edi, 0
		jne try2
		//have 0 in this bit	-	adding to queue
		mov eax, qsize
		imul eax, 4
		lea ebx, q
		add ebx, eax
		mov eax, esi
		dec eax
		mov [ebx], eax
		inc qsize
		
try2:
		mov eax, esi
		cdq
		mov ebx, m
		idiv ebx	//in edx: (esi mod m)
		mov edi, m
		dec edi
		cmp edx, edi
		je try3
		// checking +1
		mov eax, esi
		inc eax
		mov edi, tb
	getbit4:
		cmp eax, 0
		je endgetbit4
		shr edi, 1
		dec eax
		jmp getbit4
	endgetbit4:
		and edi, 1
		cmp edi, 0
		jne try3
		//have 0 in this bit	-	adding to queue
		mov eax, qsize
		imul eax, 4
		lea ebx, q
		add ebx, eax
		mov eax, esi
		inc eax
		mov [ebx], eax
		inc qsize

try3:	// -m
		mov eax, esi
		cmp eax, m
		jl try4
		// we can check -m
		sub eax, m
		mov edi, tb
	getbit5:
		cmp eax, 0
		je endgetbit5
		shr edi, 1
		dec eax
		jmp getbit5
	endgetbit5:
		and edi, 1
		cmp edi, 0
		jne try4
		// having zero.		adding to queue
		mov eax, qsize
		imul eax, 4
		lea ebx, q
		add ebx, eax
		mov eax, esi
		sub eax, m
		mov [ebx], eax
		inc qsize

try4:
		mov eax, n
		dec eax
		imul eax, m
		cmp eax, esi
		jle stoptrying
		//we can check +m
		mov eax, esi
		add eax, m
		mov edi, tb
	getbit6:
		cmp eax, 0
		je endgetbit6
		shr edi, 1
		dec eax
		jmp getbit6
	endgetbit6:
		and edi, 1
		cmp edi, 0
		jne stoptrying
		// having zero.		adding to queue
		mov eax, qsize
		imul eax, 4
		lea ebx, q
		add ebx, eax
		mov eax, esi
		add eax, m
		mov [ebx], eax
		inc qsize

	stoptrying:

		mov eax, qsize
		cmp qpos, eax
		jl queuenotempty
		jmp finishloop	// exit

end2:
	}
	cout << "Number of zero areas: " << ans << endl;
	return 0;
}