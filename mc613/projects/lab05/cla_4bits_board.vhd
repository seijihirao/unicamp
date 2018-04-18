-- brief : lab05 - question 2

library ieee;
use ieee.std_logic_1164.all;

entity cla_4bits_board is
  port(
    SW    : in  std_logic_vector(8 downto 0);
    LEDR  : out std_logic_vector(4 downto 0)
  );
end cla_4bits_board;

architecture rtl of cla_4bits_board is
component cla_4bits
	port(
		x    : in  std_logic_vector(3 downto 0);
		y    : in  std_logic_vector(3 downto 0);
		cin  : in  std_logic;
		sum  : out std_logic_vector(3 downto 0);
		cout : out std_logic
	);
end component;
begin
	cla: cla_4bits port map (
		x(0)	=>	SW(0),
		x(1)	=>	SW(1),
		x(2)	=>	SW(2),
		x(3)	=>	SW(3),
		y(0)	=>	SW(4),
		y(1)	=>	SW(5),
		y(2)	=>	SW(6),
		y(3)	=>	SW(7),
		cin	=>	SW(8),
		sum(0)=>	LEDR(0),
		sum(1)=>	LEDR(1),
		sum(2)=>	LEDR(2),
		sum(3)=>	LEDR(3),
		cout	=>	LEDR(4)
	);
end rtl;

