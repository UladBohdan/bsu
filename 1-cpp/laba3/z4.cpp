#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(string a, string b)
{
    int i=0;
    while (i<a.length() && i<b.length() && a[i]==b[i])
        i++;
    if (i==a.length() && i==b.length())
        return true;
    if (i==a.length())
    {
	//	while (i<b.length() && b[i]==b[0])
     //       i++;
     //   if (i==b.length())
      //      return true;
        if (b[i]>b[0]  || (b[i]==b[0] && b[i]>a[a.length()-1]))
            return true;
        else
            return false;
    }
    if (i==b.length())
    {
	//	while (i<a.length() && a[i]==a[0])
     //       i++;
     //   if (i==a.length())
      //      return true;
        if (a[i]>a[0]  || (a[i]==a[0] && a[i]>b[b.length()-1]))
            return false;
        else
            return true;
    }
    return (a[i]<b[i]);
}

string largestNumber(const vector<int> &A) {
    string ans;
    vector<string> str(A.size(), "");
    for (int i=0; i<A.size(); i++)
    {
        int t=A[i];
        while (t!=0)
        {
            str[i]=(char)(t%10+48)+str[i];
            t/=10;
        }
    }
    sort(str.begin(),str.end(),comp);
    for (int i=str.size()-1; i>=0; i--)
    {
		cout << str[i] << " ";
        ans+=str[i];
	}
    if (ans=="")
        ans="0";
    return ans;
}

int main()
{
	string a="99986970963951935898868588558147967757707497171771571070770669694656456416406286176146115885775755365084964844794624514140939539339138237236035434328827927239228214913611";
	string b="99986970963951935898868588558147967757707497177171571070770669694656456416406286176146115885775755365084964844794624514140939539339138237236035434328827927239228214913611";
	string inp="855, 796, 614, 354, 628, 886, 99, 27, 770, 694, 611, 577, 575, 149, 462, 617, 858, 382, 640, 409, 536, 749, 372, 775, 11, 508, 479, 65, 393, 715, 951, 71, 963, 641, 2, 707, 395, 451, 645, 588, 69, 706, 89, 484, 710, 239, 279, 343, 970, 986, 288, 360, 496, 391, 136, 228, 41, 935, 814, 717";
	int x=1;
	for (int i=0; i<inp.length(); i++)
		if (inp[i]==',')
			x++;
	int arr[]={855, 796, 614, 354, 628, 886, 99, 27, 770, 694, 611, 577, 575, 149, 462, 617, 858, 382, 640, 409, 536, 749, 372, 775, 11, 508, 479, 65, 393, 715, 951, 71, 963, 641, 2, 707, 395, 451, 645, 588, 69, 706, 89, 484, 710, 239, 279, 343, 970, 986, 288, 360, 496, 391, 136, 228, 41, 935, 814, 717};
	vector<int> t(arr, arr+x);
	largestNumber(t);
	cout << endl;
	for (int i=0; i<a.length(); i++)
		if (a[i]!=b[i])
		{
			cout << "failed " << i << "   " << a[i] << " " << b[i] << endl;
		}
		
	return 0;
}

/*71 717   71717  71771
 * 71 7177		717177	717771
 *78 787   78787  78778
 * */
