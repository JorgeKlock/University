set title "TSP backtracking"
set key top left vertical inside
set grid
set xlabel "ciudades(n)"
set ylabel "tiempo(s)"
plot "ul16_back.txt" using 2:3 with lines
set terminal pdf
set output "U16_Back.pdf"
replot
pause 5 "Pulsa enter para continuar..."