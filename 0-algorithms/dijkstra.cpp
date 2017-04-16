#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <stack>

using namespace std;

const int INF=999999999;
const int s=0;      // place to start

int main()
{
    int n, m, t1, t2, t3;
    ifstream fin("data/dijkstra.txt");
    fin >> n >> m;
    vector < stack <pair <int, int> > > g(m);
    vector <int> d(n, INF), from(n,0);
    vector <bool> used(n, false);
    d[s]=0;
    for (int i=0; i<m; i++)
    {
        fin >> t1 >> t2 >> t3;
        g[t1].push(make_pair(t2,t3));
        g[t2].push(make_pair(t1,t3));
    }
    for (int i=0; i<n; i++)
    {
        if (!used[i])
        {
            used[i]=true;
            while (!g[i].empty())
            {
                t1=g[i].top().first;
                t2=g[i].top().second;
                g[i].pop();
                if (d[t1]>t2+d[i])
                {
                    d[t1]=t2+d[i];
                    from[t1]=i;
                }
            }

        }
    }
    for (int i=0; i<n; i++)
    {
        if (d[i]==INF)
        {
            cout << i << ", Impossible to destinate from " << s << endl;
            continue;
        }
        cout << i << ", distance: " << d[i] << ". How to get: ";
        stack <int> temp;
        temp.push(i);
        while (temp.top()!=s)
            temp.push(from[temp.top()]);
        while (!temp.empty())
        {
            cout << temp.top() << " ";
            temp.pop();
        }
        cout << endl;
    }
    return 0;
}

