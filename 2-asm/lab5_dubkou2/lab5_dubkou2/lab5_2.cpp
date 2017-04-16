// Dubkou p.47 #2

#include <iostream>

extern "C" char* __stdcall cont(char*,char*);

using namespace std;

int main()
{
	char a[20], b[20];
	cout << "your strings: ";
	gets(a);
	gets(b);
	char* c=cont(a,b);
	cout << "answer: ";
	puts(c);
	return 0;
}