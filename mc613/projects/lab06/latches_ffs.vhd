-- brief : lab06 - question 1

library ieee;
use ieee.std_logic_1164.all;
use work.latches_ffs_pack.all;

entity latches_ffs is
  port (
    clock :   in  std_logic;
    preset :  in  std_logic;
    clear :   in  std_logic;
    A :       in  std_logic;
    B :       in  std_logic;
    Q :       out std_logic_vector(1 to 6)
  );
end latches_ffs;

architecture structural of latches_ffs is
begin

  lff1: latch_sr_nand port map (
    S_n => NOT(A),
    R_n => NOT(B),
    Q_a  => Q(6), -- << CHANGE HERE
    Q_b  => open
  );
  
  lff2: latch_sr_gated port map (
    S   => A,
    R   => B,
    Clk => clock,
    Q   => Q(4), -- << CHANGE HERE
    Q_n => open
  );
  
  lff3: latch_d_gated port map (
    D   => A,
    Clk => clock,
    Q   => Q(1), -- << CHANGE HERE
    Q_n => open
  );
  
  lff4: ff_d port map (
    D      => A,
    Clk    => clock,
    Q      => Q(3), -- << CHANGE HERE
    Q_n    => open,
    Preset => preset,
    Clear  => clear
  );
  
  lff5: ff_jk port map (
    J      => A,
    K      => B,
    Clk    => clock,
    Q      => Q(5), -- << CHANGE HERE
    Q_n    => open,
    Preset => preset,
    Clear  => clear
  );
  
  lff6: ff_t port map (
    T      => A,
    Clk    => clock,
    Q      => Q(2), -- << CHANGE HERE
    Q_n    => open,
    Preset => preset,
    Clear  => clear
  );

end structural;
