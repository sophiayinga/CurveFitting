/********************************************************************
 * Applied Programming:                                             
 *    Solution of Overdetermined System of Equations Ax=b arising   
 *    in least square problems via QR factorizations using the GSL                                                 *                                                                  
 * Compilation:  gcc -ansi -g -lgsl -lgslcblas  GSL_LS_with_QR.c -o  GSL_LS_with_QR
 *                                                                  
 * Tested in Ubuntu 12.04 LTS                                       
 * Revised: Juan C. Cockburn, April 9, 2015 (juan.cockburn@rit.edu) 
 * R. Repka 10/10/2015 - Minor clean up
 ********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>

/*
* gcc -Wall -ansi -L/home/kaiwen/workspace/dev/lib -I/home/kaiwen/workspace/dev/include GSL_LS_with_QR.c -lgsl -lgslcblas -lm -o qs
* LD_LIBRARY_PATH=/home/kaiwen/workspace/dev/lib
* export LD_LIBRARY_PATH
*/

/* Dimension of A matrix: ROWS*COLS for this example    */ 
/* ROWS = number of equations, COLS = number of unknowns */
#define ROWS 10
#define COLS 1

int main(void)
{
  int i, j;         /* counters                 */
  int nr, nc;       /* number of rows and cols  */
  gsl_vector *c;    /* coefficient vector for normal equations: c=A^T b */
  gsl_matrix *A;    /* coefficient matrix       */
  gsl_vector *b;    /* coefficient vector       */
  gsl_vector *x_ls; /* least squares solution   */
  gsl_vector *tau;  /* Householder coefficients */
  gsl_vector *res;  /* vector of residuals      */
  
  /* In practice you will most likely read A and b from stdio or a file */
  /* In this example I just made up the matrix A and vector b           */
  /* You will also need the dimensions of A                             */
   nr=ROWS;
   nc=COLS;
   
  /* Allocate space for Matrices and vectors */
  c    = gsl_vector_alloc(nc);     /* Coefficient Matrix for normal equations: c=A^T b */
  A    = gsl_matrix_alloc(nr, nc); /* Data matrix */
  b    = gsl_vector_alloc(nr);     /* Data vector */
  x_ls = gsl_vector_alloc(nc);     /* Contains the final solution */
  res  = gsl_vector_alloc(nr);     /* Contains the residual */
  tau  = gsl_vector_alloc(nc);     /* required place holder for GSL */

  /* Make the first column of data 1's */
  for(i = 0; i < nr; i++)
  {
    gsl_matrix_set(A, i, 0, 1.0);
  }
  
  /* Initialize Matrix A with dummy data  */
  for(i = 1; i < nr; i++)
  {
    for(j = 0; j < nc; j++)
    {
      gsl_matrix_set(A, i, j, 1.0 / (double)(i + j + 1));
    }
  }
  
   /* Initialize vector b with dummy data */
  for(i = 0; i < nr; i++) 
  {
    gsl_vector_set(b, i, (double)i+1);
  }
  
  /* Print matrix A and vector  b */
  printf("A (%d x %d) \t\t\t\t\t   b (%d x 1)\n", nr,nc,nr);
  for(i = 0; i < nr; i++) 
  {
    printf("%3d: ", i);
    for(j = 0; j < nc; j++)
    {
      printf("% 12.5g ", gsl_matrix_get(A, i, j));
    }
    printf("|  % 12.5g ", gsl_vector_get(b, i));
    printf("\n");
  }
  printf("\n");

  /*  Solve Ax=b directly via QR factorization */

  /*  Find QR decomposition: (note that gls_linalg_QR_decomp overwrites A )
   *  On return, the vector tau and the columns of the lower triangular part of
   *  the matrix A have the Householder coefficients and vectors
   */
  gsl_linalg_QR_decomp(A, tau);

#if VERB
  /* Print overwritten matrix A */
  printf("A (%d x %d) overwritten after QR decomposition \n", nr,nc);
  for(i = 0; i < nr; i++) 
  {
    printf("%3d: ", i);
    for(j = 0; j < nc; j++) 
    {
      printf("% 12.5g ", gsl_matrix_get(A, i, j));
    }
    printf("\n");
  }
  printf("\n");
#endif

  /* Solve R x_ls = Q^T b, R is upper triangular */

  /* Note that we pass the "overwritten A", tau and b as input arguments
   * On return x_ls has the least square solution and res the residual vector Ax-b 
   */
  gsl_linalg_QR_lssolve(A, tau, b, x_ls, res);

  /* Print least squares solution x_ls and the total error sqrt{SOS}  */

  /* The error is the 2 norm of the residual vector                 
   * BLAS to compute the 2-nomr of a vector: dnrm2error            
   *      double gsl_blas_dnrm2 (const gsl_vector * x)            
   */
  printf("Least Squares Solution via QR factorization:\n");
  for(i = 0; i < nc; i++)
  {
    printf(" x_ls[%1d] = % 20.16e \n",i, gsl_vector_get(x_ls, i));
  }
  printf("\n");
  printf(" LS error = %f:\n",gsl_blas_dnrm2(res));

  /* Free memory  */
  gsl_vector_free(c);
  gsl_matrix_free(A);
  gsl_vector_free(b);
  gsl_vector_free(x_ls);
  gsl_vector_free(tau); 
  gsl_vector_free(res); 

  return 0; /* main */
}

