#include <iostream>
#include <vector>

using namespace std;

string a;
vector <int> temp_ans;

void try_to_find(int pos, int lic)
{
	for (unsigned int i=pos+1; i<a.length(); i++)
		if (a[i]-48==lic)
		{
			temp_ans.push_back(a[i]-48);
			try_to_find(i,lic+1);
			i=a.length();
		}
}

int main()
{
	cout << "Uviadzicie naturalny lik:" << endl;
	cin >> a;
	vector <int> ans;
	for (unsigned int i=0; i<a.length()-1; i++)
	{
		temp_ans.clear();
		temp_ans.push_back(a[i]-48);
		try_to_find(i,a[i]+1-48);
		if (temp_ans.size()>ans.size())
		{
			ans.clear();
			for (unsigned int j=0; j<temp_ans.size(); j++)
				ans.push_back(temp_ans[j]);
		}
	}
	for (unsigned int i=0; i<ans.size(); i++)
		cout << ans[i];
	return 0;
}
