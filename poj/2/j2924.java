import java.io.*;
import java.util.*;
import java.math.*;

public class Main
{
  public static void main(String args[]) throws Exception
  {
    Scanner cin = new Scanner(System.in);
    final int T = cin.nextInt();
    for (int i = 1; i <= T; i++) {
      BigInteger n = new BigInteger(cin.next(), 10);
      BigInteger m = new BigInteger(cin.next(), 10);
      System.out.println("Scenario #" + i + ':');
      System.out.println(n.add(m).multiply(m.subtract(n).add(BigInteger.ONE)).shiftRight(1));
      System.out.println("");
    }
  }
}
