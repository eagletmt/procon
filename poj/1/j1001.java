import java.util.*;
import java.math.*;

public class Main {
  public static void main(String[] args) {
    Scanner cin = new Scanner(System.in);
    while (cin.hasNext()) {
      final BigDecimal R = new BigDecimal(cin.next());
      final int n = cin.nextInt();
      String ans = R.pow(n).stripTrailingZeros().toPlainString();
      if (ans.charAt(0) == '0') {
        ans = ans.substring(1);
      }
      System.out.println(ans);
    }
  }
}
