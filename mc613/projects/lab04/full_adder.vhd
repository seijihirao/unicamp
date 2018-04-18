library ieee;
use ieee.std_logic_1164.all;

entity full_adder is
  port (
    x, y : in std_logic;
    r : out std_logic;
    cin : in std_logic;
    cout : out std_logic
  );
end full_adder;

architecture structural of full_adder is
signal tmp: std_logic;
begin
  r <= (x xor y) xor cin;
  cout <= (x and y) or ((x xor y) and cin);
end structural;
