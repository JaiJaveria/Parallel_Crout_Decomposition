strategy 1:
  we used the pragma omp parallel for to parallelize the 2 internal loops inside the big j loop.
  we removed any possibilty of data race by making variable sum,i,k private.
strategy 2:
  in this we distribute the 2 internal loops to 2 sections and also break each loop into 2 chunks. Thus we created 4 sections in total.
  we did not increase the number of sections and preferred to hard code it since it was leading to great increase in the code base and also to the errors that we were facing. Thus we did a tradeoff and settled for 4 sections. For number of threads different that 4, openmp internally handles them.
  when trying to run the 2 loops in parallel, a new data race is created since the first loop tries to update L[j][j] when the other loops reads it. To remove this we started the loop from i=j+1 rather than j and computed the i=j iteration before the sections pragma.
strategy 3:
  in this we divide the 2 internal loops to two sections and then use the parallel for pragma. we used strategies used in 1,2 to remove data races from our code.
strategy 4:
  strategy-1
    in this we divide the iterations of the loop in a round robin fashion. for the ith iteration, we give it to the process that has its rank such that i%(num of processes)=rank i.e. iteration 1 goes to process 1, 2 to process 2....
    after computing the necesarry matrix value, we broadcast it to all the processes.
  strategy-2
    In some case as the number of processes increased, the above strategy was taking a lot of time. Especially with 16 processes, the strategy did not stop for quite a lot of time(i was running it on 8 core machine)
    So we tried another strategy, where we do not broadcast updates cell by cell. Instead we scatter the L, U array, do the computation in each process and gather it again.
    This strategy fineshed faster on p=16 case. But for all other cases it was taking more time than strategy1.
    The possible increase in time for p=16 case might be due to the less nuber of cores available in our executions. Thus we have stuck to the first strategy in the submission. The bash files compile and run the strategy1 which is in crout_4. We have included strategy2 just to show our exploration while coming up with an implementation. Strategy2 is in crout_4_strat2.c file.
