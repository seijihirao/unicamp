library ieee;
use ieee.std_logic_1164.all;

entity xbar_gen is
	generic(N: integer := 4);
	port(s: in std_logic_vector (N-1 downto 0);
       y1, y2: out std_logic);
end xbar_gen;

architecture rtl of xbar_gen is

signal tmp1: std_logic_vector(N downto 0);
signal tmp2: std_logic_vector(N downto 0);
component xbar_v3
	port(x1, x2, s: in std_logic;
       y1, y2: out std_logic);
end component;

begin
	tmp1(0) <= '1';
	tmp2(0) <= '0';
	
	generate_label:
	for i in 0 to N-1 generate
		xbar: xbar_v3 port map (
			x1 	=> tmp1(i),
			x2 	=> tmp2(i),
			s		=> s(i),
			y1		=>	tmp1(i+1),
			y2		=> tmp2(i+1)
		);
	end generate;
	
	y1 <= tmp1(N);
	y2 <= tmp2(N);
	
end rtl;

