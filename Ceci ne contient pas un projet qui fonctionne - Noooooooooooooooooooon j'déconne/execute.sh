# -i 10000 		=> 10000 iterations
# -e 012345 	=> Launch successively the versions 0,1,2,3,4 and 5
# -s 012345 	=> For each version, set the matrix factor size to 0,2 and 4
# -t 13 		=> For each size, set the thread factor to 1 and 3
# -m 			=> Display the CPU time  

./bin/project -i 10000 -e 012345 -s 024 -t 13 -m
