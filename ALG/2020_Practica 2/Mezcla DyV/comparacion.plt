set title "Comparacion FuerzaBruta y DyV"
set key top left vertical inside
set grid
set xlabel "Cantidad de Vectores (k)"
set ylabel "Tiempo(sec)"
plot "nano.dat" using 1:2 with lp, "nanob.dat" using 1:2 with lp
#CUBO(x) = a*x*x*x + b*x*x + c*x + d
#fit CUBO(x) "floyd.dat" using 1:2 via a,b,c,d
#plot "floyd.dat" using 1:2 title "floyd" , CUBO(x)
set terminal pdf
set output "Comparacion.pdf"
replot
pause 5 "Pulsa enter para continuar..."