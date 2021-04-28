int i, j, k;
double sum = 0;
for (i = 0; i < n; i++) {
    U[i][i] = 1;
}
for (j = 0; j < n; j++) {

  //i=j iteration here
  for (k = 0; k < j; k++)
  {
   sum = sum + L[j][k] * U[k][j];
  }
   L[j][j] = A[j][j] - sum;
   //--i=j end
   int inc=(n-j)/8;
  #pragma omp parallel sections
 {
   #pragma omp section
   {
     for ( int i=j+1; i<j+1*inc; i++)
     {
           double sum = 0;
           for (int k = 0; k < j; k++) {
            sum = sum + L[i][k] * U[k][j];
          }
          L[i][j] = A[i][j] - sum;
     }
   }
   #pragma omp section
   {
     for ( int i=j+1*inc; i<j+2*inc; i++)
     {
           double sum = 0;
           for (int k = 0; k < j; k++) {
            sum = sum + L[i][k] * U[k][j];
          }
          L[i][j] = A[i][j] - sum;
     }
   }
   #pragma omp section
   {
     for ( int i=j+2*inc; i<j+3*inc; i++)
     {
           double sum = 0;
           for (int k = 0; k < j; k++) {
            sum = sum + L[i][k] * U[k][j];
          }
          L[i][j] = A[i][j] - sum;
     }
   }
   #pragma omp section
   {
     for ( int i=j+3*inc; i<j+4*inc; i++)
     {
           double sum = 0;
           for (int k = 0; k < j; k++) {
            sum = sum + L[i][k] * U[k][j];
          }
          L[i][j] = A[i][j] - sum;
     }
   }
   #pragma omp section
   {
     for ( int i=j+4*inc; i<j+5*inc; i++)
     {
           double sum = 0;
           for (int k = 0; k < j; k++) {
            sum = sum + L[i][k] * U[k][j];
          }
          L[i][j] = A[i][j] - sum;
     }
   }
   #pragma omp section
   {
     for ( int i=j+5*inc; i<j+6*inc; i++)
     {
           double sum = 0;
           for (int k = 0; k < j; k++) {
            sum = sum + L[i][k] * U[k][j];
          }
          L[i][j] = A[i][j] - sum;
     }
   }
   #pragma omp section
   {
     for ( int i=j+6*inc; i<j+7*inc; i++)
     {
           double sum = 0;
           for (int k = 0; k < j; k++) {
            sum = sum + L[i][k] * U[k][j];
          }
          L[i][j] = A[i][j] - sum;
     }
   }
   #pragma omp section
   {
     for ( int i=j+7*inc; i<n; i++)
     {
           double sum = 0;
           for (int k = 0; k < j; k++) {
            sum = sum + L[i][k] * U[k][j];
          }
          L[i][j] = A[i][j] - sum;
     }
   }
   #pragma omp section
   {
     for ( int i=j+0*inc; i<j+1*inc; i++)
     {
       double sum = 0;
       for(int k = 0; k < j; k++) {
       sum = sum + L[j][k] * U[k][i];
       }
       if (L[j][j] == 0) {
        exit(0);
       }
       U[j][i] = (A[j][i] - sum) / L[j][j];
     }
   }
   #pragma omp section
   {
     for ( int i=j+1*inc; i<j+2*inc; i++)
     {
       double sum = 0;
       for(int k = 0; k < j; k++) {
       sum = sum + L[j][k] * U[k][i];
       }
       if (L[j][j] == 0) {
        exit(0);
       }
       U[j][i] = (A[j][i] - sum) / L[j][j];
     }
   }
   #pragma omp section
   {
     for ( int i=j+2*inc; i<j+3*inc; i++)
     {
       double sum = 0;
       for(int k = 0; k < j; k++) {
       sum = sum + L[j][k] * U[k][i];
       }
       if (L[j][j] == 0) {
        exit(0);
       }
       U[j][i] = (A[j][i] - sum) / L[j][j];
     }
   }
   #pragma omp section
   {
     for ( int i=j+3*inc; i<j+4*inc; i++)
     {
       double sum = 0;
       for(int k = 0; k < j; k++) {
       sum = sum + L[j][k] * U[k][i];
       }
       if (L[j][j] == 0) {
        exit(0);
       }
       U[j][i] = (A[j][i] - sum) / L[j][j];
     }
   }
   #pragma omp section
   {
     for ( int i=j+4*inc; i<j+5*inc; i++)
     {
       double sum = 0;
       for(int k = 0; k < j; k++) {
       sum = sum + L[j][k] * U[k][i];
       }
       if (L[j][j] == 0) {
        exit(0);
       }
       U[j][i] = (A[j][i] - sum) / L[j][j];
     }
   }
   #pragma omp section
   {
     for ( int i=j+5*inc; i<j+6*inc; i++)
     {
       double sum = 0;
       for(int k = 0; k < j; k++) {
       sum = sum + L[j][k] * U[k][i];
       }
       if (L[j][j] == 0) {
        exit(0);
       }
       U[j][i] = (A[j][i] - sum) / L[j][j];
     }
   }
   #pragma omp section
   {
     for ( int i=j+6*inc; i<j+7*inc; i++)
     {
       double sum = 0;
       for(int k = 0; k < j; k++) {
       sum = sum + L[j][k] * U[k][i];
       }
       if (L[j][j] == 0) {
        exit(0);
       }
       U[j][i] = (A[j][i] - sum) / L[j][j];
     }
   }
   #pragma omp section
   {
     for ( int i=j+7*inc; i<n; i++)
     {
       double sum = 0;
       for(int k = 0; k < j; k++) {
       sum = sum + L[j][k] * U[k][i];
       }
       if (L[j][j] == 0) {
        exit(0);
       }
       U[j][i] = (A[j][i] - sum) / L[j][j];
     }
   }



 }
}
