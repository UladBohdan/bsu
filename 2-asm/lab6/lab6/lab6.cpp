#include "stdafx.h"
#include <iostream>
#include <iomanip>

extern "C" void __fastcall init(int*,int);
extern "C" int* __fastcall center();
extern "C" int* __fastcall secondless();
extern "C" int* __fastcall closetoav();
extern "C" int* __fastcall freqrep();
extern "C" int* __fastcall sumdig(int*,int);

using namespace std;

int main()
{
	int n, a[100];
	int* ans;
	cout << "array size: ";
	cin >> n;
	cout << "array: ";
	for (int i=0; i<n; i++)
		cin >> a[i];
	init(a,n);
	cout << endl << "ANSWERS (index = address-begin+1):" << endl;
	ans=center();
	cout << "1. center element (index): " << ans-a+1 << endl;
	ans=secondless();
	cout << "2. second less element (index): " << ans-a+1 << endl;
	ans=closetoav();
	cout << "3. closest to average (index): " << ans-a+1 << endl;
	ans=freqrep();
	cout << "4. most repeated (index, -1 for zero repeats): " << ans-a+1 << endl;
	ans=sumdig(a,n);
	cout << "5. smallest digit sum (index): " << ans-a+1 << endl;
	return 0;
}