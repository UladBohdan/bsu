// Dubkou p.47 #4
// 16 ->10

#include <iostream>

extern "C" int __cdecl check(char*);

using namespace std;

int main()
{
	char a[10];
	cout << "number in 16 (not too big, please!): ";
	gets(a);
	int temp=check(a);
	if (temp==-1)
		cout << "not in 16" << endl;
	else
		cout << "in 10: " << temp << endl;

	return 0;
}