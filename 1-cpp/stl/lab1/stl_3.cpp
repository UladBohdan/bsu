#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <fstream>
#include <algorithm>

using namespace std;

bool checking (int t)
{
	return t>15;
}

int main()
{
	ifstream fin("input_numbers");
	vector <int> a;
	deque <int> b;
	list <int> c;
	int num;
	while (!fin.eof())
	{
		fin >> num;
		a.push_back(num);
		b.push_back(num);
		c.push_back(num);
	}
	cout << "         vector    deque    list" << endl;
	cout << "sizes:     " << a.size() << "       " << b.size() << "      " << c.size() << endl;
	int temp1=0, temp2=0, temp3=0;
	vector<int>::iterator i=a.begin();
	deque<int>::iterator j=b.begin();
	list<int>::iterator k=c.begin();
	for (; i!=a.end() && j!=b.end() && k!=c.end(); i++, j++, k++)
	{
		temp1+=(*i);
		temp2+=(*j);
		temp3+=(*k);
	}
	cout << "sums:     " << temp1 << "       " << temp2 << "     " << temp3 << endl;
	cout << "average:  " << temp1*1./a.size() << "    " << temp2*1./b.size() << "    " << temp3*1./c.size() << endl;
	cout << endl;
	cout << "number of '3'  " << count(a.begin(),a.end(),3) << endl;
	cout << "number of >15  " << count_if(a.begin(),a.end(),checking);
	return 0;
}
