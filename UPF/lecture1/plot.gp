# Set titles and labels
set title "Trajectory Plot"
set xlabel "X-axis (Column 3)"
set ylabel "Y-axis (Column 4)"
# Plot trajectory from column 3 vs column 4
plot "output" using 3:4 with lines title "Trajectory"

