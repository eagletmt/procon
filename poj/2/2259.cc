#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

int main()
{
  int K = 0;
  int T;
  while (scanf("%d", &T) == 1 && T != 0) {
    static int team_tbl[1000000];
    for (int i = 0; i < T; i++) {
      int N;
      scanf("%d", &N);
      for (int j = 0; j < N; j++) {
        int id;
        scanf("%d", &id);
        team_tbl[id] = i;
      }
    }

    printf("Scenario #%d\n", ++K);
    queue<int> q;
    vector<queue<int> > team_queues(T);
    char buf[8];
    while (scanf("%s", buf) == 1 && strcmp(buf, "STOP") != 0) {
      if (strcmp(buf, "ENQUEUE") == 0) {
        int id;
        scanf("%d", &id);
        const int team = team_tbl[id];
        if (team_queues[team].empty()) {
          q.push(team);
        }
        team_queues[team].push(id);
      } else {
        const int team = q.front();
        const int id = team_queues[team].front();
        team_queues[team].pop();
        if (team_queues[team].empty()) {
          q.pop();
        }
        printf("%d\n", id);
      }
    }
    puts("");
  }
  return 0;
}