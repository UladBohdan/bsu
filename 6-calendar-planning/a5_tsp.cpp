#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

const double INF = 999999999.;
const double MAGIC = -192847327.;

using namespace std;

// Input is a list of edges: (node1, node2, cost). 1-based.

int main() {
  ifstream fin("data/a5_tsp.txt");
  int n, m;
  fin >> n >> m;
  vector<vector<double> > g (n, vector<double>(n, MAGIC));
  for (int i = 0; i < m; i++) {
    int a, b;
    double c;
    fin >> a >> b >> c;
    // Assuming the graph is directed.
    g[a-1][b-1] = c;
  }

  vector<int> order(n);
  for (int i = 0; i < n; i++) {
    order[i] = i;
  }

  int num_routes = 1;
  for (int i = 2; i <= n; i++) {
    num_routes *= i;
  }

  double min_found = INF;
  vector<int> min_route_order;

  for (int t = 0; t < num_routes; t++) {
    double new_route = 0;
    bool a_route = true;
    for (int i = 1; i < n; i++) {
      double edge_value = g[order[i-1]][order[i]];
      if (edge_value == MAGIC) {
        a_route = false;
      }
      new_route += edge_value;
    }
    double edge_value = g[order[n-1]][order[0]];
    if (edge_value == MAGIC) {
      a_route = false;
    }
    new_route += edge_value;
    if (a_route && new_route < min_found) {
      min_found = new_route;
      min_route_order = vector<int>(order);
    }

    next_permutation(order.begin(), order.end());
  }

  cout << "TSP route found!" << endl;
  cout << "Min cost is:  " << min_found << endl;
  cout << "The route is:  ";
  for (int i = 0; i < n; i++) {
    cout << min_route_order[i] + 1 << " ";
  }
  cout << min_route_order[0] + 1 << endl;

  return 0;
}
