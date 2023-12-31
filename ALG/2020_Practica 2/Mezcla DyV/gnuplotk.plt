set title "Mezcla K vectores"
set key top left vertical inside
set grid
set xlabel "numero vectores(k)"
set ylabel "Tiempo(sec)"
plot "mezcla_kvariante_numerosgrandes.dat" using 1:2 with lp
Nlogn(x) = a*x*log(x)+b
fit Nlogn(x) "mezcla_n50_k100_2000.dat" using 1:2 via a, b
plot "mezcla_kvariante_numerosgrandes.dat" using 1:2 title "Mezcla K vectores" , Nlogn(x)
set terminal pdf
set output "Mezcla_K.pdf"
replot
pause 5 "Pulsa enter para continuar..."