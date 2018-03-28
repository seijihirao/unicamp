library ieee;
use ieee.std_logic_1164.all;

entity alu_board is
  port (
    SW : in std_logic_vector(9 downto 0);
    HEX5, HEX4, HEX3, HEX2, HEX1, HEX0 : out std_logic_vector(6 downto 0);
    LEDR : out std_logic_vector(3 downto 0)
  );
end alu_board;

architecture behavioral of alu_board is
component alu
  port (
    a, b : in std_logic_vector(3 downto 0);
    F : out std_logic_vector(3 downto 0);
    s0, s1 : in std_logic;
    Z, C, V, N : out std_logic
  );
end component;

component two_comp_to_7seg
  port (
    bin : in std_logic_vector(3 downto 0);
    segs : out std_logic_vector(6 downto 0);
    neg : out std_logic
  );
end component;

signal result: std_logic_vector(3 downto 0);
signal neg_a, neg_b, neg_r: std_logic;
begin
	sum: alu port map(
		s0		=>	SW(9),
		s1		=>	SW(8),
		a(3)	=>	SW(7),
		a(2)	=>	SW(6),
		a(1)	=>	SW(5),
		a(0)	=>	SW(4),
		b(3)	=>	SW(3),
		b(2)	=>	SW(2),
		b(1)	=>	SW(1),
		b(0)	=>	SW(0),
		F		=> result,
		Z		=> LEDR(3),
		C		=> LEDR(2),
		V		=> LEDR(1),
		N		=> LEDR(0)
	);
	
	hex_0: two_comp_to_7seg port map(
		bin	=>	result,
		segs	=>	HEX0,
		neg	=> neg_r
	);
	
	HEX1(0) <= '1';
	HEX1(1) <= '1';
	HEX1(2) <= '1';
	HEX1(3) <= '1';
	HEX1(4) <= '1';
	HEX1(5) <= '1';
	HEX1(6) <= neg_r;
	
	hex_2: two_comp_to_7seg port map(
		bin(0)	=>	SW(0),
		bin(1)	=>	SW(1),
		bin(2)	=>	SW(2),
		bin(3)	=>	SW(3),
		segs	=>	HEX2,
		neg	=> neg_b
	);
	
	
	HEX3(0) <= '1';
	HEX3(1) <= '1';
	HEX3(2) <= '1';
	HEX3(3) <= '1';
	HEX3(4) <= '1';
	HEX3(5) <= '1';
	HEX3(6) <= neg_b;
	
	hex_4: two_comp_to_7seg port map(
		bin(0)	=>	SW(4),
		bin(1)	=>	SW(5),
		bin(2)	=>	SW(6),
		bin(3)	=>	SW(7),
		segs	=>	HEX4,
		neg	=> neg_a
	);
	
	
	HEX5(0) <= '1';
	HEX5(1) <= '1';
	HEX5(2) <= '1';
	HEX5(3) <= '1';
	HEX5(4) <= '1';
	HEX5(5) <= '1';
	HEX5(6) <= neg_a;
	
end behavioral;
