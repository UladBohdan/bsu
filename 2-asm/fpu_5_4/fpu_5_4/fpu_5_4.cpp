#include <iostream>

using namespace std;

extern "C" double* __stdcall func(double, double);

int main()
{
	double x, eps;
	cout << "x, eps: ";
	cin >> x >> eps;
	double* ans=func(x,eps);
	cout << "answer: " << *ans << endl;
	return 0;
}