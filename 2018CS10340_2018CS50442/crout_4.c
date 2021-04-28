#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>
void write_output(char fname[], double** arr, int n )
{
    FILE *f = fopen(fname, "w");
    for( int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            fprintf(f, "%0.12f ", arr[i][j]);
            // printf("%0.12f ", arr[i][j]);
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

  size_t n=atoi(argv[1]);

  double (*A)[n]=malloc(sizeof *A *n);
  double (*L)[n]=malloc(sizeof *L *n);
  double (*U)[n]=malloc(sizeof *U *n);
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
  //open the file
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
  MPI_Bcast(A,n*n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      L[i][j]=0;
      U[i][j]=0;
    }
  }

    int i, j, k;
    double sum = 0;
    for (i = 0; i < n; i++) {
        U[i][i] = 1;
    }

    for (j = 0; j < n; j++)
    {
      if (world_rank==0)
      {
        // i=j iteration
        sum = 0;
        for (k = 0; k < j; k++) {
            sum = sum + L[j][k] * U[k][j];
        }
        L[j][j] = A[j][j] - sum;
      }
      MPI_Bcast(L,n*n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
      MPI_Bcast(U,n*n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
      MPI_Scatter(L,n*n/world_size,MPI_DOUBLE,calc_mat_L,n*n/world_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
      MPI_Scatter(U,n*n/world_size,MPI_DOUBLE,calc_mat_U,n*n/world_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
      for (i = j+1; i < n; i++)
      {
          sum = 0;
          for (k = 0; k < j; k++) {
              sum = sum + L[i][k] * U[k][j];
          }
          L[i][j] = A[i][j] - sum;
          // printf(" L %d %d %lf\n",i,j,L[i][j] );
      }
      for (i = j; i < n; i++)
      {
          sum = 0;
          for(k = 0; k < j; k++) {
              sum = sum + L[j][k] * U[k][i];
          }
          if (L[j][j] == 0) {
              exit(0);
              // return;
          }
          U[j][i] = (A[j][i] - sum) / L[j][j];
          // printf(" U %d %d %lf\n",i,j,U[i][j] );
      }
      MPI_Gather(calc_mat_L,n*n/world_size,MPI_DOUBLE,L,n*n/world_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
      MPI_Gather(calc_mat_U,n*n/world_size,MPI_DOUBLE,U,n*n/world_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
      }

  MPI_Finalize();
  // char * outL=malloc(sizeof(char)*17+1);//"output_L_"+argv[4]+"_"+argv[3]+".txt";
  // char * outU=malloc(sizeof(char)*17+1);//"output_U_"+argv[4]+"_"+argv[3]+".txt";
  // strcpy(outL,"output_L_");
  // strcpy(outU,"output_U_");
  // outL[9]='\0';
  // outU[9]='\0';
  // strcat(outL,argv[4]);
  // strcat(outU,argv[4]);
  // // outL[10]='\0';
  // // outU[10]='\0';
  // strcat(outL,"_");
  // strcat(outU,"_");
  // // outL[11]='\0';
  // // outU[11]='\0';
  // strcat(outL,argv[3]);
  // strcat(outU,argv[3]);
  // // if (num_threads==16) {
  // //   outL[13]='\0';
  // //   outU[13]='\0';
  // // }
  // // else
  // // {
  // //   outL[12]='\0';
  // //   outU[12]='\0';
  // // }
  // strcat(outL,".txt");
  // strcat(outU,".txt");
  // // printf("L:\n" );
  // write_output(outL, L, n );
  // // printf("U:\n" );
  // write_output(outU, U, n );
  // // for (size_t i = 0; i < n; i++) {
  // //   for (size_t j = 0; j < n; j++) {
  // //     printf("%lf ",L[i][j]);
  // //   }
  // //   printf("\n" );
  // // }
  // // printf("\n" );
  // // printf("\n" );
  // // for (size_t i = 0; i < n; i++) {
  // //   for (size_t j = 0; j < n; j++) {
  // //     printf("%lf ",U[i][j]);
  // //   }
  // //   printf("\n" );
  // // }
  // // printf("295\n" );
  //
  // free(outL);
  // free(outU);
  // for (size_t i = 0; i < n; i++) {
  //   free(A[i]);
  //   free(L[i]);
  //   free(U[i]);
  // }
  // free(A);
  // free(L);
  // free(U);
  // return 0;
}
