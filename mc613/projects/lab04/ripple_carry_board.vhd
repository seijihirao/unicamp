library ieee;
use ieee.std_logic_1164.all;

entity ripple_carry_board is
  port (
    SW : in std_logic_vector(7 downto 0);
    HEX4 : out std_logic_vector(6 downto 0);
    HEX2 : out std_logic_vector(6 downto 0);
    HEX0 : out std_logic_vector(6 downto 0);
    LEDR : out std_logic_vector(0 downto 0)
    );
end ripple_carry_board;

architecture rtl of ripple_carry_board is
component ripple_carry
	generic (
		N : integer := 4
	);
	port (
    x,y : in std_logic_vector(N-1 downto 0);
    r : out std_logic_vector(N-1 downto 0);
    cin : in std_logic;
    cout : out std_logic;
    overflow : out std_logic
  );
end component;

component bin2hex
	port (
        SW: in std_logic_vector(3 downto 0); 
        HEX0: out std_logic_vector(6 downto 0)
    );
end component;

signal result: std_logic_vector(3 downto 0);
begin
	
	-- Display inputs
	hexX: bin2hex port map (
		SW(0)		=>	SW(0),
		SW(1)		=>	SW(1),
		SW(2)		=>	SW(2),
		SW(3)		=>	SW(3),
		HEX0		=>	HEX4
	);
	hexY: bin2hex port map (
		SW(0)		=>	SW(4),
		SW(1)		=>	SW(5),
		SW(2)		=>	SW(6),
		SW(3)		=>	SW(7),
		HEX0		=>	HEX2
	);
	
	-- Sum with ripple carry
	sum: ripple_carry port map (
		x(0)		=>	SW(0),
		x(1)		=>	SW(1),
		x(2)		=>	SW(2),
		x(3)		=>	SW(3),
		y(0)		=>	SW(4),
		y(1)		=>	SW(5),
		y(2)		=>	SW(6),
		y(3)		=>	SW(7),
		r			=>	result,
		cin		=>	'0',
		overflow	=> LEDR(0)
	);
	hexR: bin2hex port map (
		SW(0)		=>	result(0),
		SW(1)		=>	result(1),
		SW(2)		=>	result(2),
		SW(3)		=>	result(3),
		HEX0		=>	HEX0
	);
end rtl;
