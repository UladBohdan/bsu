#include <iomanip>
#include <iostream>
#include <queue>
#include <random>

using namespace std;

// Parameters.
int A = 120, B = 10;  // Distribution parameters. Originally A1, A2, B1, B2;
int b = 16, eps = 4;  // Travel time distribution parameters.
int t1 = 15, t2 = 10;  // Generation time intervals.
int m1 = 10, m2 = 10;  // Packet sizes.
int k = 1 * 60 * 60;  // Time to run in seconds.

class Event {
public:
  Event(int time, string type) : time(time), type(type) { }

  int time;
  string type;
};

auto comp = [](const Event& a, const Event& b) { return a.time > b.time; };

void print_log(int cur_time, string msg) {
  cout << setw(5) << cur_time << "  " << msg << endl;
}

int main() {
  priority_queue<Event, vector<Event>, decltype(comp)> q(comp);

  default_random_engine generator;
  uniform_int_distribution<int> transport_distribution(b-eps, b+eps);
  uniform_int_distribution<int> process_distribution(A-B, A+B);

  q.push(Event(0, "START"));

  int queue_count_1 = 0, queue_count_2 = 0, wait_two_packets = 0;

  while (!q.empty()) {
    Event temp = q.top();
    q.pop();
    int cur_time = temp.time;
    if (cur_time >= k) {
      print_log(cur_time, "time limit exceeded.");
      return 0;
    }
    if (temp.type == "START") {
      print_log(cur_time, "started.");
      q.push(Event(cur_time+t1, "GENERATED_1"));
      q.push(Event(cur_time+t2, "GENERATED_2"));
    } else if (temp.type == "GENERATED_1") {
      print_log(cur_time, "object type 1 was generated.");
      q.push(Event(cur_time+t1, "GENERATED_1"));
      queue_count_1++;
      if (queue_count_1 == m1) {
        char buf[50];
        sprintf(buf, "%d objects of type 1 were packed.", m1);
        print_log(cur_time, string(buf));
        queue_count_1 = 0;
        wait_two_packets++;
        if (wait_two_packets == 2) {
          print_log(cur_time, "two packets sent for processing.");
          wait_two_packets = 0;
          int time_transport = transport_distribution(generator);
          int time_process = process_distribution(generator);
          q.push(Event(cur_time+time_transport+time_process, "RELEASE"));
        }
      }
    } else if (temp.type == "GENERATED_2") {
      print_log(cur_time, "object type 2 was generated.");
      q.push(Event(cur_time+t2, "GENERATED_2"));
      queue_count_2++;
      if (queue_count_2 == m2) {
        char buf[50];
        sprintf(buf, "%d objects of type 2 were packed.", m2);
        print_log(cur_time, string(buf));
        queue_count_2 = 0;
        wait_two_packets++;
        if (wait_two_packets == 2) {
          print_log(cur_time, "two packets sent for processing.");
          wait_two_packets = 0;
          int time_transport = transport_distribution(generator);
          int time_process = process_distribution(generator);
          q.push(Event(cur_time+time_transport+time_process, "RELEASE"));
        }
      }
    } else if (temp.type == "RELEASE") {
      print_log(cur_time, "two packets were released.");
    }
  }

  return 0;
}
