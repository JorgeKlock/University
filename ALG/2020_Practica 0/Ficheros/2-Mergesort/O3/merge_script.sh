#!/bin/csh -vx
@ i = 10000
while ( $i < 250000)
./mergesort3.o $i >> mergesort_GRANDE_3.dat
@ i += 10000
end
