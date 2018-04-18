-- brief : lab05 - question 2

library ieee;
use ieee.std_logic_1164.all;

entity cla_8bits_partial is
  port(
    x    : in  std_logic_vector(7 downto 0);
    y    : in  std_logic_vector(7 downto 0);
    cin  : in  std_logic;
    sum  : out std_logic_vector(7 downto 0);
    cout : out std_logic
  );
end cla_8bits_partial;

architecture rtl of cla_8bits_partial is
component cla_4bits is
	port(
		x    : in  std_logic_vector(3 downto 0);
		y    : in  std_logic_vector(3 downto 0);
		cin  : in  std_logic;
		sum  : out std_logic_vector(3 downto 0);
		cout : out std_logic
	);
end component;
signal carry: std_logic; 
begin
	cla1: cla_4bits port map (
		x(0)	=>	x(0),
		x(1)	=>	x(1),
		x(2)	=>	x(2),
		x(3)	=>	x(3),
		y(0)	=>	y(0),
		y(1)	=>	y(1),
		y(2)	=>	y(2),
		y(3)	=>	y(3),
		cin	=>	cin,
		sum(0)=>	sum(0),
		sum(1)=>	sum(1),
		sum(2)=>	sum(2),
		sum(3)=>	sum(3),
		cout	=>	carry
	);
	cla2: cla_4bits port map (
		x(0)	=>	x(4),
		x(1)	=>	x(5),
		x(2)	=>	x(6),
		x(3)	=>	x(7),
		y(0)	=>	y(4),
		y(1)	=>	y(5),
		y(2)	=>	y(6),
		y(3)	=>	y(7),
		cin	=>	carry,
		sum(0)=>	sum(4),
		sum(1)=>	sum(5),
		sum(2)=>	sum(6),
		sum(3)=>	sum(7),
		cout	=>	cout
	);
end rtl;

