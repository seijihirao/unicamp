library ieee;
use ieee.std_logic_1164.all;

entity alu is
  port (
    a, b : in std_logic_vector(3 downto 0);
    F : out std_logic_vector(3 downto 0);
    s0, s1 : in std_logic;
    Z, C, V, N : out std_logic
  );
end alu;

architecture behavioral of alu is
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

signal b_base_1: std_logic_vector(3 downto 0);
signal cin: std_logic;
signal overflow: std_logic;
signal carryout: std_logic;
signal negative: std_logic;
signal zero: std_logic;
signal sum_result: std_logic_vector(3 downto 0);
signal result: std_logic_vector(3 downto 0);
signal s: std_logic_vector(0 to 1);
begin
	s <= s0 & s1;
	
	b_base_1 <= NOT b when s0 = '1' else b;
	cin <= '1' when s0 = '1' else '0';
	
	sum: ripple_carry port map (
		x			=> a,
		y			=> b_base_1,
		r			=>	sum_result,
		cin		=>	cin,
		overflow	=> overflow, 
		cout		=> carryout
	);
	
	with s select result <=
		a and b when "01",
		a or b when "11",
		sum_result when others;
	
	Z <= '1' when result = (result'range => '0') else '0'; -- pesquisar F'range ~Sushi
	N <= '1' when result(3) = '1' else '0';
	V <= '0' when s1 = '1' else overflow;
	C <= '0' when s1 = '1' else carryout;
	
	F <= result;
	
end behavioral;
