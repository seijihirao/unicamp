library ieee;
use ieee.std_logic_1164.all;

entity two_comp_to_7seg is
  port (
    bin : in std_logic_vector(3 downto 0);
    segs : out std_logic_vector(6 downto 0);
    neg : out std_logic
  );
end ;

architecture behavioral of two_comp_to_7seg is
begin

	with bin select
		segs	<=	"1000000" when "0000",	-- 0
					"1111001" when "0001",	-- 1
					"0100100" when "0010",	-- 2
					"0110000" when "0011",	-- 3
					"0011001" when "0100",	-- 4
					"0010010" when "0101",	-- 5
					"0000010" when "0110",	-- 6
					"1111000" when "0111",	-- 7
					"0000000" when "1000",	-- -8
					"1111000" when "1001",	-- -7
					"0000010" when "1010",	-- -6
					"0010010" when "1011",	-- -5
					"0011001" when "1100",	-- -4
					"0110000" when "1101",	-- -3
					"0100100" when "1110",	-- -2
					"1111001" when "1111";	-- -1
					
	neg <= NOT (bin(3));
end behavioral;
