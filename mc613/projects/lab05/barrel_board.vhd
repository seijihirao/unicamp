library ieee;
use ieee.std_logic_1164.all;

entity barrel_board is
  port (
    SW : in std_logic_vector(5 downto 0);
    LEDR : out std_logic_vector(3 downto 0)
  );
end barrel_board;

architecture behavioral of barrel_board is
	component barrel_shifter
		port(
			w : in  std_logic_vector (3 downto 0);
			s : in  std_logic_vector (1 downto 0);
			y : out std_logic_vector (3 downto 0)
		);
	end component;

	begin
		mapea: barrel_shifter port map(
			s(1) => SW(5),
			s(0) => SW(4),
			w(3) => SW(3),
			w(2) => SW(2),
			w(1) => SW(1),
			w(0) => SW(0),
			y(3) => LEDR(3),
			y(2) => LEDR(2),
			y(1) => LEDR(1),
			y(0) => LEDR(0)
		);

end behavioral;