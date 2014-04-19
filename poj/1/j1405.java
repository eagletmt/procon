import java.io.*;
import java.util.*;
import java.math.*;
public class Main
{
  public static void main(String args[]) throws Exception
  {
    Scanner cin = new Scanner(System.in);
    final int n = cin.nextInt();
    BigInteger p = new BigInteger("2", 10);
    BigInteger a = new BigInteger("2", 10);
    for (int i = 0; i < n; i++) {
      System.out.println(a);
      a = p.add(BigInteger.ONE);
      p = p.multiply(a);
    }
  }
}
