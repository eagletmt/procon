#include <iostream>
#include <string>

using namespace std;

string dp[200];
bool used[200];

int main() {
    while(true) {
      int n;
      cin >> n;
      if(n == 0) break;
      for(int i = 0; i < n; ++i) {
        dp[i] = "";
        used[i] = false;
      }
      dp[0] = "";
      used[0] = true;

      int digit = 0;
      int mod = 1;
      do {
        string dptmp[200];
        bool usedtmp[200];
        for(int j = 0; j < n; ++j) {
          dptmp[j] = dp[j];
          usedtmp[j] = used[j];
        }
        for(int i = 0; i < n; ++i) {
          if(used[i]) {
            int next = (i+mod) % n;
            string nextstr = "1";
            for(int j = 0; j < digit-dp[i].size(); ++j) {
              nextstr += "0";
            }
            nextstr += dp[i];
            dptmp[next] = nextstr;
            usedtmp[next] = true;
            //cout << i << ":" << digit << ";" << nextstr << endl;

            if(next == 0) {
              cout << nextstr << endl;
              goto nextloop;
            }
          }
        }
        mod = (mod*10) % n;
        for(int i = 0; i < n; ++i) {
          dp[i] = dptmp[i];
          used[i] = usedtmp[i];
        }

      } while(++digit);
nextloop:
      ;
    }

    return 0;
}
