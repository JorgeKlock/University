set title "Comparacion static/dynamic/guided"
set key top left vertical inside
set grid
set xlabel "Numero de chunks"
set ylabel "Tiempo(sec)"
plot "static.dat" using 2:xticlabels(1) with lp, "dynamic.dat" using 2:xticlabels(1) with lp, "guided.dat" using 2:xticlabels(1) with lp
set terminal pdf
set output "Comparacion.pdf"
replot
pause 5 "Pulsa enter para continuar..."