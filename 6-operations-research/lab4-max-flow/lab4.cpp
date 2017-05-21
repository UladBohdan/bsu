#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 999999999;
const int NO = -987584938; // some random number.

// s - number of sources.
// t - number of destinations.
// first s indices are for sources: [1 .. s]
// last n indices are for destinations: [n-t .. n]
// the rest are inner nodes.
int n, m, s, t;

// I'm creating a fake nodes for source (one for all) and destination.
// They have 0 and n+1 indices.

// You must pass a file with graph. The format is:
// <number of nodes> <number of sources> <number of destinations>
// <number of edges>
// <from> <to> <capacity> ... for every edge.

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "You must provide a file with data." << endl;
        return 0;
    }
    ifstream fin(argv[1]);

    fin >> n >> s >> t >> m;

    // graph is matrix of capacities. NO if there's no edge.
    vector<vector<int>> graph(n+2, vector<int>(n+2, NO));

    for (int i = 0; i < m; i++) {
        int a, b, c;
        fin >> a >> b >> c;
        graph[a][b] = c;
        graph[b][a] = 0; // reversed edge.
    }

    // creating fake source and fake destination.
    for (int i = 1; i <= s; i++) {
        int sum_cap = 0;
        for (int j = s+1; j <= n; j++) {
            if (graph[i][j] != NO) {
                sum_cap += graph[i][j];
            }
        }
        graph[0][i] = sum_cap;
        graph[i][0] = 0;
    }
    for (int i = n-t+1; i <= n; i++) {
        int sum_cap = 0;
        for (int j = 1; j < n-t+1; j++) {
            if (graph[j][i] != NO) {
                sum_cap += graph[j][i];
            }
        }
        graph[i][n+1] = sum_cap;
        graph[n+1][i] = 0;
    }

    vector<bool> cut(n+2, false);  // true vs. false.

    // searching for (s,t) paths while they exist.
    // using bfs for search.
    while (true) {
        queue<int> q; // for bfs. nodes indices.
        vector<bool> used(n+2, false);
        vector<int> from(n+2); // how we've reached the node.

        q.push(0);
        used[0] = true;
        from[0] = -1;

        bool path_found = false;

        while (!q.empty()) {
            int cur_node = q.front();
            q.pop();

            if (cur_node == n+1) {
                // we've found a path from source to destination.
                int min_cap = INF;
                while (true) {
                    int par = from[cur_node];
                    if (par == -1) {
                        break;
                    }
                    min_cap = min(min_cap, graph[par][cur_node]);
                    cur_node = par;
                }
                cur_node = n+1;
                while (true) {
                    int par = from[cur_node];
                    if (par == -1) {
                        break;
                    }
                    graph[par][cur_node] -= min_cap;
                    graph[cur_node][par] += min_cap;
                    cur_node = par;
                }
                path_found = true;
                break;
            }

            // checking the neighbours.
            for (int i = 0; i < n+2; i++) {
                if (used[i] == false && graph[cur_node][i] != NO && graph[cur_node][i] > 0) {
                    q.push(i);
                    from[i] = cur_node;
                    used[i] = true;
                }
            }
        }

        if (path_found == false) {
            // no more (s,t) paths.
            // stopping the algorithm.
            for (int i = 0; i < n+2; i++) {
                cut[i] = used[i];
            }
            for (int i = 1; i <= s; i++) {
                cut[i] = true;
            }
            break;
        }
    }

    int max_flow = 0;
    for (int i = 0; i < n+2; i++) {
        if (graph[i][0] != NO) {
            max_flow += graph[i][0];
        }
    }
    cout << "MAX FLOW: " << max_flow << endl;
    cout << "The CUT: ";
    for (int i = 1; i <= n; i++) {
        if (cut[i] == true) {
            cout << i << " ";
        }
    }
    cout << " ||  ";
    for (int i = 1; i <= n; i++) {
        if (cut[i] == false) {
            cout << i << " ";
        }
    }
    cout << endl;

    return 0;
}
