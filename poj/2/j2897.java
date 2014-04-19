import java.util.*;
import java.math.*;

public class Main {
  public static void main(String[] args) {
    Scanner cin = new Scanner(System.in);
    int T = cin.nextInt();
    while (T-- > 0) {
      int N = cin.nextInt();
      int K = cin.nextInt();
      System.out.println(solve(N, K));
    }
  }

  static final BigInteger five = BigInteger.valueOf(5);
  static final BigInteger magic = BigInteger.valueOf(39);
  static BigInteger solve(int N, int K) {
    final BigInteger n = BigInteger.valueOf(N);
    final BigInteger k = BigInteger.valueOf(K);
    final BigInteger num = BigInteger.valueOf(10*N-1);
    BigInteger e = BigInteger.ONE;
    for (int i = 0; i < 100; i++) {
      BigInteger x = k.multiply(e.subtract(n));
      BigInteger[] r = x.divideAndRemainder(num);
      if (r[1].intValue() == 0) {
        BigInteger ans = BigInteger.TEN.multiply(r[0]).add(k);
        if (ans.toString().length() == i+1) {
          return ans;
        }
      }
      e = e.multiply(BigInteger.TEN);
    }
    return BigInteger.ZERO;
  }
}