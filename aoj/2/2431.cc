#include <iostream>
#include <vector>
#include <functional>
using namespace std;

template <class T, class Compare>
struct SegmentTree/*{{{*/
{
  vector<T>& mem;
  vector<int> indexes;
  Compare cmp;
  SegmentTree(vector<T>& cs)
    : mem(cs), indexes(4*cs.size(), -1)
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
      if (cmp(mem[indexes[2*idx+1]], mem[indexes[2*idx+2]])) {
        indexes[idx] = indexes[2*idx+1];
      } else {
        indexes[idx] = indexes[2*idx+2];
      }
    }
  }

  inline T query_value(int left, int right) const { return mem[query_index(left, right)]; }

  inline int query_index(int left, int right) const { return query_index(left, right, 0, 0, mem.size()); }

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
        if (cmp(mem[l], mem[r])) {
          return l;
        } else {
          return r;
        }
      }
    }
  }

  void update(int idx, const T& val)
  {
    mem[idx] = val;
    update_index(0, mem.size(), 0, idx);
  }

  void update_index(int left, int right, int i, int idx)
  {
    if (left+1 == right) {
      //indexes[i] = idx;
    } else {
      const int mid = (left+right)/2;
      if (idx < mid) {
        update_index(left, mid, 2*i+1, idx);
      } else {
        update_index(mid, right, 2*i+2, idx);
      }
      if (cmp(mem[indexes[2*i+1]], mem[indexes[2*i+2]])) {
        indexes[i] = indexes[2*i+1];
      } else {
        indexes[i] = indexes[2*i+2];
      }
    }
  }
};/*}}}*/

int main()
{
  int N;
  cin >> N;
  vector<long long> mem(N+1, 0);
  SegmentTree<long long, greater<long long> > segtree(mem);
  long long sum = 0, a = 0;
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    sum += x;
    long long v = segtree.query_value(0, x);
    a = max(a, v+x);
    segtree.update(x, v+x);
  }
  cout << sum - a << endl;
  return 0;
}
