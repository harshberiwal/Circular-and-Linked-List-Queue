/*
 * llfifo.c includes the Production code with all the functions for implementing Linked list Queue
 * The details of each function is given in the respective llfifo.h file by Professor Howdy Pierce.
 *
 * Author: Harsh Beriwal
 * Compiler Used: gcc (MinGW.org GCC-6.3.0-1) 6.3.0
 * IDE Used: Eclipse Version: 2022-06 (4.24.0)
 * No Leveraged code or files
 *
 */

#include <stdio.h>
#include "llfifo.h"
#include <stdlib.h>

#define ZERO 0
#define ONE 1
#define ERROR -1

//***************LINKED LIST NODE DEFINITION**********************
struct node{
	void *data;
	struct node *next;
};
//******************NODE MEMORY DEFINITION************************
struct llfifo_s{
	struct node *head, *tail, *temp;
	int length, capacity;
};


/*
 * Creates and initializes the FIFO
 *
 * Parameters:
 *   capacity  the initial size of the fifo, in number of elements.
 *             Valid values are in the range of 0 to the limits of memory
 *
 * Returns: A pointer to a newly-created llfifo_t n, or NULL in
 *   case of an error.
 */
llfifo_t *llfifo_create(int capacity)
{
	//********************IGNORE NEGATIVE CAPACITY****************************
	if(capacity <ZERO){
		return NULL;
	}
	llfifo_t* myfifo1;                       	 //Creating a return instance
	struct node* new_llfifo;
	int required_count =ZERO;

	//******************MEMORY ALLOCATION FOR LLFIFO**************************
	myfifo1 = (struct llfifo_s*)malloc(sizeof(struct llfifo_s));

	//*************MEMORY FULL. MALLOC DOESN'T RETURN ANYTHING****************
	if(myfifo1 == NULL){
		return NULL;
	}

	//*****************INITIALIZING ALL MEMORY ELEMENT************************
	myfifo1 -> capacity = capacity;
	myfifo1 -> length = ZERO;
	myfifo1 -> head = NULL;
	myfifo1 -> tail = NULL;

	//**********************CREATING NODES AS PER CAPACITY********************
	while(required_count != capacity){
		new_llfifo = (struct node*)malloc(sizeof(struct node));

	//*************MEMORY FULL. MALLOC DOESN'T RETURN ANYTHING****************
		if(new_llfifo == NULL){
			return NULL;              //malloc didn't return anything
		}
		new_llfifo->data = NULL;
		new_llfifo->next = NULL;

	//*********************FOR LENGTH = 0 if HEAD IS NULL*********************
		if(myfifo1 ->head == NULL){
			myfifo1->head = myfifo1->tail = new_llfifo;
			myfifo1->temp = myfifo1->head;
		}
		else{
			myfifo1->temp->next = new_llfifo;
			myfifo1->temp = new_llfifo;
		}
		required_count++;
	}

	//****************MOVING TEMP BACK TO THE FIRST NODE**********************
	myfifo1 ->temp = myfifo1 ->head;
	return myfifo1;
}


/*
 * Enqueues an element onto the FIFO, growing the FIFO by adding
 * additional elements, if necessary
 *
 * Parameters:
 *   fifo    The fifo in question
 *   element The element to enqueue, which cannot be NULL
 *
 * Returns:
 *   The new length of the FIFO on success, -1 on failure. It is an error to attempt
 * to enqueue the NULL pointer.
 */
