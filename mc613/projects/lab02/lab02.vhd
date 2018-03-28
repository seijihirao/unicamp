LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY work IS 
	PORT (
		A, B, C, D, E	: IN	STD_LOGIC	;
		resultado		: OUT	STD_LOGIC
		)	;
END work ;

ARCHITECTURE LogicFunction OF work IS
SIGNAL input : STD_LOGIC_VECTOR(4 DOWNTO 0) ;
BEGIN
	input <= A&B&C&D&E ;
	WITH input SELECT
		resultado <= 	'1' WHEN "00000",
							'1' WHEN "00010",
							'1' WHEN "00101",
							'1' WHEN "01000",
							'1' WHEN "01101",
							'1' WHEN "01111",
							'1' WHEN "10010",
							'1' WHEN "10101",
							'1' WHEN "11000",
							'1' WHEN "11101",
							'1' WHEN "11111",
							'0' WHEN OTHERS
							;
END LogicFunction ;