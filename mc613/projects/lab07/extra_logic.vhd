library ieee;
use ieee.std_logic_1164.all;

entity extra_logic is
  port(w3, w2, w1, w0 : in std_logic;
       y3, y2, y1, y0 : in std_logic;
       f : out std_logic);
end extra_logic;

architecture rtl of extra_logic is
begin
  f <= (w3 and y3) or (w2 and y2) or (w1 and y1) or (w0 and y0) ;
end rtl;

