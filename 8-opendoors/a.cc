#include <iostream>

#include <vector>
#include <functional>
#include <queue>
#include <unordered_map>
#include <utility>

using namespace std;

struct Way{
  Way(int t, int e, int u) : togo(t), edgeID(e), usages(u) {}
  int togo;
  int edgeID;
  int usages;
};

int main() {
  int n, m, k;
  cin >> n >> m >> k;

  // For each room/node:
  // Pair stands for (edge ID to go, number of edge usages).
  auto cmp = [](Way left, Way right) {
    return (
      (left.usages > right.usages ||
      (left.usages == right.usages && left.togo > right.togo) ||
      (left.usages == right.usages && left.togo == right.togo && left.edgeID > right.edgeID))
    );
  };
  vector<priority_queue<Way, vector<Way>, decltype(cmp)> >
    ways(n, priority_queue<Way, vector<Way>, decltype(cmp)>(cmp));

  // For each node: this is a hashmap of edgeID to number of updates pending.
  vector<unordered_map<int,int>> updates_pending(n, unordered_map<int,int>());

  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    // For each edge:
    ways[a].push(Way(b, i, 0));
    if (a != b) {
      ways[b].push(Way(a, i, 0));
    }
  }

  int cur = 0;
  while (k > 0) {
    // cout << "CUR is " << cur+1 << endl;
    if (ways[cur].empty()) {
      break;
    }
    int togo, edgeID, freq;
    while (true) {
      auto w = ways[cur].top();
      // cout << "TOP is  node: " << w.togo+1 << "  old freq: " << w.usages << endl;
      togo = w.togo;
      freq = w.usages;
      edgeID = w.edgeID;
      int upd = updates_pending[cur][edgeID];
      if (upd > 0) {
        // cout << "have some updates:  upd: " << upd << " freq: " << freq << endl;
        ways[cur].pop();
        ways[cur].push(Way(togo, edgeID, upd+freq));
        updates_pending[cur][edgeID] = 0;
        // cout << "TOP is  node: " << ways[cur].top().togo+1 << "  new freq: " << ways[cur].top().usages << endl;
      } else {
        break;
      }
    }
    // cur -> togo.
    ways[cur].pop();
    ways[cur].push(Way(togo, edgeID, freq+1));
    if (cur != togo) {
      updates_pending[togo][edgeID]++;
    }
    cur = togo;
    k--;
  }

  cout << cur + 1 << endl;
  return 0;
}
