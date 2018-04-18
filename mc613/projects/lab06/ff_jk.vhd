library ieee;
use ieee.std_logic_1164.all;

entity ff_jk is
	port(
		J, K, Clk, Preset, Clear: in std_logic;
		Q, Q_n: out std_logic
	);
end ff_jk;

architecture Behavior of ff_jk is
component ff_d
	port(
		D, Clk, Preset, Clear: in std_logic;
		Q, Q_n: out std_logic
	);
end component;
signal Q_m: std_logic;
signal Q_s: std_logic := '0';
signal Q_s_n: std_logic := '1';
begin
	ff: ff_d port map(
		D		=>	(J and Q_s_n) or(not(K) and Q_s),
		Clk	=>	Clk,
		Preset=>	Preset,
		Clear	=>	Clear,
		Q		=>	Q_s,
		Q_n	=>	Q_s_n
	);
	Q <= Q_s;
	Q_n <= Q_s_n;
end Behavior;