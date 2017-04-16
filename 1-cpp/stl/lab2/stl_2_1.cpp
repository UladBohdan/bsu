#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

string surn, bestname;
int num=0, mx_sum=0;

struct stud
{
	string name;
	int group, mark[4];
};

void searchmx(stud a)
{
	if (a.mark[0]+a.mark[1]+a.mark[2]+a.mark[3]>mx_sum)
	{
		mx_sum=a.mark[0]+a.mark[1]+a.mark[2]+a.mark[3];
		bestname=a.name;
	}
}

bool how (stud a, stud b) 
{
	if (a.name<b.name)
		return true;
	else if (a.name==b.name && a.group<b.group)
		return true;
	return false;
}

bool testing (stud a)
{
	if (a.name==surn)
	{
		num++;
		return true;
	}
	return false;
}

int main()
{
	ifstream fin("students");
	vector <stud> s;
	do
	{
		stud temp;
		fin >> temp.name >> temp.group >> temp.mark[0] >> temp.mark[1] >> temp.mark[2] >> temp.mark[3];
		s.push_back(temp);
	}
	while (!fin.eof());
	s.pop_back();
	sort(s.begin(), s.end(), how);
	for (unsigned int i=0; i<s.size(); i++)
	{
		cout << s[i].name << " " << s[i].group << "      " << s[i].mark[0] << " " << s[i].mark[1] << " " 
														   << s[i].mark[2] << " " << s[i].mark[3] << " " << endl;
	}
	cout << endl << "Enter a surname to erase a student: ";
	cin >> surn;
	remove_if(s.begin(),s.end(),testing);
	s.resize(s.size()-num);
	cout << "NEW LIST OF STUDENTS: " << endl;
	for (unsigned int i=0; i<s.size(); i++)
	{
		cout << s[i].name << " " << s[i].group << "      " << s[i].mark[0] << " " << s[i].mark[1] << " " 
														   << s[i].mark[2] << " " << s[i].mark[3] << " " << endl;
	}
	
	map < string, stud, less<string> > m;
	for (unsigned int i=0; i<s.size(); i++)
	{
		m[s[0].name]=s[0];
	}
	
	vector <stud> not_passed;
	for (vector<stud>::iterator i=s.begin(); i!=s.end(); i++)
	{
		if (i->mark[0]<4 || i->mark[1]<4 || i->mark[2]<4 || i->mark[3]<4)
			not_passed.push_back(*i);
	}
	cout << endl;
	if (not_passed.empty())
		cout << "Everybody passed!";
	else
	{
		cout << not_passed.size() << " persons didn`t pass:" << endl;
		for (unsigned int i=0; i<not_passed.size(); i++)
			cout << "  " << not_passed[i].name << endl;
	}
	
	for_each(s.begin(),s.end(),searchmx);
	
	cout << endl << bestname << " has best marks.";
	return 0;
}
