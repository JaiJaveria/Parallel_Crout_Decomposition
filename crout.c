#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int num_threads=1;
void write_output(char fname[], double** arr, int n )
{
    FILE *f = fopen(fname, "w");
    for( int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            fprintf(f, "%0.12f ", arr[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

void crout_0(double **A, double **L, double **U, int n) {
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
                // exit(0);
                return;
            }
            U[j][i] = (A[j][i] - sum) / L[j][j];
        }
    }
}
void crout_1(double **A, double **L, double **U, int n) {
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
                // exit(0);
                return;
            }
            U[j][i] = (A[j][i] - sum) / L[j][j];
        }
    }
}
//only sections
void crout_2(double **A, double **L, double **U, int n) {
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
    			for ( i=0*(n)/1; i<1*(n)/1; i++)
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
    			for ( i=0*(n)/2; i<1*(n)/2; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=1*(n)/2; i<2*(n)/2; i++)
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
    			for ( i=0*(n)/4; i<1*(n)/4; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=1*(n)/4; i<2*(n)/4; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=2*(n)/4; i<3*(n)/4; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=3*(n)/4; i<4*(n)/4; i++)
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
    			for ( i=0*(n)/8; i<1*(n)/8; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=1*(n)/8; i<2*(n)/8; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=2*(n)/8; i<3*(n)/8; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=3*(n)/8; i<4*(n)/8; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=4*(n)/8; i<5*(n)/8; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=5*(n)/8; i<6*(n)/8; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=6*(n)/8; i<7*(n)/8; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=7*(n)/8; i<8*(n)/8; i++)
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
    			for ( i=0*(n)/16; i<1*(n)/16; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=1*(n)/16; i<2*(n)/16; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=2*(n)/16; i<3*(n)/16; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=3*(n)/16; i<4*(n)/16; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=4*(n)/16; i<5*(n)/16; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=5*(n)/16; i<6*(n)/16; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=6*(n)/16; i<7*(n)/16; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=7*(n)/16; i<8*(n)/16; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=8*(n)/16; i<9*(n)/16; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=9*(n)/16; i<10*(n)/16; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=10*(n)/16; i<11*(n)/16; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=11*(n)/16; i<12*(n)/16; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=12*(n)/16; i<13*(n)/16; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=13*(n)/16; i<14*(n)/16; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=14*(n)/16; i<15*(n)/16; i++)
    			 {
     				 U[i][i] = 1;
     			 }
    		}
    		#pragma omp section
    		{
    			for ( i=15*(n)/16; i<16*(n)/16; i++)
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
        switch(num_threads){
        case 1:
        {
        	#pragma omp parallel sections
         	{
        		#pragma omp section
        		{
        			for ( i=j+0*(n-j)/1; i<j+1*(n-j)/1; i++)
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
        			for ( i=j+0*(n-j)/2; i<j+1*(n-j)/2; i++)
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
        			for ( i=j+1*(n-j)/2; i<j+2*(n-j)/2; i++)
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
        			for ( i=j+0*(n-j)/4; i<j+1*(n-j)/4; i++)
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
        			for ( i=j+1*(n-j)/4; i<j+2*(n-j)/4; i++)
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
        			for ( i=j+2*(n-j)/4; i<j+3*(n-j)/4; i++)
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
        			for ( i=j+3*(n-j)/4; i<j+4*(n-j)/4; i++)
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
        			for ( i=j+0*(n-j)/8; i<j+1*(n-j)/8; i++)
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
        			for ( i=j+1*(n-j)/8; i<j+2*(n-j)/8; i++)
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
        			for ( i=j+2*(n-j)/8; i<j+3*(n-j)/8; i++)
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
        			for ( i=j+3*(n-j)/8; i<j+4*(n-j)/8; i++)
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
        			for ( i=j+4*(n-j)/8; i<j+5*(n-j)/8; i++)
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
        			for ( i=j+5*(n-j)/8; i<j+6*(n-j)/8; i++)
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
        			for ( i=j+6*(n-j)/8; i<j+7*(n-j)/8; i++)
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
        			for ( i=j+7*(n-j)/8; i<j+8*(n-j)/8; i++)
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
        			for ( i=j+0*(n-j)/16; i<j+1*(n-j)/16; i++)
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
        			for ( i=j+1*(n-j)/16; i<j+2*(n-j)/16; i++)
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
        			for ( i=j+2*(n-j)/16; i<j+3*(n-j)/16; i++)
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
        			for ( i=j+3*(n-j)/16; i<j+4*(n-j)/16; i++)
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
        			for ( i=j+4*(n-j)/16; i<j+5*(n-j)/16; i++)
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
        			for ( i=j+5*(n-j)/16; i<j+6*(n-j)/16; i++)
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
        			for ( i=j+6*(n-j)/16; i<j+7*(n-j)/16; i++)
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
        			for ( i=j+7*(n-j)/16; i<j+8*(n-j)/16; i++)
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
        			for ( i=j+8*(n-j)/16; i<j+9*(n-j)/16; i++)
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
        			for ( i=j+9*(n-j)/16; i<j+10*(n-j)/16; i++)
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
        			for ( i=j+10*(n-j)/16; i<j+11*(n-j)/16; i++)
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
        			for ( i=j+11*(n-j)/16; i<j+12*(n-j)/16; i++)
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
        			for ( i=j+12*(n-j)/16; i<j+13*(n-j)/16; i++)
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
        			for ( i=j+13*(n-j)/16; i<j+14*(n-j)/16; i++)
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
        			for ( i=j+14*(n-j)/16; i<j+15*(n-j)/16; i++)
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
        			for ( i=j+15*(n-j)/16; i<j+16*(n-j)/16; i++)
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

        //sequential
        // for (i = j; i < n; i++)
        // {
        //     sum = 0;
        //     for(k = 0; k < j; k++) {
        //         sum = sum + L[j][k] * U[k][i];
        //     }
        //     if (L[j][j] == 0) {
        //         // exit(0);
        //         return;
        //     }
        //     U[j][i] = (A[j][i] - sum) / L[j][j];
        // }
        switch(num_threads){
        case 1:
        {
        	#pragma omp parallel sections
         	{
        		#pragma omp section
        		{
        			for ( i=j+0*(n-j)/1; i<j+1*(n-j)/1; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
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
        			for ( i=j+0*(n-j)/2; i<j+1*(n-j)/2; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+1*(n-j)/2; i<j+2*(n-j)/2; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
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
        			for ( i=j+0*(n-j)/4; i<j+1*(n-j)/4; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+1*(n-j)/4; i<j+2*(n-j)/4; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+2*(n-j)/4; i<j+3*(n-j)/4; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+3*(n-j)/4; i<j+4*(n-j)/4; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
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
        			for ( i=j+0*(n-j)/8; i<j+1*(n-j)/8; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+1*(n-j)/8; i<j+2*(n-j)/8; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+2*(n-j)/8; i<j+3*(n-j)/8; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+3*(n-j)/8; i<j+4*(n-j)/8; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+4*(n-j)/8; i<j+5*(n-j)/8; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+5*(n-j)/8; i<j+6*(n-j)/8; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+6*(n-j)/8; i<j+7*(n-j)/8; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+7*(n-j)/8; i<j+8*(n-j)/8; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
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
        			for ( i=j+0*(n-j)/16; i<j+1*(n-j)/16; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+1*(n-j)/16; i<j+2*(n-j)/16; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+2*(n-j)/16; i<j+3*(n-j)/16; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+3*(n-j)/16; i<j+4*(n-j)/16; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+4*(n-j)/16; i<j+5*(n-j)/16; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+5*(n-j)/16; i<j+6*(n-j)/16; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+6*(n-j)/16; i<j+7*(n-j)/16; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+7*(n-j)/16; i<j+8*(n-j)/16; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+8*(n-j)/16; i<j+9*(n-j)/16; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+9*(n-j)/16; i<j+10*(n-j)/16; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+10*(n-j)/16; i<j+11*(n-j)/16; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+11*(n-j)/16; i<j+12*(n-j)/16; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+12*(n-j)/16; i<j+13*(n-j)/16; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+13*(n-j)/16; i<j+14*(n-j)/16; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+14*(n-j)/16; i<j+15*(n-j)/16; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        		#pragma omp section
        		{
        			for ( i=j+15*(n-j)/16; i<j+16*(n-j)/16; i++)
        			{
         				sum = 0;
        				for(k = 0; k < j; k++) {
        				sum = sum + L[j][k] * U[k][i];
        				}
        				if (L[j][j] == 0) {
        				// exit(0);
        				return;
        				}
        				U[j][i] = (A[j][i] - sum) / L[j][j];
        			}
        		}
        	}
        	break;
        }
        }
    }
}
void crout_3(double **A, double **L, double **U, int n) {
    int i, j, k;
    double sum = 0;
    for (i = 0; i < n; i++) {
        U[i][i] = 1;
    }
    for (j = 0; j < n; j++) {
      //i=j case
      sum = 0;
      for (k = 0; k < j; k++) {
          sum = sum + L[j][k] * U[k][j];
      }
      L[j][j] = A[j][j] - sum;
      if (num_threads==1)
      {
        for (i = j+1; i < n; i++) {
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
                // exit(0);
                return;
            }
            U[j][i] = (A[j][i] - sum) / L[j][j];
        }
      }
      else
      {
        #pragma omp parallel sections
        {
          #pragma omp section
          {
            #pragma omp parallel for schedule(static)
            for (i = j+1; i < n; i++) {
                sum = 0;
                for (k = 0; k < j; k++) {
                    sum = sum + L[i][k] * U[k][j];
                }
                L[i][j] = A[i][j] - sum;
            }

          }
          #pragma omp section
          {
            #pragma omp parallel for schedule(static)
            for (i = j; i < n; i++) {
                sum = 0;
                for(k = 0; k < j; k++) {
                    sum = sum + L[j][k] * U[k][i];
                }
                if (L[j][j] == 0) {
                    // exit(0);
                    return;
                }
                U[j][i] = (A[j][i] - sum) / L[j][j];
            }
          }
        }
      }
    }
}
int main(int argc, char const *argv[]) {
  int n=atoi(argv[1]);
  const char* filename=argv[2];
  num_threads=atoi(argv[3]);
  int strategy=atoi(argv[4]);
  double **A=(double **)malloc(sizeof(double*)*n);
  for (size_t i = 0; i < n; i++) {
    A[i]=(double*)malloc(sizeof(double)*n);
  }
  double **L=(double **)malloc(sizeof(double*)*n);
  for (size_t i = 0; i < n; i++) {
    L[i]=(double*)malloc(sizeof(double)*n);
  }
  double **U=(double **)malloc(sizeof(double*)*n);
  for (size_t i = 0; i < n; i++) {
    U[i]=(double*)malloc(sizeof(double)*n);
  }
  //open the file
  FILE* fileA=fopen(filename,"r");
  if (fileA==NULL) {
    printf("Error opening the input file for matrix A. exiting\n" );
    exit(-1);
  }
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      fscanf(fileA,"%lf",&A[i][j]);
    }
  }
  switch (strategy) {
    case 0:
      crout_0(A,L,U,n);
      break;
    case 1:
      crout_1(A,L,U,n);
      break;
    case 2:
      crout_2(A,L,U,n);
      break;
    case 3:
      crout_3(A,L,U,n);
      break;
    // case 4:
    //     crout_4(A,L,U,n);
    //     break
  }
  // const char * o="output_L_"
  char * outL=malloc(sizeof(char)*17+1);//"output_L_"+argv[4]+"_"+argv[3]+".txt";
  char * outU=malloc(sizeof(char)*17+1);//"output_U_"+argv[4]+"_"+argv[3]+".txt";
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

  write_output(outL, L, n );
  write_output(outU, U, n );
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
  free(outL);
  free(outU);
  for (size_t i = 0; i < n; i++) {
    free(A[i]);
    free(L[i]);
    free(U[i]);
  }
  free(A);
  free(L);
  free(U);
  return 0;
}
