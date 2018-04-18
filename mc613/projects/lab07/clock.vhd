library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity clock is
  port (
    clk : in std_logic;
    decimal : in std_logic_vector(3 downto 0);
    unity : in std_logic_vector(3 downto 0);
    set_hour : in std_logic;
    set_minute : in std_logic;
    set_second : in std_logic;
    hour_dec, hour_un : out std_logic_vector(6 downto 0);
    min_dec, min_un : out std_logic_vector(6 downto 0);
    sec_dec, sec_un : out std_logic_vector(6 downto 0)
  );
end clock;

architecture rtl of clock is
	component clk_div is
		port (
			clk : in std_logic;
			clk_hz : out std_logic
		);
	end component;
	signal clk_hz : std_logic;
  
	component bin2dec is
		port (
			SW: in std_logic_vector(3 downto 0);
			HEX0: out std_logic_vector(6 downto 0)
		);
	end component;
	
	signal hour_dec_b, hour_un_b : std_logic_vector(3 downto 0) := "0000";
   signal min_dec_b, min_un_b : std_logic_vector(3 downto 0) := "0000";
   signal sec_dec_b, sec_un_b : std_logic_vector(3 downto 0) := "0000";
	
begin
	clock_divider : clk_div port map (clk, clk_hz);
	
	process(clk, clk_hz)
	begin
		if (clk'event and clk = '1') then
		
			-- Clock Counter
			if (clk_hz = '1') then
				-- Count seconds
				sec_un_b <= sec_un_b + 1;
				
				if(sec_un_b = "1001") then
					sec_dec_b <= sec_dec_b + 1;
					sec_un_b <= "0000";
				end if;
				
				-- Count minutes
				if(sec_dec_b = "0101" and sec_un_b = "1001") then
					min_un_b <= min_un_b + 1;
					sec_dec_b <= "0000";
				end if;
				
				if(min_un_b = "1001") then
					min_dec_b <= min_dec_b + 1;
					min_un_b <= "0000";
				end if;
				
				-- Count hours
				if(min_dec_b = "0101" and min_un_b = "1001") then
					hour_un_b <= hour_un_b + 1;
					min_dec_b <= "0000";
				end if;
				
				if(hour_un_b = "1001") then
					hour_dec_b <= hour_dec_b + 1;
					hour_un_b <= "0000";
				end if;
				
			-- Clock Setter
			else
				-- Hour
				if(set_hour = '1') then
					hour_dec_b <= decimal;
					hour_un_b <= unity;
				end if;
				
				-- Minutes
				if(set_minute = '1') then
					min_dec_b <= decimal;
					min_un_b <= unity;
				end if;
				
				-- Seconds
				if(set_second = '1') then
					sec_dec_b <= decimal;
					sec_un_b <= unity;
				end if;
			end if;
		end if;
	end process;
	
	sec_un_dec: bin2dec port map(
		SW		=>	sec_un_b,
		HEX0	=>	sec_un
	);
	sec_dec_dec: bin2dec port map(
		SW		=>	sec_dec_b,
		HEX0	=>	sec_dec
	);
	min_un_dec: bin2dec port map(
		SW		=>	min_un_b,
		HEX0	=>	min_un
	);
	min_dec_dec: bin2dec port map(
		SW		=>	min_dec_b,
		HEX0	=>	min_dec
	);
	hour_un_dec: bin2dec port map(
		SW		=>	hour_un_b,
		HEX0	=>	hour_un
	);
	hour_dec_dec: bin2dec port map(
		SW		=>	hour_dec_b,
		HEX0	=>	hour_dec
	);
	
end rtl;