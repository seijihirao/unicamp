library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity clk_div is
  port (
    clk : in std_logic;
    clk_hz : out std_logic
  );
end clk_div;

architecture behavioral of clk_div is
signal count: integer := 0;
signal output: std_logic := '0';
begin
	process(clk)
	begin
		if (clk'event and clk = '1') then
			count <= count + 1;
			
			if (count = 50000000) then
				output <= '1';
			end if;
			
			if (count = 50000001) then
				output <= '0';
				count <= 0;
			end if;
		
		end if;
	end process;
	
	clk_hz <= output;
end behavioral;
