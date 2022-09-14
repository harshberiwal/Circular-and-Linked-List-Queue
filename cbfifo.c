/*
 * cbfifo.c includes the Production code with all the functions for implementing
 * Circular buffer Queue
 * The details of each function is given in the respective cbfifo.h file
 * by Professor Howdy Pierce.
 *
 * Author: Harsh Beriwal
 * Compiler Used: gcc (MinGW.org GCC-6.3.0-1) 6.3.0
 * IDE Used: Eclipse Version: 2022-06 (4.24.0)
 * No Leveraged code or files
 *
 */

#include "cbfifo.h"
#include <stdio.h>
#include <stdint.h>

#define SIZE 128
#define DIVIDE_BY_SIZE (SIZE-1)
#define OUT_OF_RANGE -1
#define ZERO 0
#define INCREMENT(x) (x+1)
#define ERROR -1

char queue[SIZE];
char arr[SIZE];
int head =-1;
int tail =-1;
int length = 0;
int capacity =0;

/*
 * Enqueues data onto the FIFO, up to the limit of the available FIFO
 * capacity.
 *
 * Parameters:
 *   buf      Pointer to the data
 *   nbyte    Max number of bytes to enqueue
 *
 * Returns:
 *   The number of bytes actually enqueued, which could be 0. In case
 * of an error, returns (size_t) -1.
 */
size_t cbfifo_enqueue(void *buf, size_t nbyte)
{
	size_t byte_count =nbyte;
	size_t count =ZERO;
	char *buff;
	buff = buf;
	capacity = SIZE;

	//**************BUFF DOESN"T POINT TO ANYTHING*******************
	if(buff ==NULL){
		return ERROR;
	}

	//****************LOOPING TO ADD EACH BYTE***********************
	while(byte_count--)
	{
		//*********************QUEUE EMPTY***************************
		if((head == OUT_OF_RANGE) && (tail == OUT_OF_RANGE)){
			head = tail =ZERO;
			queue[tail] = *buff++;
		}
		//**********************QUEUE FULL***************************
		else if(head == ((INCREMENT(tail))&DIVIDE_BY_SIZE)){
			length = length +count;
			return count;
		}
		//*******************ENQUEUING EACH BYTE*********************
		else {
			tail = (INCREMENT(tail))&DIVIDE_BY_SIZE;
			queue[tail] = *buff++;
		}
		count++;
	}
	length = length +count;
	return count;
}

/*
 * Attempts to remove ("dequeue") up to nbyte bytes of data from the
 * FIFO. Removed data will be copied into the buffer pointed to by buf.
 *
 * Parameters:
 *   buf      Destination for the dequeued data
 *   nbyte    Bytes of data requested
 *
 * Returns:
 *   The number of bytes actually copied, which will be between 0 and
 * nbyte.
 *
 */
size_t cbfifo_dequeue(void *buf, size_t nbyte)
{
	size_t count =ZERO;
	size_t byte_count =nbyte;
	char *buff = buf;
	if(buf == NULL)
		return count;
	//***************LOOPING TO REMOVE EACH BYTE*********************
	while(byte_count --)
	{
		//*********************QUEUE EMPTY***************************
		if((head == OUT_OF_RANGE) && (tail == OUT_OF_RANGE))
		{
			length = length - count;
			return count;
		}
		//****************LAST ELEMENT TO DEQUEUE********************
		else if(head == tail)
		{
			 *buff = queue[head];
			 head = tail = OUT_OF_RANGE;
		}
		//******************DEUQUEUING ELEMENTS**********************
		else{
			 *buff++ = queue[head];
			 head = INCREMENT(head)&DIVIDE_BY_SIZE;
		}
		count++;
	}
	length = length - count;
	return count;
}


/*
 * Returns the number of bytes currently on the FIFO.
 *
 * Parameters:
 *   none
 *
 * Returns:
 *   Number of bytes currently available to be dequeued from the FIFO
 */
size_t cbfifo_length()
{
	 return length;
}


/*
 * Returns the FIFO's capacity
 *
 * Parameters:
 *   none
 *
 * Returns:
 *   The capacity, in bytes, for the FIFO
 */
size_t cbfifo_capacity()
{
	return SIZE;
}







