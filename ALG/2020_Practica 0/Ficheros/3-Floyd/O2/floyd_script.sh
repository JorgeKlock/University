#!/bin/csh -vx
@ i = 100
while ( $i <= 725)
./floyd2.o $i >> floyd2.dat
@ i += 25
end
