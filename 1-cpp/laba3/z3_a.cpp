#include <iostream>

using namespace std;

int main()
{
	string a;
	int ans_pos=0, ans_len=1, temp_pos, temp_len;
	cout << "Uviadzice naturalny lik:" << endl;
	cin >> a;
	for (unsigned int i=0; i<a.length()-1; i++)
	{
		if (a[i+1]==a[i]+1)
		{
			temp_pos=i;
			temp_len=2;
			while ((unsigned int)temp_pos+temp_len<a.length() && a[temp_pos+temp_len]==a[temp_pos]+temp_len)
				temp_len++;
			if (temp_len>ans_len)
			{
				ans_len=temp_len;
				ans_pos=temp_pos;
			}
		}
	}
	for (int i=0; i<ans_len; i++)
		cout << a[ans_pos+i];
	return 0;
}
