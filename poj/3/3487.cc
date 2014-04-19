#include <iostream>
#include <vector>
#include <map>
#include <stack>
using namespace std;

vector<int> gale_shapley(const vector<vector<int> >& male_prefer, const vector<vector<int> >& female_rank)
{
  const int N = male_prefer.size();
  stack<int> stk;
  for (int i = 0; i < N; i++) {
    stk.push(i);
  }
  vector<int> idx(N, 0);
  vector<int> ans(N, -1);
  while (!stk.empty()) {
    const int m = stk.top();
    stk.pop();
    const int f = male_prefer[m][idx[m]];
    if (ans[f] == -1) {
      ans[f] = m;
    } else if (female_rank[f][m] < female_rank[f][ans[f]]) {
      stk.push(ans[f]);
      ++idx[ans[f]];
      ans[f] = m;
    } else {
      ++idx[m];
      stk.push(m);
    }
  }

  return ans;
}

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int N;
    cin >> N;
    map<char, int> male_name, female_name;
    string rev_male(N, ' '), rev_female(N, ' ');
    for (int i = 0; i < N; i++) {
      char c;
      cin >> c;
      const int id = male_name.size();
      male_name.insert(make_pair(c, id));
      rev_male[id] = c;
    }
    for (int i = 0; i < N; i++) {
      char c;
      cin >> c;
      const int id = female_name.size();
      female_name.insert(make_pair(c, id));
      rev_female[id] = c;
    }
    vector<vector<int> > male_prefer(N, vector<int>(N)), female_rank(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
      char c, _;
      cin >> c >> _;
      const int m = male_name[c];
      string s;
      cin >> s;
      for (int j = 0; j < N; j++) {
        male_prefer[m][j] = female_name[s[j]];
      }
    }
    for (int i = 0; i < N; i++) {
      char c, _;
      cin >> c >> _;
      const int f = female_name[c];
      string s;
      cin >> s;
      for (int j = 0; j < N; j++) {
        female_rank[f][male_name[s[j]]] = j;
      }
    }

    vector<int> ans = gale_shapley(male_prefer, female_rank);
    vector<int> rev(N);
    for (int i = 0; i < N; i++) {
      rev[ans[i]] = i;
    }
    for (int i = 0; i < N; i++) {
      cout << rev_male[i] << ' ' << rev_female[rev[i]] << endl;
    }
    cout << endl;
  }
  return 0;
}
