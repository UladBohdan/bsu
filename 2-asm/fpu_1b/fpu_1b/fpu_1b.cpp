#include <iostream>

using namespace std;

int main()
{
	float a, b, c, l, r, x=-10, lval, rval, avval, av;
	int n=0, signl=0, signr=0, pos=0, tempint;	// 0 - less than 0; 1 - grower
	float arr[3], sol[3];
	float const1=0.01, const2=2;
	cout << "Input double a,b,c for x3+ax2+bx+c:" << endl;
	cin >> a >> b >> c;
	__asm
	{
		finit
		// value of -10 to right
		fld x
		fadd a
		fmul x
		fadd b
		fmul x
		fadd c
		fst r
		ftst
		fstsw ax
		sahf
		jc global_cycle
		mov signr, 1
global_cycle:
		// R to L and new R
		mov eax, signr
		mov signl, eax
		mov eax, r
		mov l, eax
		mov signr, 0
		finit
		fld x
		fadd const1
		fst x
		finit
		fld x
		fadd a
		fmul x
		fadd b
		fmul x
		fadd c
		fst r
		ftst
		fstsw ax
		sahf
		jc contin1
		mov signr, 1
	contin1:
		mov eax, signl
		add eax, signr
		cmp eax, 1
		jne contin2
		mov eax, x
		lea ebx, arr
		mov ecx, n
		mov [ebx+ecx*4], eax
		inc n
	contin2:
		finit
		fld x
		fist tempint
		cmp tempint, 10
		jl global_cycle
		
		// RANGES ARE FOUND
		// not diving them on 2
		
		cmp n, 0
		je finish

		mov ecx, n
rep1:
		lea ebx, arr
		mov eax, n
		sub eax, ecx
		mov edx, [ebx+eax*4]
		mov l, edx
		mov r, edx
		finit
		fld l
		fsub const1
		fst l
		xor esi, esi

	divings:
		inc esi
		finit
		fld l
		fld r
		fadd
		fld const2
		fdiv
		fst av
		//now we should compare (L+R)/2 value with 0 and update L and R
		finit
		fld l
		fadd a
		fmul l
		fadd b
		fmul l
		fadd c
		fst lval

		fld lval
		ftst
		fstsw ax
		sahf
		jc contin4
		mov tempint, 0
		jmp contin5
	contin4:
		mov tempint, 1
	contin5:
		/*
		finit
		fld r
		fadd a
		fmul r
		fadd b
		fmul r
		fadd c
		fst rval
		*/
		finit
		fld av
		fadd a
		fmul av
		fadd b
		fmul av
		fadd c
		fst avval
		
		fld avval
		ftst
		fstsw ax
		sahf
		jc l_closer
		fld av
		cmp tempint, 0
		jne oldstyle1 
		fstp l
		jmp contin3
		oldstyle1:
		fstp r
		jmp contin3
	l_closer:
		fld av
		cmp tempint, 0
		jne oldstyle2
		fstp r
		jmp contin3
		oldstyle2:
		fstp l
		jmp contin3

	contin3:
		cmp esi, 15
		jne divings
		lea ebx, sol
		mov eax, n
		sub eax, ecx
		fld av
		fst [ebx+eax*4] 

		dec ecx
		cmp ecx, 0
		jne rep1
finish: 
	}
	if (n==0)
	{
		cout << "No solutions on the range." << endl;
		return 0;
	}
	cout << endl << n << " ranges:" << endl;
	for (int i=0; i<n; i++)
		cout << arr[i]-0.01 << " " << arr[i] << endl;
	cout << endl << "Solutions:" << endl;
	for (int i=0; i<n; i++)
		cout << sol[i] << endl;
	return 0;
}