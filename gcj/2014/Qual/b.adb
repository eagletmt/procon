with Ada.Text_IO;
use Ada.Text_IO;
with Ada.Long_Float_Text_IO;
use Ada.Long_Float_Text_IO;
with Ada.Integer_Text_IO;
use Ada.Integer_Text_IO;

procedure B is
  function Solve(C, F, X : in Long_Float) return Long_Float is
    acc : Long_Float := 0.0;
    n : Natural := 0;
    r : Long_Float := 2.0;
    t1, t2 : Long_Float;
  begin
    loop
      t1 := acc + X/r;
      t2 := acc + C/r + X/(r+F);
      if t1 < t2 then
        return t1;
      end if;
      acc := acc + C/r;
      r := r + F;
    end loop;
  end Solve;

  T : Natural;
  i : Natural := 0;
  C, F, X : Long_Float;
begin
  Get(Item => T);
  while i < T loop
    Get(Item => C);
    Get(Item => F);
    Get(Item => X);

    Put(Item => "Case #");
    Put(Item => i+1, Width => 0);
    Put(Item => ": ");
    Put(Item => Solve(C, F, X), Exp => 0, Fore => 0, Aft => 7);
    Put_Line("");
    i := i + 1;
  end loop;
end;
