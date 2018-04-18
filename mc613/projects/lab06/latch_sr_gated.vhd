library ieee;
use ieee.std_logic_1164.all;

entity latch_sr_gated is
	port(
		S, R, Clk: in std_logic;
		Q, Q_n: out std_logic
	);
end latch_sr_gated;

architecture Behavior of latch_sr_gated is
component latch_sr_nand
	port(
		S_n, R_n: in std_logic;
		Q_a, Q_b: out std_logic
	);
end component;
signal S_n, R_n: std_logic;
begin
	S_n <= S nand Clk;
	R_n <= R nand Clk;
	
	latch: latch_sr_nand port map(
		S_n	=>	S_n,
		R_n	=>	R_n,
		Q_a	=>	Q,
		Q_b	=>	Q_n
	);
end Behavior;