#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "stack_own.h"

using namespace std;

class complex;
class stack_own;

int main()
{
	//Example of using
	cout << endl << endl << "Several complex numbers: ";
	complex z1(0,7), z2(8,12.6), z3(9), z4;
	z1.show(); cout << " ";
	z2.show(); cout << " ";
	z3.show(); cout << " ";
	z4.show(); cout << " ";
	cout << endl << "A real number as complex object: ";
	z4=89.6;
	z4.show(); cout << endl;
	cout << endl;
	cout << "Array of random complex numbers: ";
	complex z[5];
	srand(time(NULL));
	for (int i=0; i<5; i++)
	{
		complex tmp((rand()%200)/10.,(rand()%100)/10.);
		z[i]=tmp;
		z[i].show();
		cout << " ";
	}
	cout << endl;
	cout << "Type N and your N complex numbers (as two parts - real and imaginary): ";
	int n;
	double a, b;
	cin >> n;
	stack_own s;
	for (int i=0; i<n; i++)
	{
		cin >> a >> b;
		complex tmp(a,b);
		s.push(tmp);
	}
	cout << endl;
	cout << "Reversing using stack: ";
	while (!s.empty())
	{
		s.top().show();
		cout << " ";
		s.pop();
	}
	cout << endl << endl;
	return 0;
}
