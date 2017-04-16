// Dubkou p.24 #4

#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int n, a[20], b[20], un[20], ints[20], dif[20];
	cout << "size of sets: ";
	cin >> n;
	cout << "first set : ";
	for (int i=0; i<n; i++)
		cin >> a[i];
	cout << "second set: ";
	for (int i=0; i<n; i++)
		cin >> b[i];
	__asm
	{
		mov ecx, n
		xor ebx, ebx
beg1:
		mov eax, a[ebx*4]
		or eax, b[ebx*4]
		mov un[ebx*4], eax
		inc ebx
		loop beg1

		mov ecx, n
		xor ebx, ebx
beg2:
		mov eax, a[ebx*4]
		and eax, b[ebx*4]
		mov ints[ebx*4], eax
		inc ebx
		loop beg2

		mov ecx, n
		xor ebx, ebx
beg3:
		mov eax, a[ebx*4]
		xor eax, b[ebx*4]
		and eax, a[ebx*4]
		mov dif[ebx*4], eax
		inc ebx
		loop beg3
	}
	cout << "union: ";
	for (int i=0; i<n; i++) cout << un[i] << " ";
	cout << endl << "intersection: ";
	for (int i=0; i<n; i++) cout << ints[i] << " ";
	cout << endl << "difference: ";
	for (int i=0; i<n; i++) cout << dif[i] << " ";
	cout << endl;
	return 0;
}