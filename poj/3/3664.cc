#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct cmp_fst
{
  typedef pair<pair<int,int>,int> value_type;
  bool operator()(const value_type& lhs, const value_type& rhs) const
  {
    return lhs.first.first > rhs.first.first;
  }
};

struct cmp_snd
{
  typedef pair<pair<int,int>,int> value_type;
  bool operator()(const value_type& lhs, const value_type& rhs) const
  {
    return lhs.first.second < rhs.first.second;
  }
};

int main()
{
  int N, K;
  scanf("%d %d", &N, &K);
  vector<pair<pair<int,int>,int> > cows; cows.reserve(N);
  for (int i = 0; i < N; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    cows.push_back(make_pair(make_pair(a,b), i));
  }
  partial_sort(cows.begin(), cows.begin()+K, cows.end(), cmp_fst());
  printf("%d\n", max_element(cows.begin(), cows.begin()+K, cmp_snd())->second + 1);
  return 0;
}
