#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector <char> let (26);
	for (int i=0; i<26; i++)
		let[i]=(char)('a'+i);
	for (unsigned int i=0; i<let.size(); i++)
		cout << let[i] << " ";
	cout << endl;
	for (vector<char>::reverse_iterator i=let.rbegin(); i!=let.rend(); i++)
		cout << *i << " ";
	return 0;
}
