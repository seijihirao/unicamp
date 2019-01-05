LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all;

entity ps2_mouse_test is
	port
	(
		------------------------	Clock Input	 	------------------------
		CLOCK_50	: 	in	STD_LOGIC;											--	50 MHz
		
		------------------------	Push Button		------------------------
		KEY 	:		in	STD_LOGIC_VECTOR (3 downto 0);		--	Pushbutton[3:0]

		------------------------	DPDT Switch		------------------------
		SW 	:		in	STD_LOGIC_VECTOR (9 downto 0);			--	Toggle Switch[9:0]
		
		------------------------	7-SEG Dispaly	------------------------
		HEX0 	:		out	STD_LOGIC_VECTOR (6 downto 0);		--	Seven Segment Digit 0
		HEX1 	:		out	STD_LOGIC_VECTOR (6 downto 0);		--	Seven Segment Digit 1
		HEX2 	:		out	STD_LOGIC_VECTOR (6 downto 0);		--	Seven Segment Digit 2
		HEX3 	:		out	STD_LOGIC_VECTOR (6 downto 0);		--	Seven Segment Digit 3
		
		----------------------------	LED		----------------------------
		LEDR 	:		out	STD_LOGIC_VECTOR (9 downto 0);		--	LED Red[9:0]
					
		------------------------	PS2		--------------------------------
		PS2_DAT 	:		inout	STD_LOGIC;	--	PS2 Data
		PS2_CLK		:		inout	STD_LOGIC		--	PS2 Clock
	);
end;

architecture struct of ps2_mouse_test is
	component bin2hex
		port(
			SW  : in std_logic_vector(3 downto 0);
			HEX0: out std_logic_vector(6 downto 0)
		);
	end component;

	component mouse_ctrl
		generic(
			clkfreq : integer
		);
		port(
			ps2_data	:	inout	std_logic;
			ps2_clk		:	inout	std_logic;
			clk				:	in 	std_logic;
			en				:	in 	std_logic;
			resetn		:	in 	std_logic;
			newdata		:	out	std_logic;
			bt_on			:	out	std_logic_vector(2 downto 0);
			ox, oy		:	out std_logic;
			dx, dy		:	out	std_logic_vector(8 downto 0);
			wheel			: out	std_logic_vector(3 downto 0)
		);
	end component;
	
	signal signewdata, resetn : std_logic;
	signal dx, dy : std_logic_vector(8 downto 0);
	signal x, y 	: std_logic_vector(7 downto 0);
	signal hexdata : std_logic_vector(15 downto 0);
	
	constant SENSIBILITY : integer := 16; -- Rise to decrease sensibility
begin 
	-- KEY(0) Reset
	resetn <= KEY(0);
	
	mousectrl : mouse_ctrl generic map (50000) port map(
		PS2_DAT, PS2_CLK, CLOCK_50, '1', KEY(0),
		signewdata, LEDR(7 downto 5), LEDR(9), LEDR(8), dx, dy, LEDR(3 downto 0)
	);
	
	hexseg0: bin2hex port map(
		hexdata(3 downto 0), HEX0
	);
	hexseg1: bin2hex port map(
		hexdata(7 downto 4), HEX1
	);
	hexseg2: bin2hex port map(
		hexdata(11 downto 8), HEX2
	);
	hexseg3: bin2hex port map(
		hexdata(15 downto 12), HEX3
	);	
	
	-- Read new mouse data	
	process(signewdata, resetn)
		variable xacc, yacc : integer range -10000 to 10000;
	begin
		if(rising_edge(signewdata)) then			
			x <= std_logic_vector(to_signed(to_integer(signed(x)) + ((xacc + to_integer(signed(dx))) / SENSIBILITY), 8));
			y <= std_logic_vector(to_signed(to_integer(signed(y)) + ((yacc + to_integer(signed(dy))) / SENSIBILITY), 8));
			xacc := ((xacc + to_integer(signed(dx))) rem SENSIBILITY);
			yacc := ((yacc + to_integer(signed(dy))) rem SENSIBILITY);					
		end if;
		if resetn = '0' then
			xacc := 0;
			yacc := 0;
			x <= (others => '0');
			y <= (others => '0');
		end if;
	end process;

	hexdata(3  downto  0) <= y(3 downto 0);
	hexdata(7  downto  4) <= y(7 downto 4);
	hexdata(11 downto  8) <= x(3 downto 0);
	hexdata(15 downto 12) <= x(7 downto 4);
end struct;
