/****************************************************************
myPlot devicedata output - student

Generates a png figure from columnar data.

Notes:
1) If you have two files one with inputs and one with outputs
you can combine them "by rows" using the bash command

paste realdevice.txt correction.txt > alldata.txt

2) In your .bashrc file you need to add the following lines to 
enable X:

export GDFONTPATH=/usr/share/fonts/dejavu
export GNUPLOT_DEFAULT_DDFONT="DejaVuSans.ttf"

3) popen is not ANSI (it is POSIX compliant) 

01/01/2016 R. Repka   - Initial version

***************************************************************/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <sys/stat.h>

/* Set to 1 to enable debug output */
#define DEBUG 0

int main (int argc, char *argv[]) 
{
    FILE *pipe;		            /* pipe to gnuplot  */

    if (3 == argc) 
    {
        printf("Generating plot for '%s'\n", argv[1]); 

        /*---------------------------------------------------------------
        Open pipe to gnuplot 
        ---------------------------------------------------------------*/
        #if DEBUG
            pipe = stdout;

            #else
            if( ( pipe = (FILE *) popen("gnuplot -persist","w") ) == NULL )
            {
                printf("Unable to open pipe to gnuplot\n");
                return -1;
            }
        #endif


        /*---------------------------------------------------------------
        Gnuplot commands 
        ---------------------------------------------------------------*/
        /* Set output to png file, can change to svg or x11 */


        /* Set the output file name */


        /* Set plot attributes */ 


        /* Title, labels and legend */


        /* Read data from file and generate plot */ 


        /* clean up: close pipe and return success code */
        pclose (pipe);
        return 0;
    }  /* if argc */
    else 
    {   /* wrong number of args, display program usage */
        printf("Usage: %s datafile plotfile\n", argv[0]);
        printf("    Converts 'datafile' to a PNG file called 'plotfile'\n");
        printf("    datafile format:  realVolt  origData  realVolt newData\n");
        return 1;
    } /* else () */

    return 0;
} /* main */
