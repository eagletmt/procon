import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
  public static void main(String[] args) {
    Scanner cin = new Scanner(System.in);
    int N = cin.nextInt();
    final BigInteger n26 = BigInteger.valueOf(26);
    while (N-- > 0) {
      char[] s = cin.next().toCharArray();
      BigInteger[] xs = new BigInteger[s.length];
      for (int i = 0; i < s.length; i++) {
        xs[i] = BigInteger.valueOf(s[i]-'a');
      }

      BigInteger n = BigInteger.ZERO;
      BigInteger e = BigInteger.ONE;
      for (int i = 0; i < s.length; i++) {
        n = n.multiply(n26).add(xs[i]);
        e = e.multiply(n26);
      }
      e = e.divide(n26);
      BigInteger min = n;
      int ans = 0;
      for (int i = 1; i < s.length; i++) {
        n = n.subtract(xs[i-1].multiply(e)).multiply(n26).add(xs[i-1]);
        if (n.compareTo(min) < 0) {
          min = n;
          ans = i;
        }
      }
      System.out.println(ans+1);
    }
  }
}