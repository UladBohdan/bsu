#include "stdafx.h"
#include <iostream>

extern "C" int __fastcall ppp(int,int);

using namespace std;

int main()
{
	int a, n;
	cout << "a, n: ";
	cin >> a >> n;
	cout << "a^n=" << ppp(a,n) << endl;
	return 0;
}