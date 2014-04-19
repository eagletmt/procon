import java.util.*;
import java.math.*;

public class Main {
  public static void main(String[] args) {
    BigInteger[] tbl = new BigInteger[26];
    tbl[0] = BigInteger.valueOf(26);
    for (int i = 1; i < 26; i++) {
      tbl[i] = tbl[i-1].multiply(BigInteger.valueOf(26-i));
    }

    Scanner cin = new Scanner(System.in);
    for (int N; (N = cin.nextInt()) != 0;) {
      char[] s = cin.next().toCharArray();

      ArrayList<Character> t = new ArrayList<Character>();
      for (int i = 0; i < 26; i++) {
        t.add((char)('A'+i));
      }

      BigInteger ans = BigInteger.ZERO;
      for (int i = 0; i < N; i++) {
        int idx = t.indexOf(s[i]);
        t.remove(idx);
        BigInteger n = BigInteger.valueOf(idx);
        for (int j = 0; j < (N-i-1); j++) {
          n = n.multiply(BigInteger.valueOf(t.size()-j));
        }
        ans = ans.add(n);
      }
      System.out.println(ans);
    }
  }
}