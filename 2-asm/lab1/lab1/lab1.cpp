#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int a, b, ans;
	cout << "input a: ";
	cin >> a;
	__asm
	{
		mov eax, a
		imul a
		imul a
		imul a
		imul a
		mov ecx, eax
		mov eax, a
		imul a
		imul a
		add ecx, eax
		add ecx, a
		mov ans, ecx
	}
	cout << "1. " << ans << endl;
	if (a!=4)
	{
		__asm
		{
			mov eax, a
			imul a
			imul a
			imul a
			sub eax, 2
			mov ecx, a
			sub ecx, 4
			cdq
			idiv ecx
			mov ans, eax
		}
		cout << "2. " << ans << endl;
	}
	else
		cout << "2. error" << endl;
	
	cout << "input b for ax+b=0: ";
	cin >> b;
	bool exist=false;
	if (a==0)
		cout << (b==0 ? "3. all" : "3. No solution.") << endl;
	else
	{
		__asm
		{
			mov eax, b
			mov ecx, -1
			imul ecx
			idiv a
			cmp edx, 0
			jne end_
			mov ans, eax
			mov exist, 1
		end_:
		}
		if (exist)
			cout << "3. " << ans << endl;
		else
			cout << "3. No solution." << endl;
	}
	// 4
	if (a==0)
		cout << "4. inf" << endl;
	else
	{
		int n=1;
		__asm
		{
			mov eax, a
	_start4:
			imul a
			jno _do4
			jmp _end4
	_do4:
			inc n
			jmp _start4
	_end4:
		}
		cout << "4. n=" << n << endl;
	}
	cout << "5. Solutions of 100=2x+3y:" << endl;
	int x=0, y;
	__asm
	{
cycle:
		inc x
		mov eax, x
		mov ecx, -2
		imul ecx
		add eax, 100
		cdq
		mov ecx, 3
		idiv ecx
		mov y, eax
		cmp edx, 0
		jne cycle
	}
		cout << " " << x << " " << y << endl;
	__asm
	{
		cmp x, 50
		je endd_
		jmp cycle
endd_:
	}
	return 0;
}

