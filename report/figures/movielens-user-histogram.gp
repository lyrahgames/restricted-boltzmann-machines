set size 1.2, 1.0
set logscale x

unset key

set xl 'ratings'
set yl 'users'

plot 'movielens-user-histogram.txt' with boxes lc black fs solid 0.2 title ''