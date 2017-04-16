#include <iostream>

using namespace std;

struct cell 
{
	int data;
	cell* down;
	cell* right;
};

class matrix_list
{
	private:
		cell* start;
		int n, m;
	public:
		matrix_list(int a, int b): start(NULL), n(a), m(b)
		{ }
		void push_matrix();
		void show();
};

void matrix_list::push_matrix()
{
	int k;
	for (int i=0; i<n; i++)
		for (int j=0; j<m; j++)
		{
			cin >> k;
			if (i==0 && j==0)
			{
				start->data=k;
			}
		}
} 

int main()
{
	int n, m;
	cout << "Enter the size of matrix (N rows and M cols): ";
	cin >> n >> m;
	matrix_list a(n,m);
	cout << "Enter your matrix: " << endl;
	a.push_matrix();
	return 0;
}
