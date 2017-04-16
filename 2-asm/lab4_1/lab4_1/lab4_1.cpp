#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int n, a[20][20], nmx=0, mx[100], i, j;
	cout << "size of matrix: ";
	cin >> n;
	cout << "matrix:" << endl;
	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
			cin >> a[i][j];
	//cout << a[8] << endl;
	//return 0;
	__asm
	{
		mov i, 0
		mov j, 0
		xor esi, esi
cycle:
		mov edx, n
		dec edx
		mov ebx, i
		imul ebx, 20
		add ebx, j		
		mov eax, a[ebx*4]
test1:
		cmp i, 0
		je test2
		// i not eq 0
		mov ebx, i
		dec ebx
		imul ebx, 20
		add ebx, j
		mov ecx, a[ebx*4]
		cmp eax, ecx
		jl fintest // exit
	subtest1:
		cmp j, 0
		je subtest2
		mov ebx, i
		dec ebx
		imul ebx, 20
		add ebx, j
		dec ebx
		mov ecx, a[ebx*4]
		cmp eax, ecx
		jl fintest // exit
	subtest2:
		cmp j, edx
		je test2
		mov ebx, i
		dec ebx
		imul ebx, 20
		add ebx, j
		inc ebx
		mov ecx, a[ebx*4]
		cmp eax, ecx
		jl fintest // exit
test2:
		cmp j, 0
		je test3
		mov ebx, i
		imul ebx, 20
		add ebx, j
		dec ebx
		mov ecx, a[ebx*4]
		cmp eax, ecx
		jl fintest
test3:
		cmp j, edx
		je test4
		mov ebx, i
		imul ebx, 20
		add ebx, j
		inc ebx
		mov ecx, a[ebx*4]
		cmp eax, ecx
		jl fintest
test4:
		cmp i, edx
		je test5
		mov ebx, i
		inc ebx
		imul ebx, 20
		add ebx, j
		mov ecx, a[ebx*4]
		cmp eax, ecx
		jl fintest
	subtest3:
		cmp j, 0
		je subtest4
		mov ebx, i
		inc ebx
		imul ebx, 20
		add ebx, j
		dec ebx
		mov ecx, a[ebx*4]
		cmp eax, ecx
		jl fintest
	subtest4:
		cmp j, edx
		je test5
		mov ebx, i
		inc ebx
		imul ebx, 20
		add ebx, j
		inc ebx
		mov ecx, a[ebx*4]
		cmp eax, ecx
		jl fintest
test5:
		// have maximum
		mov ebx, nmx
		mov ecx, i
		inc ecx
		mov mx[ebx*4], ecx
		mov ecx, j
		inc ecx
		inc ebx
		mov mx[ebx*4], ecx
		inc ebx
		mov mx[ebx*4], eax
		add nmx, 3
fintest:
		cmp j, edx
		je subexit1
		jmp subexit2
	subexit1:
		cmp i, edx
		je end1
		mov j, 0
		inc i
		jmp cycle
	subexit2:
		inc j
		jmp cycle
end1:
	}
	cout << endl << "matrix local maximums:" << endl;
	for (int k=0; k<nmx; k+=3)
		cout << " " << mx[k] << " " << mx[k+1] << "  appr value: " << mx[k+2] << endl;

	//Sorting rows
	int cntr=n, pos, toswap;
	__asm
	{
		mov pos, 0
		mov edx, n
		dec edx
rep1:
		dec cntr
		xor ebx, ebx
	rep2:
		mov pos, ebx
		jmp cmpandswap
	returnhome:
		mov ebx, pos
		inc ebx
		cmp ebx, edx
		jne rep2
		mov ecx, cntr
		cmp ecx, 0
		je end2
		jmp rep1

cmpandswap: // (pos) and (pos+1) rows
		xor esi, esi
		mov toswap, 0
	cmpr:
		mov ebx, pos
		imul ebx, 20
		add ebx, esi
		mov eax, a[ebx*4]
		add ebx, 20
		cmp eax, a[ebx*4]
		je way2
		cmp eax, a[ebx*4]
		jl finishcmpr
		jmp way1
	way1:
		mov toswap, 1
		jmp finishcmpr
	way2:
		inc esi
		cmp esi, n
		je finishcmpr
		jmp cmpr

	finishcmpr:
		cmp toswap, 0
		je returnhome
		// else swap:
		mov ecx, n
		mov ebx, pos
		imul ebx, 20
	swapp:
		mov eax, a[ebx*4]
		add ebx, 20
		mov esi, a[ebx*4]
		mov a[ebx*4], eax
		sub ebx, 20
		mov a[ebx*4], esi
		inc ebx
		loop swapp
		jmp returnhome


end2:
	}
	cout << endl << "matrix sorted by rows:" << endl;
	for (i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
			cout << " " << a[i][j];
		cout << endl;
	}

	//sort by max element
	int mx1, mx2;
	__asm // modified prev block
	{
		mov pos, 0
		mov edx, n
		mov cntr, edx
		dec edx
rep1X:
		dec cntr
		xor ebx, ebx
	rep2X:
		mov pos, ebx
		jmp cmpandswapX
	returnhomeX:
		mov ebx, pos
		inc ebx
		cmp ebx, edx
		jne rep2X
		mov ecx, cntr
		cmp ecx, 0
		je end3
		jmp rep1X

cmpandswapX: // (pos) and (pos+1) rows
		mov toswap, 0

		xor esi, esi
		mov ebx, pos
		imul ebx, 20
		mov eax, a[ebx*4]
		mov mx1, eax
	frst:
		inc ebx
		inc esi
		cmp esi, n
		je end_frst
		mov eax, a[ebx*4]
		cmp eax, mx1
		jl frst
		mov mx1, eax
		jmp frst
	end_frst:
		xor esi, esi
		mov ebx, pos
		inc ebx
		imul ebx, 20
		mov eax, a[ebx*4]
		mov mx2, eax
	scnd:
		inc ebx
		inc esi
		cmp esi, n
		je cmp_mxs
		mov eax, a[ebx*4]
		cmp eax, mx2
		jl scnd
		mov mx2, eax
		jmp scnd

	cmp_mxs:
		mov eax, mx1
		cmp eax, mx2
		jl finishcmprX
		mov toswap, 1

	finishcmprX:
		cmp toswap, 0
		je returnhomeX
		// else swap:
		mov ecx, n
		mov ebx, pos
		imul ebx, 20
	swappX:
		mov eax, a[ebx*4]
		add ebx, 20
		mov esi, a[ebx*4]
		mov a[ebx*4], eax
		sub ebx, 20
		mov a[ebx*4], esi
		inc ebx
		loop swappX
		jmp returnhomeX

end3:
	}
	cout << endl << "matrix sorted by max element in each row:" << endl;
	for (i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
			cout << " " << a[i][j];
		cout << endl;
	}
	return 0;
}