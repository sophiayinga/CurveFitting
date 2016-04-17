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
#include <string.h>
#include <stdlib.h>
#include "correction.h"

/* Local function definitions */
char* creatBuffer(int size);
void CreateDArray(DArray *DArrayPtr, unsigned int InitialSize);
void PushToDArray(DArray *DArrayPtr, double *PayloadPtr);
void DestroyDArray(DArray *DArrayPtr);

/******************************************************************************
 Program to test the correction module.  Reads in input params from the user
 and calucate the root using the methods in rootfinding module.
 int main(int argv, char* argv[])
 Where:
 int argv        - The number of command line parameters
 char *argv[]    - An array of pointers to the parameters
 returns: in     - 0 for success, non-zero for error
 errors:         - Error message printed to stderr and exits with an error
 code
 ******************************************************************************/
int main(int argc, char *argv[])
{
	/* local variables */
	int lcv;
	int numItem = 0;
	int result = 0;
	char *buffer;
	char *token;
	double m = 0.0;
	double b = 0.0;
	double x = 0.0;
	double y = 0.0;
	double sx = 0.0;
	double sy = 0.0;
	double sxy = 0.0;
	double sxx = 0.0;
	DArray arrayX;

	CreateDArray(&arrayX, INIT_SIZE);
	buffer = creatBuffer(BUFSIZE);
	/*read stdin line by line*/
	while(fgets(buffer, BUFSIZE, stdin) != NULL)
	{
		if(strcmp(buffer,"\n") && strcmp(buffer,"\r\n"))
		{
			numItem++;
			token = strtok(buffer, " ");
			/* reading token separated by spaces */
			x = atof(token);
			token = strtok(NULL, " ");
			y = atof(token);
			/* processing data*/
			PushToDArray(&arrayX, &x);
			sx += x;
			sy += y;
			sxy += x*y;
			sxx += x*x;
		}
	}

	fprintf(stdout, "sx: %f\n", sx);
	fprintf(stdout, "sy: %f\n", sy);
	fprintf(stdout, "sxy: %f\n", sxy);
	fprintf(stdout, "sxx: %f\n", sxx);
	fprintf(stdout, "numItem: %d\n", numItem);
	
	/* calculate for m and b */
	m = ( (numItem * sxy) - (sx * sy) ) / ( (numItem * sxx) - (sx * sy) );
	b = ( (sxx * sy) - (sx * sxy) ) / ( (numItem * sxx) - (sx * sy) );
	/* output results to stdout */
	fprintf(stdout, "m: %f\n", m);
	fprintf(stdout, "b: %f\n", b);
	/*for(lcv=0; lcv < numItem; lcv++)
	{
		result = (int) (arrayX.Payload[lcv]* m + b + 0.5);
		fprintf(stdout, "%f ", arrayX.Payload[lcv]);
		fprintf(stdout, "%d\n", result);
	}*/

	return NO_ERR;
}

/******************************************************************************
 Program to test the correction module.  Reads in input params from the user
 and calucate the root using the methods in rootfinding module.
 int main(int argv, char* argv[])
 Where:
 int argv        - The number of command line parameters
 char *argv[]    - An array of pointers to the parameters
 returns: in     - 0 for success, non-zero for error
 errors:         - Error message printed to stderr and exits with an error
 code
 ******************************************************************************/
char* creatBuffer(int size)
{
	char *buf;
	buf = (char*)malloc(size);
	/* malloc checking */
	if(buf == NULL)
	{
		fprintf(stderr, "malloc() error at line %d in %s",
				__LINE__, __FILE__);
		exit MALLOC_ERR;
	}
	return buf;
}

/***************************************************************************
 CreateDArray -- Allocates memory and initializes DArray state
 void CreateDArray(DArray *DArrayHead, unsigned int InitialSize)
 Where:
 DArray *DArrayHead       - Pointer to a storage block which holds the
 data structure entry
 unsigned int InitialSize - The initial data block size, could be 0
 returns: void            - nothing is returned.
 errors:                  - This routine will print an error message to
 stderror and exit with an error code
 **************************************************************************/
void CreateDArray(DArray *DArrayHead, unsigned int InitialSize)
{
	/* Initialize array with 0 entries used */
	DArrayHead->EntriesUsed = 0;
	/* Initialize capacity (you decide, could be zero) */
	DArrayHead->Capacity = InitialSize;
	/* Based on capacity allocate memory storage, if necessary */
	/* If initial capacity is zero, no allocation needed */

	/* else Allocate storage space for payload according to struc Data */
	DArrayHead->Payload = malloc(InitialSize * sizeof(double));
	/* if memory not allocated print error to stderr and exit with a code */
	if (DArrayHead->Payload == NULL)
	{
		fprintf(stderr, "malloc() error at line %d in %s",
				__LINE__, __FILE__);
		exit(MALLOC_ERR);
	}
} /* CreateDArray() */

/***************************************************************************
 PushToDArray -- Adds data at the end of the dynamic array and updates its
 state in the array header.  If full, reallocates memory
 space according to growth policy
 unsigned int PushToDArray(DArray *DArrayHead, Data *PayloadPtr)
 Where:
 DArray *DArrayHead      - Pointer to a storage block which holds the
 data structure entry
 Data * PayloadPtr       -
 returns: unsigned int   - The index of the last element inserted
 errors:                 - This routine will print an error message to
 stderror and exit with an error code
 **************************************************************************/
void PushToDArray(DArray *DArrayHead, double *dataPtr)
{
	/* Check if the array needs to be made larger */
	if (DArrayHead->EntriesUsed >= DArrayHead->Capacity)
	{
		/* If yes, increase the size of the dynamic array */
		DArrayHead->Capacity += GROWTH_AMOUNT;

		/* Re-allocate storage for the array elements using larger size */
		DArrayHead->Payload = realloc(DArrayHead->Payload, sizeof(double) * (DArrayHead->Capacity));
		/* if memory not re-allocated print error to stderr and exit */
		if (DArrayHead->Payload == NULL)
		{
			fprintf(stderr, "realloc() error at line %d in %s",
				__LINE__, __FILE__);
			exit(REALLOC_ERR);
		}
	}
	memcpy(&(DArrayHead->Payload[DArrayHead->EntriesUsed]), dataPtr, sizeof(double));
	/* Increment the number of elements used in Darray header */
	(DArrayHead->EntriesUsed)++;
} /* PushToDArray() */

/*************************************************************************
 DestroyDArray -- Returns the memory back to the heap and updates the
 state in the array header
 void DestroyDArray(DArray *DArrayHead)
 Where:
 DArray *DArrayHead  - Pointer to a storage block which holds the
 data structure entry
 returns: void       - nothing is returned.
 errors:             - No errors are reported
 *************************************************************************/
void DestroyDArray(DArray *DArrayHead)
{
	/* Set the number of entries used to zero in Darray header */
	DArrayHead->EntriesUsed = 0;
	/* Set the capacity to zero in Darray header*/
	DArrayHead->Capacity = 0;
	/* De-allocate the storage for the array elements */
	free(DArrayHead->Payload);
	DArrayHead->Payload = NULL;
} /* DestroyDArray() */