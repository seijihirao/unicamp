library ieee;
use ieee.std_logic_1164.all;

entity xbar_v1 is
  port(x1, x2, s: in std_logic;
       y1, y2: out std_logic);
end xbar_v1;

architecture rtl of xbar_v1 is
begin
	
	with s select y1 <= 
		x2 when '1' ,
		x1 when '0' ;
		
	with s select y2 <= 
		x1 when '1' ,
		x2 when '0' ;
		
end rtl;

