#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>
void write_output(char fname[], double** arr, int n )
{
    FILE *f = fopen(fname, "w");

    for( int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
          // printf("%0.12f ", arr[i][j]);
            fprintf(f, "%0.12f ", arr[i][j]);
        }
        fprintf(f, "\n");
        // printf("\n");
    }
    fclose(f);
}
int main(int argc, char const *argv[]) {
  MPI_Init(NULL, NULL);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  // printf("24 rank %d\n",world_rank );

  size_t n=atoi(argv[1]);

  double (*A)[n]=malloc(sizeof *A *n);
  double (*L)[n]=malloc(sizeof *L *n);
  double (*UT)[n]=malloc(sizeof *U *n);//u transpose
  // printf("30 rank %d\n",world_rank );
  // double **A=(double **)malloc(sizeof(double*)*n);
  // for (size_t i = 0; i < n; i++) {
  //   A[i]=(double*)malloc(sizeof(double)*n);
  // }
  // double **L=(double **)malloc(sizeof(double*)*n);
  // for (size_t i = 0; i < n; i++) {
  //   L[i]=(double*)malloc(sizeof(double)*n);
  // }
  // double **U=(double **)malloc(sizeof(double*)*n);
  // for (size_t i = 0; i < n; i++) {
  //   U[i]=(double*)malloc(sizeof(double)*n);
  // }
  // printf("42 rank %d\n",world_rank );
  if (world_rank==0)
  {
    const char* filename=argv[2];
    FILE* fileA=fopen(filename,"r");
    if (fileA==NULL) {
      printf("Error opening the input file for matrix A. exiting\n" );
      exit(-1);
    }
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n; j++) {
        fscanf(fileA,"%lf",&A[i][j]);
        // L[i][j]=0;
        // U[i][j]=0;
      }
    }
    /* code */
  }
  // printf("59 rank %d\n",world_rank );
  MPI_Bcast(A,n*n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      L[i][j]=0;
      UT[i][j]=0;
    }
  }

    int i, j, k;
    double sum = 0;
    for (i = 0; i < n; i++) {
        UT[i][i] = 1;
    }
    int num_rows=n/world_size;
    double (*calc_mat_L)[n]=malloc(sizeof *calc_mat_L *num_rows)
    double (*calc_mat_U)[n]=malloc(sizeof *calc_mat_U *num_rows)
    int realIndex;
    for (j = 0; j < n; j++)
    {
      if (world_rank==0)
      {
        // i=j iteration
        sum = 0;
        for (k = 0; k < j; k++) {
          // sum = sum + L[j][k] * U[k][j];
            sum = sum + L[j][k] * UT[j][k];
        }
        L[j][j] = A[j][j] - sum;
      }
      // MPI_Bcast(&(L[j][j]),n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
      // MPI_Barrier(MPI_COMM_WORLD);
      // printf("90 rank %d\n",world_rank );
      MPI_Bcast(L[j],n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
      MPI_Bcast(UT[j],n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
      MPI_Scatter(L,n*num_rows,MPI_DOUBLE,calc_mat_L,n*num_rows, MPI_DOUBLE, 0, MPI_COMM_WORLD);
      MPI_Scatter(U,n*num_rows,MPI_DOUBLE,calc_mat_U,n*num_rows, MPI_DOUBLE, 0, MPI_COMM_WORLD);
      for (i =0; i < num_rows; i++)
      // for (i = j+1; i < n; i++)
      {
        realIndex=i+num_rows*world_rank;
        if (realIndex>j && realIndex<n )
        {
          /* code */
          sum = 0;
          for (k = 0; k < j; k++) {
            // sum = sum + L[i][k] * U[k][j];
            // sum = sum + L[i][k] * UT[j][k];
              sum = sum + calc_mat_L[i][k] * UT[j][k];
          }
          calc_mat_L[i][j] = A[realIndex][j] - sum;
          // MPI_Bcast(&L[i][j],1, MPI_DOUBLE, world_rank, MPI_COMM_WORLD);
        }
          // MPI_Bcast(&L[i][j],1, MPI_DOUBLE, i%world_size, MPI_COMM_WORLD);
        // else
        // {
        //   MPI_Bcast(&L[i][j],1, MPI_DOUBLE, i%world_size, MPI_COMM_WORLD);
        //
        // }
          // printf(" L %d %d %lf\n",i,j,L[i][j] );
      }
      for (i = 0; i < num_rows; i++)
      // for (i = j; i < n; i++)
      {
        realIndex=i+num_rows*world_rank;
        if (realIndex>=j && realIndex<n )
        {
          sum = 0;
          for(k = 0; k < j; k++) {
            // sum = sum + L[j][k] * U[k][i];
              sum = sum + L[j][k] * UT[realIndex][k];
          }
          if (L[j][j] == 0) {
              exit(0);
              // return;
          }
          calc_mat_U[i][j] = (A[j][realIndex] - sum) / L[j][j];
          // UT[i][j] = (A[j][i] - sum) / L[j][j];
          // U[j][i] = (A[j][i] - sum) / L[j][j];
          // MPI_Bcast(&U[i][j],1, MPI_DOUBLE, world_rank, MPI_COMM_WORLD);

          // printf(" U %d %d %lf\n",i,j,U[i][j] );
        }
        // MPI_Bcast(&U[j][i],1, MPI_DOUBLE, i%world_size, MPI_COMM_WORLD);
        // else
        // {
        //   MPI_Bcast(&U[i][j],1, MPI_DOUBLE, i%world_size, MPI_COMM_WORLD);
        //
        // }
      }

      MPI_Gather(calc_mat_L,n*num_rows,MPI_DOUBLE,L,n*num_rows, MPI_DOUBLE, world_rank, MPI_COMM_WORLD);
      MPI_Gather(calc_mat_U,n*num_rows,MPI_DOUBLE,U,n*num_rows, MPI_DOUBLE, world_rank, MPI_COMM_WORLD);
      // MPI_Barrier(MPI_COMM_WORLD);
      // fflush(stdout);
      // printf("128 rank %d\n",world_rank );

      }
      // printf("131 rank %d\n",world_rank );
      MPI_Barrier(MPI_COMM_WORLD);

      if (world_rank==0)
      {
        // printf("127\n");
        char * outL=malloc(sizeof(char)*17+1);//"output_L_"+argv[4]+"_"+argv[3]+".txt";
        char * outU=malloc(sizeof(char)*17+1);//"output_U_"+argv[4]+"_"+argv[3]+".txt";
        // printf("152\n" );
        strcpy(outL,"output_L_");
        strcpy(outU,"output_U_");
        outL[9]='\0';
        outU[9]='\0';
        strcat(outL,argv[4]);
        strcat(outU,argv[4]);
        // outL[10]='\0';
        // outU[10]='\0';
        strcat(outL,"_");
        strcat(outU,"_");
        // outL[11]='\0';
        // outU[11]='\0';
        strcat(outL,argv[3]);
        strcat(outU,argv[3]);
        // if (num_threads==16) {
        //   outL[13]='\0';
        //   outU[13]='\0';
        // }
        // else
        // {
        //   outL[12]='\0';
        //   outU[12]='\0';
        // }
        strcat(outL,".txt");
        strcat(outU,".txt");
        // printf("L:\n" );
        // printf("174\n" );
        write_output(outL, L, n );
        // printf("U:\n" );
        write_output(outU, U, n );
        // printf("180\n" );
        // for (size_t i = 0; i < n; i++) {
        //   for (size_t j = 0; j < n; j++) {
        //     printf("%lf ",L[i][j]);
        //   }
        //   printf("\n" );
        // }
        // printf("\n" );
        // printf("\n" );
        // for (size_t i = 0; i < n; i++) {
        //   for (size_t j = 0; j < n; j++) {
        //     printf("%lf ",U[i][j]);
        //   }
        //   printf("\n" );
        // }
        // printf("295\n" );

        free(outL);
        free(outU);
      }

  for (size_t i = 0; i < n; i++) {
    // free(A[i]);
    free(L[i]);
    free(U[i]);
  }
  free(A);
  free(L);
  free(U);
  // return 0;
  MPI_Finalize();

}
