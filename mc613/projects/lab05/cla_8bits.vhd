-- brief : lab05 - question 2

library ieee;
use ieee.std_logic_1164.all;

entity cla_8bits is
  port(
    x    : in  std_logic_vector(7 downto 0);
    y    : in  std_logic_vector(7 downto 0);
    cin  : in  std_logic;
    sum  : out std_logic_vector(7 downto 0);
    cout : out std_logic
  );
end cla_8bits;

architecture rtl of cla_8bits is
signal g: std_logic_vector(7 downto 0);
signal p: std_logic_vector(7 downto 0);
signal c: std_logic_vector(8 downto 0);
begin
	c(0) <= cin;
	g <= x and y;
	p <= x or y;
	cla:
		for i in 0 to 7 generate
			sum(i)	<= (x(i) xor y(i)) xor c(i);
			c(i+1)	<=	g(i) or (p(i) and c(i));
		end generate;
	cout <= c(8);
end rtl;

