/**************************************************************************
 * Dynamic Arrays Module  - public interface
 *
 * data types: Data - struct with data to be stored
 *             DArray - structure for Dynamic Array Header
 *
 * functions: CreateDArray, PushToDArray, DestroyDArray
 *
 * Author: Greg Semeraro, Juan C. Cockburn
 * Revised: JCCK 2/3/2015
 *          R Repka 10/02/2015
 **************************************************************************/
#ifndef _DYNAMIC_ARRAYS_H_
#define _DYNAMIC_ARRAYS_H_

/* Growth Policy : Constant Size */
#define GROWTH_AMOUNT (50)

/* error codes */
#define BUFSIZE			(4096)
#define NO_ERR			(0)
#define INPUT_ERR		(-100)
#define MALLOC_ERR		(-99)
#define REALLOC_ERR		(-98)
#define INIT_SIZE		(1000)


/**************************************************************************
 * DArray - Dynamic Array Header structure to keep track of its "state"
 *          The "state" of the Dynamic Array is: Capacity and EntriesUsed
 **************************************************************************/
typedef struct DArray
{
	unsigned int Capacity; /* Max Number of elements array can hold */
	unsigned int EntriesUsed; /* Number of array elements "used"       */
	double *Payload; /* Pointer to array that actually holds the data  */
} DArray;

/***************************************************************************
 function prototypes to create, add and destroy data arrays
 **************************************************************************/
void CreateDArray(DArray *DArrayPtr, unsigned int InitialSize);
void PushToDArray(DArray *DArrayPtr, double *dataPtr);
void DestroyDArray(DArray *DArrayPtr);

#endif /* _DYNAMIC_ARRAYS_H_ */