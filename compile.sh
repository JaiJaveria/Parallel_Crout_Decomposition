gcc -g -O0 -fopenmp -o crout crout.c
mpicc -g -o crout4 crout_4.c
export OMP_NESTED=TRUE
