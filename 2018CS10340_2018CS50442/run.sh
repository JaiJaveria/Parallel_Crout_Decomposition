N=$1
INP_FILE=$2
NUM_THREADS=$3
STRATEGY=$4

if [ $STRATEGY == 4 ]
then
	# mpiexec -n $NUM_THREADS ./crout_4 $N $INP_FILE
	echo "NOT IMPLEMENTED"
else
	./crout $N $INP_FILE $NUM_THREADS $STRATEGY
fi
