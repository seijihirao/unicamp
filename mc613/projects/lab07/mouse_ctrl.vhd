-------------------------------------------------------------------------------
-- Title      : MC613
-- Project    : Mouse Controller
-- Details    : www.ic.unicamp.br/~corte/mc613/
--							www.computer-engineering.org/ps2protocol/
-------------------------------------------------------------------------------
-- File       : mouse_ctrl.vhd
-- Author     : Thiago Borges Abdnur
-- Company    : IC - UNICAMP
-- Last update: 2010/04/12
-------------------------------------------------------------------------------
-- Description: 
-- PS2 mouse basic I/O control
-------------------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all;

entity mouse_ctrl is
	generic(
		-- This is the system clock value in kHz. Should be at least 1MHz.
		--  Recommended value is 24000 kHz (CLOCK_24 (DE1 pins: PIN_A12 and 
		--  PIN_B12))
		clkfreq : integer	
	);
	port(
		ps2_data	:	inout	std_logic;	-- PS2 data pin
		ps2_clk		:	inout	std_logic;	-- PS2 clock pin
		clk				:	in	std_logic;		-- system clock (same frequency as defined in 
																	--  'clkfreq' generic)
		en				:	in	std_logic;		-- Enable
		resetn		:	in	std_logic;		-- Reset when '0'
		newdata		:	out	std_logic;		-- Rises when a new data package has arrived
																	--  from the mouse
		-- Mouse buttons state ('1' when pressed):
		--	bt_on(0): Left mouse button
		--	bt_on(1): Right mouse button
		--	bt_on(2): Middle mouse button (if it exists)
		bt_on			:	out	std_logic_vector(2 downto 0);		
		
		-- Signals that an overflow occured on this package in one of the 
		--	coordinates
		ox, oy		:	out std_logic;		
		
		-- New position relative to the last package. Nine bit values in two's
		--  complement for each coordinate.
		dx, dy		:	out	std_logic_vector(8 downto 0);
		
		-- Wheel movement relative to last package. 4 bit value in two's
		--  complement. Wheel up is a negative value, down is positive.
		wheel			: out	std_logic_vector(3 downto 0)
	);
end;

architecture rtl of mouse_ctrl is
	component ps2_iobase
		generic(
			clkfreq : integer	-- This is the system clock value in kHz
		);
		port(
			ps2_data	:	inout	std_logic;
			ps2_clk		:	inout	std_logic;
			clk				:	in	std_logic;
			en				:	in	std_logic;
			resetn		:	in	std_logic;
			idata_rdy	:	in	std_logic;
			idata			:	in	std_logic_vector(7 downto 0);
			send_rdy	:	out	std_logic;
			odata_rdy	:	out	std_logic;
			odata			:	out	std_logic_vector(7 downto 0)
		);
	end component;
		
	signal sigsend, sigsendrdy, signewdata,
				 sigreseting, xn, yn, sigwheel : std_logic;
	signal hdata, ddata : std_logic_vector(7 downto 0);
begin
	ps2io : ps2_iobase generic map(clkfreq) port map(
		ps2_data, ps2_clk, clk, en, resetn, sigsend, hdata,
		sigsendrdy, signewdata, ddata
	);
	
	-- Send Reset to mouse
	process(clk, en, resetn)
		type rststatename is (
			SETCMD, SEND, WAITACK, NEXTCMD, CLEAR
		);
	
		constant ncmd : integer := 11; -- Total number of commands to send
		type commands is array (0 to ncmd - 1) of integer;
		constant cmd : commands := (
			16#FF#, 16#F5#, -- Reset and disable reporting
			16#F3#, 200, 16#F3#, 100, 16#F3#, 80, 16#F2#, -- Wheel enabling
			16#F6#, 16#F4# -- Restore defaults and enable reporting
		);
		
		variable state : rststatename;
		variable count : integer range 0 to ncmd := 0;		
	begin
		if(rising_edge(clk)) then
			hdata <= X"00";			
			sigsend <= '0';
			sigreseting <= '1';
			
			case state is
				when SETCMD =>
					hdata <= std_logic_vector(to_unsigned(cmd(count), 8));
					if sigsendrdy = '1' then
						state := SEND;
					else
						state := SETCMD;
					end if;
					
				when SEND =>
					hdata <= std_logic_vector(to_unsigned(cmd(count), 8));
					sigsend <= '1';
					state := WAITACK;
					
				when WAITACK =>
					if signewdata = '1' then
						-- Wheel detection
						if cmd(count) = 16#F2# then
							-- If device ID is 0x00, it has no wheel				
							if ddata = X"00" then							
								sigwheel <= '0';
								state := NEXTCMD;
							-- If device ID is 0x03, it has a wheel							
							elsif ddata = X"03" then							
								sigwheel <= '1';
								state := NEXTCMD;
							end if;
						else	
							state := NEXTCMD;
						end if;
					end if;
					
				when NEXTCMD =>
					count := count + 1;
					if count = ncmd then
						state := CLEAR;
					else
						state := SETCMD;
					end if;	
			
				when CLEAR =>
					sigreseting <= '0';
					count := 0;					
			end case;
		end if;
		if resetn = '0' or en = '0' then
			state := SETCMD;
			count := 0;
			sigwheel <= '0';
		end if;
	end process;

	-- Get update packages
	process(signewdata, sigreseting, en, resetn)
		variable count : integer range 0 to 4;
	begin
		if(rising_edge(signewdata) and sigreseting = '0' 
		 and en = '1') then
			newdata <= '0';
			
			case count is
				when 0 =>
					bt_on <= ddata(2 downto 0);
					xn <= ddata(4);
					yn <= ddata(5);
					ox <= ddata(6);
					oy <= ddata(7);
					
				when 1 =>
					dx <= xn & ddata;
														
				when 2 =>
					dy <= yn & ddata;
					
				when 3 =>
					wheel <= ddata(3 downto 0);
				
				when others => 
					NULL;
			end case;
			count := count + 1;
			if (sigwheel = '0' and count > 2) or count > 3 then
				count := 0;
				newdata <= '1';
			end if;
		end if;
		if resetn = '0' or en = '0' then
			bt_on <= (others => '0');
			dx <= (others => '0');
			dy <= (others => '0');
			wheel <= (others => '0');
			xn <= '0';
			yn <= '0';
			ox <= '0';
			oy <= '0';
			count := 0;
			newdata <= '0';
		end if;
	end process;
end rtl;