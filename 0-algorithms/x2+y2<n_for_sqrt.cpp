#include <iostream>

using namespace std;

// Number of solutions for x*x+y*y < n
// x,y > 0
// for SQRT(N)

int main()
{
	int n, ans=0;
	cin >> n;
	int k=0, l=0;
	while (l*l<n)
		l++;
	cout << l << endl;
	while (l>0)
	{
		ans+=l;
		k++;
		while (l>0 && k*k+(l-1)*(l-1)>=n)
			l--;
	}
	cout << ans;
	return 0;
}
