library ieee;
use ieee.std_logic_1164.all;

entity dec2_to_4 is
  port(en, w1, w0: in std_logic;
       y3, y2, y1, y0: out std_logic);
end dec2_to_4;

architecture rtl of dec2_to_4 is
signal input : std_logic_vector(2 downto 0) ;
begin
  input <= en&w1&w0 ;
  y0 <= '1' when input = "100" else '0' ;
  y1 <= '1' when input = "101" else '0' ;
  y2 <= '1' when input = "110" else '0' ;
  y3 <= '1' when input = "111" else '0' ;
end rtl;

