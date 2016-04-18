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

/* error codes */
#define BUFSIZE			(4096)
#define NO_ERR			(0)
#define INPUT_ERR		(-100)
#define MALLOC_ERR		(-99)

/* Local function definitions */
char* creatBuffer(int size);
int correct(int x);

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
	int numItem = 0;
	int actualValue;
	int correctedValue;
	double actualVoltage;
	char *buffer;
	char *token;

	buffer = creatBuffer(BUFSIZE);
	/*read stdin line by line*/
	while(fgets(buffer, BUFSIZE, stdin) != NULL)
	{
		if(strcmp(buffer,"\n") && strcmp(buffer,"\r\n"))
		{
			numItem++;
			token = strtok(buffer, " ");
			/* reading token separated by spaces */
			actualVoltage = atof(token);
			token = strtok(NULL, " ");
			actualValue = atoi(token);
			correctedValue = correct(actualValue);
			/* print to stdout */
			fprintf(stdout, "%f ", actualVoltage);
			fprintf(stdout, "%d\n", correctedValue);
		}
	}

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
int correct(int x)
{
	double a = 4E-05;
	double b = 0.7329;
	double c = 52.973;

	return (int)(a * (x * x) + b * x + c + 0.5);
}