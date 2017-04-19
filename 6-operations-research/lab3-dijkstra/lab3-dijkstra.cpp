#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <list>
#include <utility>

using namespace std;

const int INF = 999999999;

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "no file provided" << endl;
        return 0;
    }
    string filename(argv[1]);

    ifstream fin(filename);

    int n, m;
    fin >> n >> m;
    vector<list<pair<int, int>>> graph(n, list<pair<int,int>>());
    for (int i = 0; i < m; i++) {
        int a, b, cost;
        fin >> a >> b >> cost;
        graph[a-1].push_back(make_pair(b-1, cost));
    }

    // Pairs (min cost, Node number).
    priority_queue<pair<int,int>, vector<pair<int, int>>, greater<pair<int,int>> > q;
    // Starting from x2.
    q.push(make_pair(0, 1));

    vector<int> final_costs(n, INF);
    final_costs[1] = 0;

    vector<bool> fixed(n, false);

    int num_estimated = 0;
    while (num_estimated != n) {
        pair<int, int> mn_node;
        while (!q.empty()) {
            mn_node = q.top();
            q.pop();
            if (!fixed[mn_node.second]) {
                break;
            }
        }

        int cur_node = mn_node.second;

        fixed[cur_node] = true;
        num_estimated++;

        for (list<pair<int,int>>::iterator it = graph[cur_node].begin(); it != graph[cur_node].end(); it++) {
            if (fixed[it->first]) {
                // Already estimated.
                continue;
            }
            if (final_costs[cur_node] + it->second < final_costs[it->first]) {
                final_costs[it->first] = final_costs[cur_node] + it->second;
                q.push(make_pair(final_costs[it->first], it->first));
            }
        }
    }

    cout << "  min cost paths from x2:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "    " << i+1 << "\t" << final_costs[i] << endl;
    }

    return 0;
}
