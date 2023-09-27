#!/bin/csh -vx
@ i = 100
while ( $i <= 725)
./floyd1.o $i >> floyd1.dat
@ i += 25
end
