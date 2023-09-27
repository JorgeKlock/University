#!/bin/csh -vx
@ i = 10000
while ( $i < 250000)
./mergesort1.o $i >> mergesort_GRANDE.dat
@ i += 10000
end
