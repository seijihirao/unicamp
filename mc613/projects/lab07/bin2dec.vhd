library ieee ;
use ieee.std_logic_1164.all ;

entity bin2dec is
	port (
		SW: in std_logic_vector(3 downto 0);
		HEX0: out std_logic_vector(6 downto 0)
	);
end bin2dec;

architecture LogicFunction of bin2dec IS
begin
		HEX0(0) <= NOT (SW(1) OR SW(3) OR ((NOT SW(2)) AND (NOT SW(0))) OR (SW(2) AND SW(0)) ) ;
		HEX0(1) <= NOT ((NOT SW(3) AND NOT SW(2)) OR (NOT SW(2) AND NOT SW(1)) OR (NOT SW(3) AND NOT SW(1) AND NOT SW(0)) OR (NOT SW(3) AND SW(1) AND SW(0)) ) ;
		HEX0(2) <= NOT ((NOT SW(2) AND NOT SW(1)) OR (NOT SW(3) AND SW(0)) OR (NOT SW(3) AND SW(2)) ) ;
		HEX0(3) <= NOT (SW(3) OR (NOT SW(2) AND NOT SW(0)) OR (NOT SW(2) AND SW(1)) OR (SW(1) AND NOT SW(0)) OR (SW(2) AND NOT SW(1) AND SW(0)) ) ;
		HEX0(4) <= NOT ((NOT SW(2) AND NOT SW(0)) OR (SW(1) AND NOT SW(0)) OR (SW(3) AND SW(1)) OR (SW(3) AND SW(2)) ) ;
		HEX0(5) <= NOT (SW(3) OR (NOT SW(1) AND NOT SW(0)) OR (SW(2) AND NOT SW(1)) OR (SW(2) AND NOT SW(0)) ) ;
		HEX0(6) <= NOT (SW(3) OR (NOT SW(2) AND SW(1)) OR (SW(1) AND NOT SW(0)) OR (SW(2) AND NOT SW(1)) ) ;
		
end LogicFunction ;