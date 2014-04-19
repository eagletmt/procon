#include <iostream>
#include <sstream>
#include <map>
using namespace std;

struct unknown {};

struct MolecularFormula
{
  map<string,int> weights;

  void input_weight(const string& atom, int w)
  {
    weights.insert(make_pair(atom, w));
  }

  int calculate_weight(const string& formula) const
  {
    return work(formula, 0).first;
  }

  pair<int,int> work(const string& formula, size_t pos) const
  {
    int weight = 0;
    while (pos < formula.size()) {
      if (formula[pos] == '(') {
        const pair<int,int> r = work(formula, pos+1);
        int w = r.first;
        pos = r.second;
        if ('0' <= formula[pos] && formula[pos] <= '9') {
          int scale = 0;
          while ('0' <= formula[pos] && formula[pos] <= '9') {
            scale = scale*10 + formula[pos]-'0';
            ++pos;
          }
          w *= scale;
        }
        weight += w;
      } else if ('A' <= formula[pos] && formula[pos] <= 'Z') {
        string atom = string(1, formula[pos]);
        ++pos;
        while ('a' <= formula[pos] && formula[pos] <= 'z') {
          atom += formula[pos];
          ++pos;
        }
        const map<string,int>::const_iterator it = weights.find(atom);
        if (it == weights.end()) {
          throw unknown();
        }
        int w = it->second;
        if ('0' <= formula[pos] && formula[pos] <= '9') {
          int scale = 0;
          while ('0' <= formula[pos] && formula[pos] <= '9') {
            scale = scale*10 + formula[pos]-'0';
            ++pos;
          }
          w *= scale;
        }
        weight += w;
      } else if (formula[pos] == ')') {
        return make_pair(weight, pos+1);
      }
    }
    return make_pair(weight, pos);
  }
};

int main()
{
  MolecularFormula mf;
  string s;
  while (getline(cin, s) && s != "END_OF_FIRST_PART") {
    istringstream iss(s);
    string atom;
    int w;
    iss >> atom >> w;
    mf.input_weight(atom, w);
  }
  while (getline(cin, s) && s != "0") {
    try {
      cout << mf.calculate_weight(s) << endl;
    } catch (const unknown&) {
      cout << "UNKNOWN" << endl;
    }
  }
  return 0;
}