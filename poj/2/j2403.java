import java.io.*;
import java.util.*;

public class Main
{
  public static void main(String[] args) throws Exception
  {
    Scanner cin = new Scanner(System.in);
    final int m = cin.nextInt();
    final int n = cin.nextInt();
    Map<String, Integer> dict = new HashMap<String, Integer>();
    for (int i = 0; i < m; i++) {
      final String word = cin.next();
      final int score = cin.nextInt();
      dict.put(word, score);
    }

    for (int i = 0; i < n; i++) {
      String str;
      int score = 0;
      while (!(str = cin.next()).equals(".")) {
        Integer c = dict.get(str);
        if (c != null) {
          score += c;
        }
      }
      System.out.println(score);
    }
  }
}
