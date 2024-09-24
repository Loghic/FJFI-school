# Set titles and labels
set title "Trajectory Plot"
set xlabel "X-axis (Column 3)"
set ylabel "Y-axis (Column 4)"
# Plot trajectory from column 3 vs column 4
plot "output" using 3:4 with lines title "Trajectory"

# Add a pause to view the first plot, and then press enter to move to the next one
pause -1

# Set titles and labels for height over time
set title "Height vs Time"
set xlabel "Time (Column 2)"
set ylabel "Height (Column 4)"
# Plot height (column 4) vs time (column 2)
plot "output" using 2:4 with lines title "Height over Time"
