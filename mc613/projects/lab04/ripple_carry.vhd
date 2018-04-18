library ieee;
use ieee.std_logic_1164.all;

entity ripple_carry is
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
end ripple_carry;

architecture rtl of ripple_carry is
component full_adder
	port (
    x, y : in std_logic;
    r : out std_logic;
    cin : in std_logic;
    cout : out std_logic
  );
end component;
signal c: std_logic_vector(0 to N);
signal s: std_logic_vector(N-1 downto 0);
begin
	c(0) <= cin;
	ripple:
		for i in 0 to N-1 generate
			add: full_adder port map (
				x		=>	x(i),
				y		=>	y(i),
				r		=> s(i),
				cin	=> c(i),
				cout	=> c(i+1)
			);
		end generate;
		cout <= c(N);
		overflow <= (x(N-1) and y(N-1) and not s(N-1)) or (not x(N-1) and not y(N-1) and s(N-1));
		r <= s;
end rtl;
