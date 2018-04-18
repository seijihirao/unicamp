library ieee;
use ieee.std_logic_1164.all;

entity shift_board2 is 
	generic (N : integer := 6);
	port (
		SW   : in std_logic_vector(9 downto 0);
		KEY  : in std_logic_vector(0 downto 0);
		LEDR : out std_logic_vector(N-1 downto 0) 
	);
end shift_board2;

architecture behavioral of shift_board2 is
	component shift_register
		port (
			 clk     : in  std_logic;
			 mode    : in  std_logic_vector(1 downto 0);
			 ser_in  : in  std_logic;
			 par_in  : in  std_logic_vector((N - 1) downto 0);
			 par_out : out std_logic_vector((N - 1) downto 0)
		  );
	 end component;

	 begin
		mapa: shift_register port map (
			par_out => LEDR,
			mode(0) => SW(7),
			mode(1) => SW(8),
			ser_in => SW(6),
			par_in(0) => SW(0),
			par_in(1) => SW(1),
			par_in(2) => SW(2),
			par_in(3) => SW(3),
			par_in(4) => SW(4),
			par_in(5) => SW(5),
			clk => SW(9)
		);
end behavioral;	