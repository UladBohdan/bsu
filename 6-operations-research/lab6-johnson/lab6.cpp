#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <utility>

using namespace std;

const int N = 10;
const int MAX_TIME = 20;

int main() {
    srand(time(NULL));

    vector<pair<int, int>> jobs(N);

    // Randomly generating jobs.
    for (int i = 0; i < N; i++) {
        jobs[i] = make_pair(rand() % MAX_TIME + 1, rand() % MAX_TIME + 1);
    }

    cout << "Randomly generated jobs: " << endl;
    for (int i = 0; i < N; i++) {
        cout << " (" << jobs[i].first << ", " << jobs[i].second << ") ";
    }
    cout << endl;

    // The algorithm.
    sort(jobs.begin(), jobs.end(),
        [](const pair<int,int>& a, const pair<int,int>& b) -> bool{
            return (min(a.first, a.second) < min(b.first, b.second));
        });
    vector<pair<int, int>> ans(N);
    int pos1 = 0, pos2 = N-1;
    for (int i = 0; i < N; i++) {
        if (jobs[i].first < jobs[i].second) {
            ans[pos1] = jobs[i];
            pos1++;
        } else {
            ans[pos2] = jobs[i];
            pos2--;
        }
    }

    // Generating output.
    cout << "The order of jobs to minimize time: " << endl;
    for (int i = 0; i < N; i++) {
        cout << " (" << ans[i].first << ", " << ans[i].second << ") ";
    }
    cout << endl;

    vector<int> m1_start_time(N);   // m for Machine.
    vector<int> m1_end_time(N);
    vector<int> m2_start_time(N);
    vector<int> m2_end_time(N);

    int m2_downtime = 0;

    m1_start_time[0] = 0;
    m1_end_time[0] = ans[0].first;
    m2_start_time[0] = ans[0].first;
    m2_end_time[0] = ans[0].first + ans[0].second;
    m2_downtime += m2_start_time[0];

    for (int i = 1; i < N; i++) {
        pair<int, int> job = ans[i];

        m1_start_time[i] = m1_end_time[i-1];
        m1_end_time[i] = m1_start_time[i] + job.first;
        m2_start_time[i] = max(m1_end_time[i], m2_end_time[i-1]);
        m2_end_time[i] = m2_start_time[i] + job.second;
        m2_downtime += (m2_start_time[i] - m2_end_time[i-1]);
    }

    cout << "            Machine1  Machine2" << endl;
    for (int i = 0; i < N; i++) {
        cout << "JOB " << i << "  timing:  " << m1_start_time[i] << "-" << m1_end_time[i] << "  "
             << m2_start_time[i] << "-" << m2_end_time[i] << endl;
    }

    cout << "Machine 2 downtime (minimized): " << m2_downtime << endl;

    return 0;
}
