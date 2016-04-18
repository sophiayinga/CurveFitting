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
int correct(double x);

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
	int correctedValue;
	double actualVoltage;
	double actualValue;
	char *buffer;
	char *token;
	FILE *inputFIle;


	inputFIle = fopen(argv[1], "r");
	buffer = creatBuffer(BUFSIZE);
	/*read stdin line by line*/
	while(fgets(buffer, BUFSIZE, inputFIle) != NULL)
	{
		if(strcmp(buffer,"\n") && strcmp(buffer,"\r\n"))
		{
			numItem++;
			token = strtok(buffer, " ");
			/* reading token separated by spaces */
			actualVoltage = atof(token);
			token = strtok(NULL, " ");
			actualValue = atof(token);
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
int correct(double x)
{
	
	double a = 0.00000002;
	double b = 0.0001;
	double c = 0.977;
	double d = 46.786;
	double result = 0;

	result = (a * (x * x * x) - b * (x * x) + c * x - d);
	/*
	double a = 0.00004;
	double b = 0.7326;
	double c = 53.133;
	double result = 0;

	result = (a * (x * x) + b * x + c);
	*/

	return (int)(result + 0.5);
}