#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

vector<int> x, y;

double d(int i, int j) {
    return (abs(i-j) == 1 ? 0 : sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j])) );
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n;
    fin >> n;
    x.resize(n);
    y.resize(n);
    for (int i=0; i<n; i++)
        fin >> x[i] >> y[i];

    vector<vector<double> > t(n, vector<double>(n+1));
    for (int i=0; i<n; i++) {
        t[i][0] = t[i][1] = t[i][2] = t[i][3] = 0;
    }
    for (int s=4; s<=n; s++) {
        for (int i=0; i<n; i++) {
            double mn = 999999999;
            for (int k=1; k<=s-2; k++) {
                mn = min(mn, t[i][(k+1)%n] + t[(i+k)%n][(s-k)%n] + d(i,(i+k)%n) + d((i+k)%n,(i+s-1)%n ));
            }
            t[i][s] = mn;
            //cout << "SET i=" << i << " s=" << s << "   " << mn << endl;
        }

        /*cout << "TABLE" << endl;
        for (int i=0; i<n; i++) {
            for (int j=0; j<=n; j++) {
                cout << t[i][j] << " ";
            }
            cout << endl;
        }*/

    }
    fout << t[0][n] << endl;
    return 0;
}