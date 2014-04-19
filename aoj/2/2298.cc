#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

typedef enum { CARROT, DOWN, GOAL } Event;
struct event {
  int dist;
  Event ev;
  event(int d, Event e) : dist(d), ev(e) {}
  bool operator<(const event& that) const { return dist > that.dist; }
};

int main()
{
  int N, K, T, U, V, L;
  cin >> N >> K >> T >> U >> V >> L;
  priority_queue<event> q;
  q.push(event(L, GOAL));
  for (int i = 0; i < N; i++) {
    int d;
    cin >> d;
    q.push(event(d, CARROT));
  }

  bool running = false;
  int running_dist = 0;
  int prev = 0;
  int have = 0;
  int ignore = 0;
  bool goal = false;
  while (!q.empty() && !goal) {
    const Event ev = q.top().ev;
    const int dist = q.top().dist;
    q.pop();
    if (running) {
      running_dist += dist - prev;
    }
    switch (ev) {
      case CARROT:
        if (running) {
          if (have == K) {
            // over boost
            ++ignore;
            q.push(event(dist+V*T, DOWN));
          } else {
            ++have;
          }
        } else {
          q.push(event(dist+V*T, DOWN));
          running = true;
        }
        break;
      case DOWN:
        if (ignore > 0) {
          --ignore;
        } else {
          if (have > 0) {
            --have;
            q.push(event(dist+V*T, DOWN));
          } else {
            running = false;
          }
        }
        break;
      case GOAL:
        goal = true;
        break;
    }
    prev = dist;
  }

  printf("%.6f\n", running_dist/double(V) + (L-running_dist)/double(U));
  return 0;
}
