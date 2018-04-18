library ieee;
use ieee.std_logic_1164.all;

entity ff_d is
	port(
		D, Clk, Preset, Clear: in std_logic := '1';
		Q, Q_n: out std_logic
	);
end ff_d;

architecture Behavior of ff_d is
begin
	process
	begin
		wait until Clk'EVENT AND Clk = '1';
		if Clear = '1' then
			Q <= '0';
			Q_n <= '1';
		elsif Preset = '1' then
			Q <= '1';
			Q_n <= '0';
		else
			Q <= D;
			Q_n <= not(D);
		end if;
	end process;
end Behavior;