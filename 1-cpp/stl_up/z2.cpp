#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int main()
{
	ifstream fin("fishes");
	vector < vector <string> > fman;
	fman.resize(4);
	string temp;
	int i=0;
	while (!fin.eof())
	{
		fin >> temp;
		if (temp=="1" || temp=="2" || temp=="3")
			i=temp[0]-48;
		else
			fman[i].push_back(temp);
	}
	fman[3].pop_back();
	for (int i=1; i<=3; i++)
	{
		cout << "Fisherman " << i << ":  ";
		for (unsigned int j=0; j<fman[i].size(); j++)
			cout << fman[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	//UNIONS:
	for (int i=1; i<=3; i++) 
		sort(fman[i].begin(),fman[i].end());
	vector <string> temp_un(fman[1].size()+fman[2].size());
	vector<string>::iterator it;
	it=set_union(fman[1].begin(),fman[1].end(),fman[2].begin(),fman[2].end(),temp_un.begin());
	temp_un.resize(it-temp_un.begin());
	vector <string> un(temp_un.size()+fman[3].size());
	it=set_union(temp_un.begin(),temp_un.end(),fman[3].begin(),fman[3].end(),un.begin());
	un.resize(it-un.begin());
	cout << "UNIQUE FISHES WHICH WERE CAUGHT: " << endl;
	for (vector<string>::iterator i=un.begin(); i!=un.end(); i++)
		cout << "  " << *i << endl;
	cout << endl;
	
	//DIFFERENCE:
	vector <string> dif (fman[0].size());
	sort(fman[0].begin(),fman[0].end());
	it=set_difference(fman[0].begin(),fman[0].end(),un.begin(),un.end(),dif.begin());
	dif.resize(it-dif.begin());
	cout << "FISHES WERE NOT CAUGHT BY ANYBODY: " << endl;
	for (vector<string>::iterator i=dif.begin(); i!=dif.end(); i++)
		cout << "  " << *i << endl;
	return 0;
}
