library ieee;
use ieee.std_logic_1164.all;

entity mux16_to_1 is
  port(data : in std_logic_vector(15 downto 0);
       sel : in std_logic_vector(3 downto 0);
       output : out std_logic);
end mux16_to_1;

architecture rtl of mux16_to_1 is
component mux4_to_1 
	port(d3, d2, d1, d0 : in std_logic;
       sel : in std_logic_vector(1 downto 0);
       output : out std_logic);
end component ;
signal m: std_logic_vector (3 downto 0) ;

begin
	mux0: mux4_to_1 port map (
		d0 => data(0),
		d1 => data(1),
		d2 => data(2),
		d3 => data(3),
		sel(0) => sel(0),
		sel(1) => sel(1),
		output => m(0)
	) ;
		mux1: mux4_to_1 port map (
		d0 => data(4),
		d1 => data(5),
		d2 => data(6),
		d3 => data(7),
		sel(0) => sel(0),
		sel(1) => sel(1),
		output => m(1)
	) ; 
		mux2: mux4_to_1 port map (
		d0 => data(8),
		d1 => data(9),
		d2 => data(10),
		d3 => data(11),
		sel(0) => sel(0),
		sel(1) => sel(1),
		output => m(2)
	) ;
		mux3: mux4_to_1 port map (
		d0 => data(12),
		d1 => data(13),
		d2 => data(14),
		d3 => data(15),
		sel(0) => sel(0),
		sel(1) => sel(1),
		output => m(3)
	) ;
	muxf: mux4_to_1 port map (
		sel(0) => sel(2),
		sel(1) => sel(3),
		d0 => m(0),
		d1 => m(1),
		d2 => m(2),
		d3 => m(3),
		output => output
	) ;
end rtl;

