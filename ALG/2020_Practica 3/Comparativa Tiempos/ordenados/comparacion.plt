set title "Comparacion Vecino/Insercion/Propio"
set key top left vertical inside
set grid
set xlabel "Fichero de Datos (nombre)"
set ylabel "Tiempo(sec)"
plot "vecino.dat" using 2:xticlabels(1) with lp, "insercion.dat" using 2:xticlabels(1) with lp, "propio.dat" using 2:xticlabels(1) with lp
set terminal pdf
set output "Comparacion.pdf"
replot
pause 5 "Pulsa enter para continuar..."