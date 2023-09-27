set title "Tiempo medio de hanoi"
set key top left vertical inside
set grid
set xlabel "Talla(n)"
set ylabel "Tiempo(sec)"
plot "hanoi.dat" using 1:2 
EXPOH(x) = a*(2**x)+b
fit EXPOH(x) "hanoi.dat" using 1:2 via a,b
plot "hanoi.dat" using 1:2 title "hanoi" , EXPOH(x)
set terminal pdf
set output "hanoi.pdf"
replot
pause 5 "Pulsa enter para continuar..."
