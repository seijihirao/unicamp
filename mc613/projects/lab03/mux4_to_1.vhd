library ieee;
use ieee.std_logic_1164.all;

entity mux4_to_1 is
  port(d3, d2, d1, d0 : in std_logic;
       sel : in std_logic_vector(1 downto 0);
       output : out std_logic);
end mux4_to_1;

architecture rtl of mux4_to_1 is
component extra_logic
	port(w3, w2, w1, w0 : in std_logic;
			y3, y2, y1, y0 : in std_logic;
			f : out std_logic);
end component ;
component dec2_to_4
	port(en, w1, w0: in std_logic;
       y3, y2, y1, y0: out std_logic);
end component ;
signal y: std_logic_vector (3 downto 0) ;

begin
	part1: dec2_to_4 port map (
		en => '1',
		w0	=>	sel(0),
		w1	=>	sel(1),
		y0	=> y(0),
		y1	=> y(1),
		y2	=> y(2),
		y3	=> y(3)
	) ;
	part2: extra_logic port map (
		w0 => d0,
		w1 => d1,
		w2 => d2,
		w3 => d3,
		y0	=> y(0),
		y1	=> y(1),
		y2	=> y(2),
		y3	=> y(3),
		f => output
	) ;
		
end rtl;

