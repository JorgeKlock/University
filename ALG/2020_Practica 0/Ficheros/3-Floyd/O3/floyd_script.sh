#!/bin/csh -vx
@ i = 100
while ( $i <= 725)
./floyd3.o $i >> floyd3.dat
@ i += 25
end
