#include <iostream>
#include <cstdio>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;

struct item
{
  int price;
  item(int p) : price(p) {}
};

struct bidder
{
  int account;
  bidder(int p) : account(p) {}
};

struct event
{
  int tm;
  int price;
  int tid, bid;
  event(int t, int i) : tm(t), price(-1), tid(i), bid(-1) {}
  event(int t, int p, int i, int j) : tm(t), price(p), tid(i), bid(j) {}
  bool bid_p() const { return price != -1; }
  bool operator<(const event& e) const
  {
    if (tm == e.tm) {
      // bid event preceeds
      return e.bid_p();
    } else {
      return tm > e.tm;
    }
  }
};

int read(string& t)
{
  replace(t.begin(), t.end(), ':', ' ');
  istringstream iss(t);
  int h, m, s;
  iss >> h >> m >> s;
  return 3600*h + 60*m + s;
}

int main()
{
  int N;
  cin >> N;
  map<int, item> items;
  priority_queue<event> q;
  for (int i = 0; i < N; i++) {
    int tid;
    double p;
    string e;
    cin >> tid >> p >> e;
    q.push(event(read(e), tid));
    items.insert(make_pair(tid, p*100));
  }
  int M;
  cin >> M;
  map<int, bidder> bidders;
  for (int i = 0; i < M; i++) {
    int id;
    double p;
    cin >> id >> p;
    bidders.insert(make_pair(id, 100*p));
  }
  int K;
  cin >> K;
  for (int i = 0; i < K; i++) {
    int tid, bid;
    double p;
    string t;
    cin >> tid >> bid >> p >> t;
    q.push(event(read(t), p*100, tid, bid));
  }

  set<int> finished;
  typedef map<int, vector<pair<int,int> > > record;
  record curbids;
  while (!q.empty()) {
    const event evt = q.top();
    q.pop();
    if (evt.bid_p()) {
      if (finished.count(evt.tid)) {
        continue;
      }
      item item = items.find(evt.tid)->second;
      if (evt.price < item.price) {
        continue;
      }
      curbids[evt.tid].push_back(make_pair(evt.price, evt.bid));
    } else {
      vector<pair<int,int> > &v = curbids[evt.tid];
      printf("Item %d ", evt.tid);
      sort(v.begin(), v.end(), greater<pair<int,int> >());
      for (vector<pair<int,int> >::const_iterator jt = v.begin(); jt != v.end(); ++jt) {
        int p = jt->first;
        int bid = jt->second;
        bidder& bidder = bidders.find(bid)->second;
        if (p <= bidder.account) {
          bidder.account -= p;
          printf("Bidder %d Price %.2f\n", bid, p/100.0);
          goto NEXT;
        }
      }
      puts("Reserve not met.");
NEXT:
      ;
      curbids.erase(curbids.find(evt.tid));
      finished.insert(evt.tid);
    }
  }
  return 0;
}
