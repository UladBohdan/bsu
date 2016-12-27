#include <fstream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

const int INF = 999999999;

struct Edge {
    // | capacity, cost, max_flow |
    int cap;
    int cost;
    int flow;

    Edge() : cap(0), cost(0), flow(0) { }

    Edge(int _cap, int _cost, int _flow) : cap(_cap), cost(_cost), flow(_flow) { }
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

int main() {

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    fin >> n >> m >> x >> y;
    x--;
    y--;

    vector<vector<Edge> > g(n, vector<Edge>(n)), g_built(n, vector<Edge>(n));
    for (int i=0; i<m; i++) {
        int a, b, c, d;
        fin >> a >> b >> c >> d;
        g[a-1][b-1] = Edge(c, d, 0);
        g[b-1][a-1] = Edge(0, -d, 0);
    }
    while (!fin.eof()) {
        int a, b;
        fin >> a >> b >> ws;
        g_built[a-1][b-1] = g[a-1][b-1];
        g_built[b-1][a-1] = g[b-1][a-1];
    }

    pair<int, int> best = max_flow_min_cost(g);
    pair<int, int> other = max_flow_min_cost(g_built);

    if (best == other) {
        fout << "Yes" << endl << best.first << endl << best.second << endl;
    } else {
        fout << "No" << endl << best.first << endl << best.second << endl << other.first << endl << other.second << endl;
    }
    return 0;
}
