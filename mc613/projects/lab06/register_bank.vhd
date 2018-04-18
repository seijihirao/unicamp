library ieee;
use ieee.std_logic_1164.all;

entity register_bank is
  port (
    clk : in std_logic;
    data_in : in std_logic_vector(3 downto 0);
    data_out : out std_logic_vector(3 downto 0);
    reg_rd : in std_logic_vector(2 downto 0);
    reg_wr : in std_logic_vector(2 downto 0);
    we : in std_logic;
    clear : in std_logic
  );
end register_bank;

architecture structural of register_bank is

component reg
	generic (
    N : integer := 4
  );
  port (
    clk : in std_logic;
    data_in : in std_logic_vector(N-1 downto 0);
    data_out : out std_logic_vector(N-1 downto 0);
    load : in std_logic; -- Write enable
    clear : in std_logic
  );
end component;
 
component zbuffer
	generic (n : integer := 4) ;
	port(
		enable: in std_logic;
		input: in std_logic_vector(n-1 downto 0);
		output: out std_logic_vector(n-1 downto 0)
	);
end component;

component dec3_to_8
	port(
		enable: in std_logic;
		input: in std_logic_vector(2 downto 0);
		output: out std_logic_vector(7 downto 0)
	);
end component;

type Matrix is array ( 7 downto 0 ) of std_logic_vector( 3 downto 0);

signal d2r, r2d: std_logic_vector(7 downto 0);
signal joao: Matrix;
begin
	
	dec_d2r: dec3_to_8 port map(
		enable => we,
		input  => reg_wr,
		output => d2r
	);
	
	dec_r2d: dec3_to_8 port map(
		enable => we,
		input  => reg_rd,
		output => r2d
	);
	
	proc:
		for i in 0 to 7 generate
			regs: reg port map(
				clk => clk,
				data_in => data_in,
				data_out => joao(i),
				clear => clear,
				load => d2r(i)
			);
			buff: zbuffer port map(
				enable => r2d(i),
				input => joao(i),
				output => data_out
			);
		end generate;
	
end structural;
