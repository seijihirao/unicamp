library ieee;
use ieee.std_logic_1164.all;

entity ff_t is
	port(
		T, Clk, Preset, Clear: in std_logic;
		Q, Q_n: out std_logic
	);
end ff_t;

architecture Behavior of ff_t is
component ff_jk
	port(
		J, K, Clk, Preset, Clear: in std_logic;
		Q, Q_n: out std_logic
	);
end component;
begin
	ff: ff_jk port map(
		J		=>	T,
		K		=>	T,
		Clk	=>	Clk,
		Preset=>	Preset,
		Clear	=>	Clear,
		Q		=>	Q,
		Q_n	=>	Q_n
	);
end Behavior;