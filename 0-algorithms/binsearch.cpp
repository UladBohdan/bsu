#include <iostream>

//Returns the place where val can be located

using namespace std;

int binarysearch (int a[], int n, int val)
{
    int l=0, r=n-1;
    while (l<=r)
    {
        int t=(l+r)/2;
        if ((a[t]==val && t==0) || (t>0 && a[t]==val && a[t-1]<val))
			return t;
        else if (a[t]>=val)
            r=t-1;
        else if (a[t]<val)
            l=t+1;
    }
    return -1;
}

int lower(const vector<int> &a, int val) {
    int l=0, r=a.size()-1;
    while (l<=r) {
        int t=(l+r)/2;
        if ((a[t]==val && t==0) || (a[t]==val && t>0 && a[t-1]<val))
            return t;
        else if (a[t]>=val)
            r=t-1;
        else
            l=t+1;
    }
    return -1;
}

int upper(const vector<int> &a, int val) {
    int l=0, r=a.size()-1;
    while (l<=r) {
        int t=(l+r)/2;
        if ((a[t]==val && t==a.size()-1) || (a[t]==val && t<a.size()-1 && a[t+1]>val))
            return t;
        else if (a[t]>val)
            r=t-1;
        else
            l=t+1;
    }
    return -1;
}

int main()
{
	int a[]={5,7,10,11,11,18,18,18,18,19,23};
	int b[]={1,2,2,4,5};
	cout << binarysearch(b,5,5);
    return 0;
}
