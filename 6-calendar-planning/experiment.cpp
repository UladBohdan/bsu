#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

const int INF = 999999999;

struct Edge {
    // | capacity, cost |
    int cap;
    int cost;

    Edge() : cap(0), cost(0) { }

    Edge(int _cap, int _cost) : cap(_cap), cost(_cost) { }
};

int n, m, x, y;

pair<int, int> max_flow_min_cost(vector<vector<Edge> >& g) {

    vector<int> l(n, INF), par(n);
    l[x] = 0;

    //min cost path (ford-bellman)
    for (int it = 0; it < n-1; it++) {
        bool changed = false;
        for (int a = 0; a < n; a++) {
            for (int b = 0; b < n; b++) {
                if (g[a][b].cap) {
                    int alt = l[a] + g[a][b].cost;
                    if (l[b] > alt ) {
                        l[b] = alt;
                        par[b] = a;
                        changed = true;
                    }
                }
            }
        }
        if (!changed) {
            break;
        }
    }

    if (l[y] == INF) {
        // FOUND. OUTPUT
        int capacity = 0, cost = 0;
        for (int i = 0; i < n; i++) {
            capacity += g[i][x].cap;
        }
        for (int a = 0; a < n; a++) {
            for (int b = 0; b < n; b++) {
                if (g[a][b].cost < 0) {
                    cost -= g[a][b].cost * g[a][b].cap;
                }
            }
        }
        return make_pair(capacity, cost);

    } else {

        int min_edge = INF;
        int from = y;
        while (from != x) {
            int temp = from;
            from = par[from];
            min_edge = min(min_edge, g[from][temp].cap);
        }
        from = y;
        while (from != x) {
            int temp = from;
            from = par[from];
            g[from][temp].cap -= min_edge;
            g[temp][from].cap += min_edge;
        }

        return max_flow_min_cost(g);
    }

}

// the file is:
// number of employees, number of jobs
// for every employee - size of Q_e, and pairs (job, cost).
// for every job - the demand
//
// everything is 1-based.

int main() {
    ifstream fin("data/experiment.txt");

    int n_employees, n_jobs;
    fin >> n_employees >> n_jobs;

    // 0 is S, last is T.
    n = n_employees + n_jobs + 2;
    m = 0;
    x = 0;
    y = n - 1;
    vector<vector<Edge> > g(n, vector<Edge>(n));

    for (int i = 1; i <= n_employees; i++) {
      int q_e_size;
      fin >> q_e_size;
      for (int j = 0; j < q_e_size; j++)  {
        int job, cost;
        fin >> job >> cost;
        g[i][n_employees + job] = Edge(1, cost);

        g[n_employees + job][i] = Edge(0, -cost);
      }
    }

    // reading demands.
    for (int i = 1; i <= n_jobs; i++) {
      int demand;
      fin >> demand;
      g[n_employees + i][y] = Edge(demand, 0);
      g[y][n_employees + i] = Edge(0, 0);
    }

    // adding (s, e) edges.
    for (int i = 1; i <= n_employees; i++) {
      g[x][i] = Edge(1, 0);
      g[i][x] = Edge(0, 0);
    }

    pair<int, int> ans = max_flow_min_cost(g);

    cout << "Schedule: " << endl;
    for (int a = 0; a < n; a++) {
        for (int b = 0; b < n; b++) {
            if (g[a][b].cost < 0 && g[a][b].cap > 0) {
                cout << "Job " << a - n_employees << "  by " << b << endl;
            }
        }
    }

    cout << "Max flow:  " << ans.first << endl;
    cout << "Min cost:  " << ans.second << endl;

    return 0;
}
