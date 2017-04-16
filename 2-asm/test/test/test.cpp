#include <iostream>

extern "C" int __fastcall divs(int*,int);

using namespace std;

int main()
{
	int b, a[100], n;
	cout << "your number: ";
	cin >> b;
	n=divs(a,b);
	cout << "number of dividers: " << n << endl;
	for (int i=0; i<n; i++)
		cout << " " << a[i];
	cout << endl;
	return 0;
}