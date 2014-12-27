set terminal png
set output 'aufg3.png'

set xlabel 'N'
set ylabel 'Integral'
set title 'Monte-Carlo-Integration'
set logscale x
unset key

set arrow from 1,1 to 1e7,1 nohead
plot 'aufg3.txt' u 1:2:3 with errorbars
