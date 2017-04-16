#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct ret
{
	int sum, num;
};

class student
{
	protected:
		string name;
		int group;
		double aver;
	public:
		student()
		{}
		student(string new_name, int new_group) : name(new_name), group(new_group), aver(0)
		{}
		virtual void show()
		{
			cout << endl;
			cout << "Student " << name << " (" << group << " group)" << endl;
			cout << "Has not passed exams yet" << endl;
		}
		virtual ret marks()
		{
			ret k={0,0};
			return k;
		}
		~student()
		{}
};

class stud_1 : public student
{
	protected:
		int a[4];
		double av1;
	public:
		static double group_sum1;
		stud_1()
		{}
		stud_1(string new_name, int new_group, int a0, int a1, int a2, int a3) : student(new_name,new_group)
		{
			a[0]=a0;
			a[1]=a1;
			a[2]=a2;
			a[3]=a3;
			av1=(a0+a1+a2+a3)/4.;
			group_sum1+=av1;
		} 
		virtual void show()
		{
			cout << endl;
			cout << "Student " << name << " (" << group << " group)" << endl;
			cout << "Marks after first session: " << a[0] << " " << a[1] << " " << a[2] << " " << a[3] << endl;
			cout << "Average mark: " << av1 << endl;
		}
		virtual ret marks()
		{
			ret k={a[0]+a[1]+a[2]+a[3],1};
			return k;
		}
		~stud_1()
		{}
};

class stud_2 : public stud_1
{
	protected:
		int b[4];
		double av2;
	public:
		static double group_sum2;
		stud_2()
		{}
		stud_2(string new_name, int new_group, int a0, int a1, int a2, int a3, int b0, int b1, int b2, int b3) : 
			stud_1(new_name,new_group,a0,a1,a2,a3)
		{
			b[0]=b0;
			b[1]=b1;
			b[2]=b2;
			b[3]=b3;
			av2=(b0+b1+b2+b3)/4.;
			group_sum2+=av2;
		} 
		virtual void show()
		{
			cout << endl;
			cout << "Student " << name << " (" << group << " group)" << endl;
			cout << "Marks after first session: " << a[0] << " " << a[1] << " " << a[2] << " " << a[3] << endl;
			cout << "Average mark: " << av1 << endl;
			cout << "Marks after second session: " << b[0] << " " << b[1] << " " << b[2] << " " << b[3] << endl;
			cout << "Average mark: " << av2 << endl;
		}
		virtual ret marks()
		{
			ret k={a[0]+a[1]+a[2]+a[3]+b[0]+b[1]+b[2]+b[3],2};
			return k;
		}
		~stud_2()
		{}
	
};

double stud_1::group_sum1=0;
double stud_2::group_sum2=0;

int main()
{
	ifstream in("data");
	int n1, n2, n3;
//	cout << "Enter a group of students (at least one in each category)" << endl;
//	cout << "How many students has not passed exams yet? ";
	in >> n1;
	student *st1 = new student[n1];
	for (int i=0; i<n1; i++)
	{
		string temp;
		int gr;
		in >> temp >> gr;
		st1[i]=student(temp,gr);
	}
//	cout << "How many students has already passed first session? ";
	in >> n2;
	stud_1 *st2 = new stud_1[n2];
	for (int i=0; i<n2; i++)
	{
		string temp;
		int gr, a[4];
		in >> temp >> gr >> a[0] >> a[1] >> a[2] >> a[3];
		st2[i]=stud_1(temp,gr,a[0],a[1],a[2],a[3]);
	}
	//cout << "How many students has already passed second session? ";
	in >> n3;
	stud_2 *st3 = new stud_2[n3];
	for (int i=0; i<n3; i++)
	{
		string temp;
		int gr, a[8];
		in >> temp >> gr >> a[0] >> a[1] >> a[2] >> a[3] >> a[4] >> a[5] >> a[6] >> a[7];
		st3[i]=stud_2(temp,gr,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7]);
	}
	cout << endl << "READING FROM FILE..." << endl << endl;
	cout << "Average after first session: " << st2[0].group_sum1/(n2*1.+n3*1.) << endl;
	cout << "Average after two sessions: " << st3[0].group_sum2/(n3*1.) << endl;
	//student *p = new student[n1+n2+n3];
	student *p[20];
	int pos=0;
	for (int i=0; i<n1; i++, pos++)
		p[pos]=&st1[i];
	for (int i=0; i<n2; i++, pos++)
		p[pos]=&st2[i];
	for (int i=0; i<n3; i++, pos++)
		p[pos]=&st3[i];
	for (int i=0; i<n1+n2+n3; i++)
		p[i]->show();
	int sum=0, num=0;
	for (int i=0; i<n1+n2+n3; i++)
	{
		ret k=p[i]->marks();
		sum+=k.sum;
		num+=k.num;
	}
	cout << "\nGeneral average mark for session: " << sum*1./num;
	return 0;
}
