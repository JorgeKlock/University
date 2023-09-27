#!/bin/csh -vx
@ i = 10000
while ( $i < 250000)
./mergesort2.o $i >> mergesort_GRANDE_2.dat
@ i += 10000
end
