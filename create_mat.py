import numpy as np
import sys

n = int(sys.argv[1])
# file = sys.argv[2]

A = np.random.uniform(-4, 4, (n, n))

# f = open(file, 'w')
for i in A:
    for j in i:
        print ("{0:.12f}".format(j), '', end='')
        # print ("{0:.12f}".format(j), '', end='', file=f)
    # print(file=f)
    print()
# f.close()