int llfifo_enqueue(llfifo_t *fifo, void *element)
{
	struct node* new_llfifo;
	if(element == NULL){
		return ERROR;              		//element is not pointing to any data
	}
	//**********************WHEN ALL ELEMENTS ARE DEQUEUED****************************************
	if(((fifo -> length) < (fifo -> capacity)) && (fifo -> head == NULL) && (fifo -> tail == NULL)){
		fifo -> head = fifo -> tail = fifo -> temp;
		fifo -> tail ->data = element;
		(fifo -> length)++;
		return (fifo ->length);
	}
	//****************WHEN THE ELEMENT HAS TO BE ENQUEUD INTO THE FIRST NODE**********************
	else if(((fifo -> length) < (fifo -> capacity)) && (fifo ->tail ->next == NULL)){
		fifo -> tail -> next = fifo -> temp;
		fifo -> temp = fifo ->temp ->next;
		fifo -> tail = fifo -> tail ->next;
		fifo -> tail -> next = ZERO;
		fifo ->tail->data = element;
		(fifo -> length)++;
		return (fifo ->length);
	}
	//********************************FIRST TIME ENQUEUE******************************************
	else if(((fifo -> length) < (fifo -> capacity)) && (fifo -> length ==ZERO)){
		fifo ->tail->data = element;
		(fifo -> length)++;
		return (fifo ->length);
	}
	//********************************ENQUEUE ALL OTHER NODES*************************************
	else if((fifo -> length) < (fifo -> capacity)){
		fifo->tail->next->data = element;
		fifo->tail = fifo->tail->next;
		(fifo -> length)++;
		return (fifo ->length);
	}
	//****************************WHEN CAPACITY IS EQUAL TO LENGTH********************************
	else{
		new_llfifo = (struct node*)malloc(sizeof(struct node));
		if(new_llfifo == NULL){
			return ERROR;              		//malloc didn't return anything
		}
		new_llfifo ->data = element;
		new_llfifo ->next = ZERO;

		//*******************************ENQUEUE WITH CAPACITY 0**********************************
		if(fifo -> length == ZERO){
			fifo ->head = fifo ->tail = fifo -> temp = new_llfifo;
		}
		else{
			fifo ->tail ->next =new_llfifo;
			fifo ->tail =new_llfifo;
		}
		(fifo ->capacity)++;
		(fifo -> length)++;
	}
	return (fifo -> length);
}


/*
 * Removes ("dequeues") an element from the FIFO, and returns it
 *
 * Parameters:
 *   fifo  The fifo in question
 *
 * Returns:
 *   The dequeued element, or NULL if the FIFO was empty
 */
void *llfifo_dequeue(llfifo_t *fifo)
{
	void *dequeued;

	//*****************WHEN ALL ELEMENTS ARE ALREADY DEQUEUED****************
	if(fifo -> length ==ZERO){
		return NULL;
	}

	//**********************LAST ELEMENT TO BE DEQUEUED**********************
	else if(fifo -> length == ONE){
		dequeued = fifo -> head -> data;
		fifo -> head -> data =ZERO;
		fifo -> head = fifo -> tail = NULL;
		(fifo -> length)--;
		return dequeued;
	}

	//******************DEQUEUING BY CHANGING HEAD POSITION******************
	else{
		dequeued = fifo -> head -> data;
		fifo -> head -> data =ZERO;
		fifo -> head = fifo -> head -> next;
		(fifo -> length)--;
		return dequeued;
	}
}


/*
 * Returns the number of elements currently on the FIFO.
 *
 * Parameters:
 *   fifo  The fifo in question
 *
 * Returns:
 *   The number of elements currently on the FIFO
 */
int llfifo_length(llfifo_t *fifo)
{
	return (fifo ->length);             	//RETURNING LENGTH FROM MEMORY FOR THAT INSTANCE
}


/*
 * Returns the FIFO's current capacity
 *
 * Parameters:
 *   fifo  The fifo in question
 *
 * Returns:
 *   The current capacity, in number of elements, for the FIFO
 */
int llfifo_capacity(llfifo_t *fifo)
{
	return (fifo ->capacity);				//RETURNING CAPACITY FROM MEMORY FOR THAT INSTANCE
}


/*
 * Teardown function: Frees all dynamically allocated
 * memory. After calling this function, the fifo should not be used
 * again!
 *
 * Parameters:
 *   fifo  The fifo in question
 *
 * Returns: none
 */
void llfifo_destroy(llfifo_t *fifo)
{
	struct node* destroyed;
	int count =ZERO;

	//**********FREEING ALL THE CREATED NODES IN THE LINKED LIST*************
	while(fifo ->temp !=NULL)
	{
		destroyed = fifo ->temp;
		fifo -> temp = fifo -> temp ->next;
		free(destroyed);
		count++;
	}
	free(fifo);								//FREEING MEMORY OF FIFO
}






















