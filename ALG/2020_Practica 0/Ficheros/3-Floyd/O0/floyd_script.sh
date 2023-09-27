#!/bin/csh -vx
@ i = 100
while ( $i <= 725)
./floyd.o $i >> floyd.dat
@ i += 25
end
