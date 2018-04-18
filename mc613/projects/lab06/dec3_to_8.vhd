library ieee;
use ieee.std_logic_1164.all;

entity dec3_to_8 is
	port(
		enable: in std_logic;
		input: in std_logic_vector(2 downto 0);
		output: out std_logic_vector(7 downto 0)
	);
end dec3_to_8;

architecture Behavior of dec3_to_8 is
signal input_t: std_logic_vector(3 downto 0); 
begin
	input_t <= enable & input;
	with input_t select output <=
		"00000001" when "1000",
		"00000010" when "1001",
		"00000100" when "1010",
		"00001000" when "1011",
		"00010000" when "1100",
		"00100000" when "1101",
		"01000000" when "1110",
		"10000000" when "1111",
		"00000000" when others;
end Behavior;