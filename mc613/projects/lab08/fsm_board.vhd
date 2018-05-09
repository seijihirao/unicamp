library ieee;
use ieee.std_logic_1164.all;

entity fsm_board is
  port (
    SW   : in  std_logic_vector(9 downto 0);
    KEY  : in  std_logic_vector(3 downto 1);
    LEDR : out std_logic_vector(9 downto 0)
  );
end fsm_board;

architecture structural of fsm_board is

  component fsm_table is
    port (
      clock : in  std_logic;
      reset : in  std_logic;
      w     : in  std_logic;
      z     : out std_logic
    );
  end component;
  
  component fsm_diag is
    port (
      clock : in  std_logic;
      reset : in  std_logic;
      w     : in  std_logic;
      z     : out std_logic
    );
  end component;
  
  component fsm_seq is
    port (
      clock : in  std_logic;
      reset : in  std_logic;
      w     : in  std_logic;
      z     : out std_logic
    );
  end component;

begin

  table : fsm_table port map (
    clock => KEY(3),
    reset => SW(9),
    w     => SW(8),
    z     => LEDR(8)
  );

  diag : fsm_diag port map (
    clock => KEY(2),
    reset => SW(5),
    w     => SW(4),
    z     => LEDR(4)
  );

  seq : fsm_seq port map (
    clock => KEY(1),
    reset => SW(1),
    w     => SW(0),
    z     => LEDR(0)
  );

  LEDR(9) <= '0';
  LEDR(7 downto 5) <= (others => '0');
  LEDR(3 downto 1) <= (others => '0');

end structural;
