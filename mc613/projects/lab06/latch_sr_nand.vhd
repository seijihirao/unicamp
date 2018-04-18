library ieee;
use ieee.std_logic_1164.all;

entity latch_sr_nand is
	port(
		S_n, R_n: in std_logic;
		Q_a, Q_b: out std_logic
	);
end latch_sr_nand;

architecture Behavior of latch_sr_nand is
signal temp_a, temp_b: std_logic;
begin
	temp_a <= S_n nand temp_b;
	temp_b <= R_n nand temp_a;
	Q_a <= temp_a;
	Q_b <= temp_b;
end Behavior;