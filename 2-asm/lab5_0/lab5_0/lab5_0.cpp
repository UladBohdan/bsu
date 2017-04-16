#include "stdafx.h"
#include <iostream>

extern "C" int __stdcall count(int, int, int);

using namespace std;

int main()
{
	int a, b, x;
	cout << "a, x, b: ";
	cin >> a >> x >> b;
	cout << "a*x+b=" << count(a,x,b) << endl;
	return 0;
}