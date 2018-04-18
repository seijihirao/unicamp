library ieee;
use ieee.std_logic_1164.all;

entity zbuffer is
	generic (n : integer := 8) ;
	port(
		enable: in std_logic;
		input: in std_logic_vector(n-1 downto 0);
		output: out std_logic_vector(n-1 downto 0)
	);
end zbuffer;

architecture Behavior of zbuffer is
begin
	output <= (others => 'Z') when enable = '0' else input;
end Behavior;