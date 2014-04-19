#include <iostream>
#include <queue>
using namespace std;

struct query {
  int qnum, period, time;

  query(int n, int p, int t) : qnum(n), period(p), time(t) {}

  bool operator<(const query& q) const
  {
    return time == q.time ? qnum > q.qnum : time > q.time;
  }
};

void process(priority_queue<query>& queries, int k)
{
  for (int i = 0; i < k; i++) {
    query q = queries.top();
    queries.pop();
    cout << q.qnum << endl;
    queries.push(query(q.qnum, q.period, q.time + q.period));
  }
}

int main()
{
  priority_queue<query> queries;
  string input;
  while (cin >> input && input != "#") {
    int n, p;
    cin >> n >> p;
    queries.push(query(n, p, p));
  }

  int k;
  cin >> k;
  process(queries, k);
  return 0;
}
