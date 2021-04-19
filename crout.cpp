int num_threads=1;
void crout_0(double const **A, double **L, double **U, int n) {
    int i, j, k;
    double sum = 0;
    for (i = 0; i < n; i++) {
        U[i][i] = 1;
    }
    for (j = 0; j < n; j++) {
        for (i = j; i < n; i++) {
            sum = 0;
            for (k = 0; k < j; k++) {
                sum = sum + L[i][k] * U[k][j];
            }
            L[i][j] = A[i][j] - sum;
        }
        for (i = j; i < n; i++) {
            sum = 0;
            for(k = 0; k < j; k++) {
                sum = sum + L[j][k] * U[k][i];
            }
            if (L[j][j] == 0) {
                exit(0);
            }
            U[j][i] = (A[j][i] - sum) / L[j][j];
        }
    }
}
void crout_1(double const **A, double **L, double **U, int n) {
    int i, j, k;
    double sum = 0;
    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        U[i][i] = 1;
    }
    for (j = 0; j < n; j++) {
        #pragma omp parallel for
        for (i = j; i < n; i++) {
            sum = 0;
            for (k = 0; k < j; k++) {
                sum = sum + L[i][k] * U[k][j];
            }
            L[i][j] = A[i][j] - sum;
        }

        #pragma omp parallel for
        for (i = j; i < n; i++) {
            sum = 0;
            for(k = 0; k < j; k++) {
                sum = sum + L[j][k] * U[k][i];
            }
            if (L[j][j] == 0) {
                exit(0);
            }
            U[j][i] = (A[j][i] - sum) / L[j][j];
        }
    }
}
void crout_2(double const **A, double **L, double **U, int n) {
    int i, j, k;
    double sum = 0;
    //sequential
    // for (i = 0; i < n; i++) {
    //     U[i][i] = 1;
    // }
    switch(num_threads){
      case 1:
      {
      	#pragma omp parallel sections
       	{
      		#pragma omp section
      		{
      			for (int i=0*(n)/1; i<1*(n)/1; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      	}
      	break;
      }
      case 2:
      {
      	#pragma omp parallel sections
       	{
      		#pragma omp section
      		{
      			for (int i=0*(n)/2; i<1*(n)/2; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=1*(n)/2; i<2*(n)/2; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      	}
      	break;
      }
      case 4:
      {
      	#pragma omp parallel sections
       	{
      		#pragma omp section
      		{
      			for (int i=0*(n)/4; i<1*(n)/4; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=1*(n)/4; i<2*(n)/4; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=2*(n)/4; i<3*(n)/4; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=3*(n)/4; i<4*(n)/4; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      	}
      	break;
      }
      case 8:
      {
      	#pragma omp parallel sections
       	{
      		#pragma omp section
      		{
      			for (int i=0*(n)/8; i<1*(n)/8; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=1*(n)/8; i<2*(n)/8; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=2*(n)/8; i<3*(n)/8; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=3*(n)/8; i<4*(n)/8; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=4*(n)/8; i<5*(n)/8; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=5*(n)/8; i<6*(n)/8; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=6*(n)/8; i<7*(n)/8; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=7*(n)/8; i<8*(n)/8; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      	}
      	break;
      }
      case 16:
      {
      	#pragma omp parallel sections
       	{
      		#pragma omp section
      		{
      			for (int i=0*(n)/16; i<1*(n)/16; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=1*(n)/16; i<2*(n)/16; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=2*(n)/16; i<3*(n)/16; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=3*(n)/16; i<4*(n)/16; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=4*(n)/16; i<5*(n)/16; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=5*(n)/16; i<6*(n)/16; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=6*(n)/16; i<7*(n)/16; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=7*(n)/16; i<8*(n)/16; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=8*(n)/16; i<9*(n)/16; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=9*(n)/16; i<10*(n)/16; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=10*(n)/16; i<11*(n)/16; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=11*(n)/16; i<12*(n)/16; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=12*(n)/16; i<13*(n)/16; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=13*(n)/16; i<14*(n)/16; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=14*(n)/16; i<15*(n)/16; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      		#pragma omp section
      		{
      			for (int i=15*(n)/16; i<16*(n)/16; i++)
      			 {
       				 U[i][i] = 1;
       			 }
      		}
      	}
      	break;
      }
      }


    for (j = 0; j < n; j++) {
        //sequential
        // for (i = j; i < n; i++) {
        //     sum = 0;
        //     for (k = 0; k < j; k++) {
        //         sum = sum + L[i][k] * U[k][j];
        //     }
        //     L[i][j] = A[i][j] - sum;
        // }
        switch(num_threads)
        {
          case 1:
          {
          	#pragma omp parallel sections
           	{
          		#pragma omp section
          		{
          			for (int i=j+0*(n-j)/1; i<j+1*(n-j)/1; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          	}
          	break;
          }
          case 2:
          {
          	#pragma omp parallel sections
           	{
          		#pragma omp section
          		{
          			for (int i=j+0*(n-j)/2; i<j+1*(n-j)/2; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+1*(n-j)/2; i<j+2*(n-j)/2; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          	}
          	break;
          }
          case 4:
          {
          	#pragma omp parallel sections
           	{
          		#pragma omp section
          		{
          			for (int i=j+0*(n-j)/4; i<j+1*(n-j)/4; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+1*(n-j)/4; i<j+2*(n-j)/4; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+2*(n-j)/4; i<j+3*(n-j)/4; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+3*(n-j)/4; i<j+4*(n-j)/4; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          	}
          	break;
          }
          case 8:
          {
          	#pragma omp parallel sections
           	{
          		#pragma omp section
          		{
          			for (int i=j+0*(n-j)/8; i<j+1*(n-j)/8; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+1*(n-j)/8; i<j+2*(n-j)/8; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+2*(n-j)/8; i<j+3*(n-j)/8; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+3*(n-j)/8; i<j+4*(n-j)/8; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+4*(n-j)/8; i<j+5*(n-j)/8; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+5*(n-j)/8; i<j+6*(n-j)/8; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+6*(n-j)/8; i<j+7*(n-j)/8; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+7*(n-j)/8; i<j+8*(n-j)/8; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          	}
          	break;
          }
          case 16:
          {
          	#pragma omp parallel sections
           	{
          		#pragma omp section
          		{
          			for (int i=j+0*(n-j)/16; i<j+1*(n-j)/16; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+1*(n-j)/16; i<j+2*(n-j)/16; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+2*(n-j)/16; i<j+3*(n-j)/16; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+3*(n-j)/16; i<j+4*(n-j)/16; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+4*(n-j)/16; i<j+5*(n-j)/16; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+5*(n-j)/16; i<j+6*(n-j)/16; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+6*(n-j)/16; i<j+7*(n-j)/16; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+7*(n-j)/16; i<j+8*(n-j)/16; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+8*(n-j)/16; i<j+9*(n-j)/16; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+9*(n-j)/16; i<j+10*(n-j)/16; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+10*(n-j)/16; i<j+11*(n-j)/16; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+11*(n-j)/16; i<j+12*(n-j)/16; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+12*(n-j)/16; i<j+13*(n-j)/16; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+13*(n-j)/16; i<j+14*(n-j)/16; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+14*(n-j)/16; i<j+15*(n-j)/16; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          		#pragma omp section
          		{
          			for (int i=j+15*(n-j)/16; i<j+16*(n-j)/16; i++)
          			{
              				sum = 0;
              				for (k = 0; k < j; k++) {
            				   sum = sum + L[i][k] * U[k][j];
           				   }
           				   L[i][j] = A[i][j] - sum;
          			}
          		}
          	}
          	break;
          }
        }


        for (i = j; i < n; i++) {
            sum = 0;
            for(k = 0; k < j; k++) {
                sum = sum + L[j][k] * U[k][i];
            }
            if (L[j][j] == 0) {
                exit(0);
            }
            U[j][i] = (A[j][i] - sum) / L[j][j];
        }
    }
}
