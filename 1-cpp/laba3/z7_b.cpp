#include <iostream>
#include <vector>

using namespace std;

string a;
string ans;

void try_to_find(int pos, char lic, string temp)
{
	for (unsigned int i=pos+1; i<a.length(); i++)
		if (a[i]>lic)
		{
			if (temp.length()>=ans.length()) ans=temp+a[i];
			try_to_find(i,a[i],temp+a[i]);
		}
}

int main()
{
	cout << "Uviadzicie naturalny lik:" << endl;
	cin >> a;
	for (unsigned int i=0; i<a.length()-1; i++)
	{
		string temp;
		temp+=a[i];
		try_to_find(i,a[i],temp);
	}
	cout << ans;
	return 0;
}
