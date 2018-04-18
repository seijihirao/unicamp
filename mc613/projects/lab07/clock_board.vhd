library ieee;
use ieee.std_logic_1164.all;

entity clock_board is
  port (
    CLOCK_50 : in std_logic;
    SW : in std_logic_vector(7 downto 0);
    KEY : in std_logic_vector(3 downto 1);
    HEX5, HEX4, HEX3, HEX2, HEX1, HEX0 : out std_logic_vector(6 downto 0)
  );
end clock_board;

architecture rtl of clock_board is
  component clock is
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
  end component;
begin

  clock_inst : clock port map (
    clk => CLOCK_50,
    decimal => SW(7 downto 4),
    unity => SW(3 downto 0),
    set_hour => NOT KEY(3),
    set_minute => NOT KEY(2),
    set_second => NOT KEY(1),
    hour_dec => HEX5,
    hour_un => HEX4,
    min_dec => HEX3,
    min_un => HEX2,
    sec_dec => HEX1,
    sec_un => HEX0
  );

end rtl;