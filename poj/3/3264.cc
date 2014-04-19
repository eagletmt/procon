#include <cstdio>
#include <vector>
#include <functional>
#include <cmath>
using namespace std;

template <class Compare>
struct SegmentTree
{
  const vector<int>& cows;
  vector<int> indexes;
  Compare cmp;
  SegmentTree(const vector<int>& cs)
    : cows(cs), indexes(4*cs.size(), -1)
  {
    build(0, 0, cs.size());
  }

  void build(int idx, int left, int right)
  {
    if (left+1 == right) {
      indexes[idx] = left;
    } else {
      const int mid = (left + right)/2;
      build(2*idx+1, left, mid);
      build(2*idx+2, mid, right);
      // minimum in [left, right)
      if (cmp(cows[indexes[2*idx+1]], cows[indexes[2*idx+2]])) {
        indexes[idx] = indexes[2*idx+1];
      } else {
        indexes[idx] = indexes[2*idx+2];
      }
    }
  }

  inline int query_value(int left, int right) const { return cows[query_index(left, right)]; }

  inline int query_index(int left, int right) const { return query_index(left, right, 0, 0, cows.size()); }

  int query_index(int left, int right, int i, int a, int b) const
  {
    // [a, b) is the range of indexes[i]
    if (b <= left || right <= a) {
      // does not intersect
      return -1;
    } else if (left <= a && b <= right) {
      // contains
      return indexes[i];
    } else {
      const int m = (a+b)/2;
      const int l = query_index(left, right, 2*i+1, a, m);
      const int r = query_index(left, right, 2*i+2, m, b);
      if (l == -1) {
        return r;
      } else if (r == -1) {
        return l;
      } else {
        if (cmp(cows[l], cows[r])) {
          return l;
        } else {
          return r;
        }
      }
    }
  }
};

int main()
{
  int N, Q;
  scanf("%d %d", &N, &Q);
  vector<int> cows(N);
  for (int i = 0; i < N; i++) {
    scanf("%d", &cows[i]);
  }

  const SegmentTree<less<int> > segtree_min(cows);
  const SegmentTree<greater<int> > segtree_max(cows);

  for (int i = 0; i < Q; i++) {
    int l, r;
    scanf("%d %d", &l, &r);
    --l;
    printf("%d\n", segtree_max.query_value(l, r) - segtree_min.query_value(l, r));
  }
  return 0;
}