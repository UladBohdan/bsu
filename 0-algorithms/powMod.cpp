#include <iostream>

using namespace std;

// returns value of (x^n % d)
// from interviewbit
// actually, maybe works just for int

long long pow(long long x, long long n, long long d) {
    int sign=0;
    if (x<0 && n%2==1)
        sign=d;
    if (x==0)
        return 0;
    if (n==0)
        return 1;
    if (n==1)
        return x%d+sign; 
    if (n%2==0)
        return pow((x*x)%d, n/2, d)%d+sign;
    else
        return (pow((x*x)%d,(n-1)/2,d)*x)%d+sign;
}

int main()
{
	cout << pow(2,3,3);
	return 0;
}
