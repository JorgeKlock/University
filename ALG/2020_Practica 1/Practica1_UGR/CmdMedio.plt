set title "Tiempo medio de floyd"
set key top left vertical inside
set grid
set xlabel "Talla(n)"
set ylabel "Tiempo(sec)"
plot "floyd.dat" using 1:2 
CUBO(x) = a*x*x*x + b*x*x + c*x + d
fit CUBO(x) "floyd.dat" using 1:2 via a,b,c,d
plot "floyd.dat" using 1:2 title "floyd" , CUBO(x)
set terminal pdf
set output "floyd.pdf"
replot
pause 5 "Pulsa enter para continuar..."
