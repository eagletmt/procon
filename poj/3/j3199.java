import java.util.*;
import java.math.*;

public class Main {
  public static void main(String[] args) {
    Scanner cin = new Scanner(System.in);
    while (true) {
      final int N = cin.nextInt();
      final int D = cin.nextInt();
      if (N == 0 && D == 0) {
        break;
      }

      BigInteger n = new BigInteger(""+N);
      System.out.println(n.pow(D));
    }
  }
}
