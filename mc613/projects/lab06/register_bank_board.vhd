library ieee;
use ieee.std_logic_1164.all;

entity register_bank_board is
  port (
    KEY: in std_logic_vector(3 downto 0);
    SW: in std_logic_vector(9 downto 0);
    HEX0: out std_logic_vector(6 downto 0)
  );
end register_bank_board;

architecture structural of register_bank_board is
component register_bank
	port (
		clk : in std_logic;
		data_in : in std_logic_vector(3 downto 0);
		data_out : out std_logic_vector(3 downto 0);
		reg_rd : in std_logic_vector(2 downto 0);
		reg_wr : in std_logic_vector(2 downto 0);
		we : in std_logic;
		clear : in std_logic
	);
end component;

component bin2hex
    port (
        SW: in std_logic_vector(3 downto 0); 
        HEX0: out std_logic_vector(6 downto 0)
    );  
end component;

signal output: std_logic_vector(3 downto 0);

begin
	
	charmander: register_bank port map(
		clk	=>	KEY(0),
		clear	=>	KEY(1),
		we		=>	KEY(2),
		data_in	=>	SW(3 downto 0),
		reg_wr	=>	SW(6 downto 4),
		reg_rd	=>	SW(9 downto 7),
		data_out	=>	output
	);
	
	display: bin2hex port map(
		SW		=> output,
		HEX0	=> HEX0
	);
	
end structural;
