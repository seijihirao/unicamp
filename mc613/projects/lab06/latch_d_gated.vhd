library ieee;
use ieee.std_logic_1164.all;

entity latch_d_gated is
	port(
		D, Clk: in std_logic;
		Q, Q_n: out std_logic
	);
end latch_d_gated;

architecture Behavior of latch_d_gated is
component latch_sr_gated
	port(
		S, R, Clk: in std_logic;
		Q, Q_n: out std_logic
	);
end component;
begin
	latch: latch_sr_gated port map(
		S		=>	D,
		R		=>	not(D),
		Clk	=>	Clk,
		Q		=>	Q,
		Q_n	=>	Q_n
	);
end Behavior;