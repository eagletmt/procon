#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <cassert>
using namespace std;

typedef enum { DCL, ASSIGN, GOTO, INC, DEC, END } inst_type;

struct inst
{
  inst_type stmt;
  int label;
  char id;
  int value;
  inst(const string& line)
  {
    istringstream iss(line);
    string c;
    iss >> c;
    if (c == "DCL") {
      stmt = DCL;
      iss >> id;
    } else if (c == "GOTO") {
      stmt = GOTO;
      if (iss >> label) {
        id = ' ';
      } else {
        iss.clear();
        iss.str(line);
        iss >> c >> id >> label;
      }
      --label;
    } else if (c == "INC") {
      stmt = INC;
      iss >> id;
    } else if (c == "DEC") {
      stmt = DEC;
      iss >> id;
    } else if (c == "END") {
      stmt = END;
    } else {
      stmt = ASSIGN;
      assert(c.size() == 1);
      id = c[0];
      iss >> c;
      assert(c == "=");
      iss >> value;
    }
  }
};

struct machine
{
  vector<inst> prog;

  void execute(ostream& os) const
  {
    map<char, pair<int,bool> > mem;
    for (int pc = 0; prog[pc].stmt != END;) {
      const inst& i = prog[pc];
      switch (i.stmt) {
        case DCL:
          if (mem.count(i.id) && !mem[i.id].second) {
            os << pc+1 << ' ' << 1 << endl;
          } else {
            mem[i.id] = make_pair(0, false);
          }
          ++pc;
          break;

        case GOTO:
          if (i.id == ' ') {
            pc = i.label;
          } else {
            if (!mem.count(i.id)) {
            os << pc+1 << ' ' << 2 << endl;
              ++pc;
            } else {
              mem[i.id].second = true;
              if (mem[i.id].first > 0) {
                pc = i.label;
              } else {
                ++pc;
              }
            }
          }
          break;

        case INC:
          if (!mem.count(i.id)) {
            os << pc+1 << ' ' << 2 << endl;
          } else {
            mem[i.id].second = true;
            ++mem[i.id].first;
          }
          ++pc;
          break;

        case DEC:
          if (!mem.count(i.id)) {
            os << pc+1 << ' ' << 2 << endl;
          } else {
            mem[i.id].second = true;
            --mem[i.id].first;
          }
          ++pc;
          break;

        case ASSIGN:
          if (!mem.count(i.id)) {
            os << pc+1 << ' ' << 2 << endl;
          } else {
            mem[i.id].second = true;
            mem[i.id].first = i.value;
          }
          ++pc;
          break;

        case END:
          assert(NULL);
          break;
      }
    }
  }
};

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; ++Ti) {
    int N;
    cin >> N;
    machine m;
    string line;
    cin.ignore();
    for (int i = 0; i < N; i++) {
      getline(cin, line);
      m.prog.push_back(inst(line));
    }
    cout << Ti << endl;
    m.execute(cout);
  }
  return 0;
}