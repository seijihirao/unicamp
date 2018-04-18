library ieee;
use ieee.std_logic_1164.all;

package latches_ffs_pack is
	component latch_sr_nand
		port(
			S_n, R_n: in std_logic;
			Q_a, Q_b: out std_logic
		);
	end component;
	component latch_sr_gated
		port(
			S, R, Clk: in std_logic;
			Q, Q_n: out std_logic
		);
	end component;
	component latch_d_gated
		port(
			D, Clk: in std_logic;
			Q, Q_n: out std_logic
		);
	end component;
	component ff_d
		port(
			D, Clk, Preset, Clear: in std_logic;
			Q, Q_n: out std_logic
		);
	end component;
	component ff_jk
		port(
			J, K, Clk, Preset, Clear: in std_logic;
			Q, Q_n: out std_logic
		);
	end component;
	component ff_t
		port(
			T, Clk, Preset, Clear: in std_logic;
			Q, Q_n: out std_logic
		);
	end component;
end latches_ffs_pack;