#
# Rodrigo Seiji P. Hirao
# RA186837
#

# Variables

105 0000000DAC  # x = 3500
106 0000000009  # CONT = 9

# Constants

205 000000000A  # g = 10
206 0000000001  # i = 1

# Code

000 LOAD MQ,M(205)      # MQ = g

000 MUL M(105)          # MQ = y = gx
001 LOAD MQ             # AC = MQ
001 STOR M(305)         # y

002 RSH                 # AC = k = y/2
002 STOR M(306)         # k

003 LOAD M(106)         # AC = CONT
003 SUB M(206)          # AC = CONT - i
004 STOR M(106)         # CONT

004 LOAD M(305)         # AC = y
005 DIV M(306)          # MQ = AC/k
005 LOAD MQ             # AC = MQ
005 ADD M(306)          # AC = AC + k
006 RSH                 # AC = k = AC/2
006 STOR M(306)         # k
007 LOAD M(106)         # AC = CONT

007 JUMP+M(003,20:39)   # do while CONT >= 0

008 LOAD M(306)         # AC = k
008 JUMP M(400,00:19)   # end

