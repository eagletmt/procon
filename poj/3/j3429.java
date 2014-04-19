import java.util.*;
import java.math.*;

public class Main {
  public static void main(String[] args) {
    Scanner cin = new Scanner(System.in);
    int N = cin.nextInt();
    ArrayList<P> ps = new ArrayList<P>();;
    for (int i = 0; i < N; i++) {
      int x = cin.nextInt();
      int y = cin.nextInt();
      ps.add(new P(new Ratio(x), new Ratio(y)));
    }
    int M = cin.nextInt();
    int ans = 0;
    Ratio zero = new Ratio(0);
    for (int i = 0; i < M; i++) {
      int a = cin.nextInt()-1;
      int b = cin.nextInt()-1;
      int c = cin.nextInt()-1;
      int d = cin.nextInt()-1;
      P p = new Line(ps.get(a), ps.get(b)).intersection(new Line(ps.get(c), ps.get(d)));;
      if (ans == 0 && p.x.equals(zero) && p.y.equals(zero)) {
        ans = i+1;
      }
      ps.add(p);
    }
    System.out.println(ans);
  }
}

class Ratio {
  BigInteger n, d;
  Ratio(int x) { this.n = BigInteger.valueOf(x);  this.d = BigInteger.ONE; }
  Ratio(BigInteger n, BigInteger d) {
    if (d.equals(BigInteger.ZERO)) {
      throw new ArithmeticException("d = 0");
    }
    if (n.signum() < 0 && d.signum() < 0) {
      this.n = n.negate();
      this.d = d.negate();
    } else {
      this.n = n;
      this.d = d;
    }
  }

  boolean equals(Ratio r) { return n.equals(r.n) && d.equals(r.d); }
  Ratio add(Ratio r) {
    BigInteger g = d.gcd(r.d);
    return new Ratio(r.d.divide(g).multiply(n).add(d.divide(g).multiply(r.n)), d.divide(g).multiply(r.d));
  }
  Ratio subtract(Ratio r) { return add(new Ratio(r.n.negate(), r.d)); }
  Ratio multiply(Ratio r) {
    BigInteger g1 = n.gcd(r.d), g2 = d.gcd(r.n);
    return new Ratio(n.divide(g1).multiply(r.n.divide(g2)), d.divide(g2).multiply(r.d.divide(g1)));
  }
  Ratio divide(Ratio r) { return multiply(new Ratio(r.d, r.n)); }
}

class P {
  Ratio x, y;
  P(Ratio x, Ratio y) { this.x = x; this.y = y; }

  P add(P p) { return new P(x.add(p.x), y.add(p.y)); }
  P subtract(P p) { return new P(x.subtract(p.x), y.subtract(p.y)); }
  P multiply(Ratio c) { return new P(x.multiply(c), y.multiply(c)); }
  Ratio cross(P p) { return x.multiply(p.y).subtract(p.x.multiply(y)); }
}

class Line {
  P a, b;
  Line(P a, P b) { this.a = a;  this.b = b; }
  P intersection(Line ln) {
    P x = b.subtract(a);
    P y = ln.b.subtract(ln.a);
    return a.add(x.multiply(y.cross(ln.a.subtract(a)).divide(y.cross(x))));
  }
}
