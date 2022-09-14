/*
 * test_llfifo.c includes all the functions used in test_llfifo(). The details of each function
 * is given in test_llfifo.h
 *
 * Author: Harsh Beriwal
 * Compiler Used: gcc (MinGW.org GCC-6.3.0-1) 6.3.0
 * IDE Used: Eclipse Version: 2022-06 (4.24.0)
 *
 * The below line was taken from the Internet - https://blog.hubspot.com/sales/famous-quotes
 *
 * "If you look at what you have in life, "
	"you'll always have more. If you look at what "
	"you don't have in life, you'll never have enough. "
	"-Oprah Winfrey";
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "test_llfifo.h"
#include "llfifo.h"

int checks_passed =0;
int total_checks  =0;
int test_failed   =0;
int tests_to_check =0;



void test_fifo_NULL(int val1, int val2)
{
	if(!test_failed){
		if(val1 ==val2){
			printf("Test:%d - Passed for Invalid Input\n", total_checks);
			checks_passed++;
		}
		else{
			printf("Test:%d - Test Failed for Invalid Input\n", total_checks);
			test_failed =ONE;
		}
	}
}

void test_llfifo_compare_length(int val_1, int val_2)
{
	if(!test_failed){
		if(val_1 == val_2){
			printf("Test:%d - Passed. Length as Expected "
					"(Value - %d)\n", total_checks, val_2);
			checks_passed++;
		}
		else{
			printf("Test:%d - Failed. Length not same as %d\n", total_checks, val_2);
			test_failed =ONE;
		}
	}
}

void test_llfifo_compare_capacity(int val_1, int val_2)
{
	if(!test_failed){
		if(val_1 == val_2){
			printf("Test:%d - Passed. Capacity as Expected "
					"(Value - %d)\n", total_checks, val_2);
			checks_passed++;
		}
		else{
			printf("Test:%d - Failed. Capacity not same as %d\n", total_checks, val_2);
			test_failed =ONE;
		}
	}
}


void test_llfifo_compare_return(int val_1, int val_2)
{
	if(!test_failed){
		if(val_1 == val_2){
			printf("Test:%d - Passed. Enqueue Return as Expected "
					"(Value - %d)\n", total_checks, val_2);
			checks_passed++;
		}
		else{
			printf("Test:%d - Failed. Enqueue Return not same "
					"as %d\n", total_checks, val_2);
			test_failed =ONE;
		}
	}
}

void test_llfifo_dequeued(char val1, char val2)
{
	if(!test_failed){
		if(val1 == val2){
			printf("Test:%d - Passed. Expected Dequeued Element (Value - %c)"
					"Received\n", total_checks, val2);
			checks_passed++;
		}
		else{
			printf("Test:%d - Failed for Valid Input. Expected "
					"(Value - %c)\n", total_checks, val2);
			test_failed =ONE;
		}
	}

}


int test_llfifo()
{
	char str[]= "If you look at what you have in life, "
			"you'll always have more. If you look at what "
			"you don't have in life, you'll never have enough. "
			"-Oprah Winfrey";

	llfifo_t *fifo, *fifo2;
	printf("Test:%d - Testing when Capacity is less than 0\n", ++total_checks);
	test_fifo_NULL((int)llfifo_create(-1), 0);
	CHECK;
	printf("Test:%d - Testing when Dequeuing data while NULL\n", ++total_checks);
	fifo = llfifo_create(5);
	test_llfifo_dequeued((int)llfifo_dequeue(fifo), 0);
	CHECK;
	llfifo_dequeue(fifo);
	printf("Test:%d - Testing when Enqueuing 30 times\n", ++total_checks);
	for(int i =0; i<30; i++)
	{
		llfifo_enqueue(fifo,(void*)&str[i]);
	}
	test_llfifo_compare_length(llfifo_length(fifo),30);
	CHECK;
	printf("Test:%d - Dequeuing 30 Times and checking Simultaneously\n", ++total_checks);
	for(int i =0; i<30; i++)
	{
		test_llfifo_dequeued(*(char*)llfifo_dequeue(fifo),*(char*)&str[i]);
		CHECK;
	}
	printf("Test:%d - Next UP checking if length and capacity are "
			"correct\n", ++total_checks);
	test_llfifo_compare_length(llfifo_length(fifo),0);
	CHECK;
	test_llfifo_compare_capacity(llfifo_capacity(fifo),30);
	CHECK;
	printf("Test:%d - Creating Second Instance FIFO2 with "
			"capacity 0\n", ++total_checks);
	fifo2 = llfifo_create(0);
	test_llfifo_compare_capacity(llfifo_capacity(fifo2), 0);
	CHECK;
	printf("Test:%d - Testing FIFO2 when Enqueuing Length Less than "
			"capacity\n", ++total_checks);
	fifo2 = llfifo_create(TWENTY);
	test_llfifo_compare_length(llfifo_length(fifo2),0);
	test_llfifo_compare_capacity(llfifo_capacity(fifo2), TWENTY);
	printf("Test:%d - Enqueuing 10 elements\n", ++total_checks);
	for(int i=0; i<10; i++)
	{
		test_llfifo_compare_return(llfifo_enqueue(fifo2,(void*)&str[i]),i+1);
	}
	test_llfifo_compare_length(llfifo_length(fifo2),10);
	test_llfifo_compare_capacity(llfifo_capacity(fifo2), TWENTY);
	for(int i =0; i<10; i++)
	{
		test_llfifo_dequeued(*(char*)llfifo_dequeue(fifo2),*(char*)&str[i]);
		CHECK;
	}
	printf("Test:%d - Testing FIFO2 when Enqueuing Length more than "
			"capacity\n", ++total_checks);
	fifo2 = llfifo_create(5);
	test_llfifo_compare_length(llfifo_length(fifo2),0);
	test_llfifo_compare_capacity(llfifo_capacity(fifo2), 5);
	for(int i=0; i<TWENTY; i++)
	{
		test_llfifo_compare_return(llfifo_enqueue(fifo2,(void*)&str[i]),i+1);
	}
	test_llfifo_compare_length(llfifo_length(fifo2),TWENTY);
	test_llfifo_compare_capacity(llfifo_capacity(fifo2), TWENTY);
	for(int i =0; i<10; i++)
	{
		test_llfifo_dequeued(*(char*)llfifo_dequeue(fifo2),*(char*)&str[i]);
		CHECK;
	}
	test_llfifo_compare_length(llfifo_length(fifo2),10);
	test_llfifo_compare_capacity(llfifo_capacity(fifo2), TWENTY);
	CHECK;
	printf("Test:%d - Testing both instance when Enqueue more dequeue "
			"less then Enqueue Full capacity\n", ++total_checks);
	fifo2 = llfifo_create(10);
	test_llfifo_compare_length(llfifo_length(fifo2),0);
	test_llfifo_compare_capacity(llfifo_capacity(fifo2), 10);
	for(int i=0; i<8; i++)
	{
		test_llfifo_compare_return(llfifo_enqueue(fifo2,(void*)&str[i]),i+1);
	}
	test_llfifo_compare_length(llfifo_length(fifo2),8);
	test_llfifo_compare_capacity(llfifo_capacity(fifo2), 10);
	for(int i =0; i<5; i++)
	{
		test_llfifo_dequeued(*(char*)llfifo_dequeue(fifo2),*(char*)&str[i]);
		CHECK;
	}
	test_llfifo_compare_length(llfifo_length(fifo2),3);
	test_llfifo_compare_capacity(llfifo_capacity(fifo2), 10);
	for(int i=0; i<7; i++)
	{
		test_llfifo_compare_return(llfifo_enqueue(fifo2,(void*)&str[i]),4+i);
	}
	test_llfifo_compare_length(llfifo_length(fifo2),10);
	test_llfifo_compare_capacity(llfifo_capacity(fifo2), 10);
	CHECK;
	printf("Test:%d - Testing Enqueue full equal dequeue full and then enqueue "
			"at NULL Length\n", ++total_checks);
	fifo = llfifo_create(0);
	test_llfifo_compare_length(llfifo_length(fifo),0);
	test_llfifo_compare_capacity(llfifo_capacity(fifo), 0);
	printf("Test:%d - ENQUEUING ALL ELEMENTS IN THE STRING\n", total_checks);
	for(int i=0; i<strlen(str); i++)
	{
		llfifo_enqueue(fifo,(void*)&str[i]);
	}
	test_llfifo_compare_length(llfifo_length(fifo),strlen(str));
	test_llfifo_compare_capacity(llfifo_capacity(fifo), strlen(str));
	printf("Test:%d - DEQUEUING ALL ELEMENTS IN THE STRING\n", total_checks);
	for(int i =0; i<strlen(str); i++)
	{
		llfifo_dequeue(fifo);
	}
	test_llfifo_compare_length(llfifo_length(fifo),0);
	test_llfifo_compare_capacity(llfifo_capacity(fifo), strlen(str));
	printf("Test:%d - ENQUEUING 20 ELEMENTS IN THE STRING\n", total_checks);
	for(int i=0; i<20; i++)
	{
		llfifo_enqueue(fifo,(void*)&str[i]);
	}
	test_llfifo_compare_length(llfifo_length(fifo),TWENTY);
	test_llfifo_compare_capacity(llfifo_capacity(fifo), strlen(str));
	CHECK;
	printf("Test:%d - Enqueuing less Dequeuing More then Enqueuing again at "
			"NULL Length\n", ++total_checks);
	fifo = llfifo_create(5);
	test_llfifo_compare_length(llfifo_length(fifo),0);
	test_llfifo_compare_capacity(llfifo_capacity(fifo), 5);
	printf("Test:%d - ENQUEUING 20 ELEMENTS IN THE STRING\n", total_checks);
	for(int i=0; i<TWENTY; i++)
	{
		llfifo_enqueue(fifo,(void*)&str[i]);
	}
	test_llfifo_compare_length(llfifo_length(fifo),TWENTY);
	test_llfifo_compare_capacity(llfifo_capacity(fifo), TWENTY);
	printf("Test:%d - DEQUEUING 25 ELEMENTS IN THE STRING\n", total_checks);
	for(int i =0; i<TWENTY; i++)
	{
		llfifo_dequeue(fifo);
	}
	for(int i =0; i<5;i++)
	{
		test_llfifo_dequeued((int)llfifo_dequeue(fifo), 0);
	}
	test_llfifo_compare_length(llfifo_length(fifo),0);
	test_llfifo_compare_capacity(llfifo_capacity(fifo), TWENTY);
	for(int i=0; i<5; i++)
	{

		test_llfifo_compare_return(llfifo_enqueue(fifo,(void*)&str[i]),i+1);
	}
	test_llfifo_compare_length(llfifo_length(fifo),5);
	test_llfifo_compare_capacity(llfifo_capacity(fifo), TWENTY);
	CHECK;
	printf("Test:%d - Enqueuing, Dequeuing one less and Enqueuing again at "
			"Length 1\n", ++total_checks);
	fifo = llfifo_create(20);
	test_llfifo_compare_length(llfifo_length(fifo),0);
	test_llfifo_compare_capacity(llfifo_capacity(fifo), TWENTY);
	printf("Test:%d - ENQUEUING 20 ELEMENTS IN THE STRING\n", total_checks);
	for(int i=0; i<20; i++)
	{
		llfifo_enqueue(fifo,(void*)&str[i]);
	}
	test_llfifo_compare_length(llfifo_length(fifo),TWENTY);
	test_llfifo_compare_capacity(llfifo_capacity(fifo), TWENTY);
	printf("Test:%d - DEQUEUING 19 ELEMENTS IN THE STRING\n", total_checks);
	for(int i =0; i<19; i++)
	{
		llfifo_dequeue(fifo);
	}
	test_llfifo_compare_length(llfifo_length(fifo),1);
	test_llfifo_compare_capacity(llfifo_capacity(fifo), TWENTY);
	for(int i=0; i<20; i++)
	{

		test_llfifo_compare_return(llfifo_enqueue(fifo,(void*)&str[i]),i+2);
	}
	test_llfifo_compare_length(llfifo_length(fifo),21);
	test_llfifo_compare_capacity(llfifo_capacity(fifo), 21);
	CHECK;
	printf("Test:%d - BOUNDARY CHECK - If Enqueued data is "
			"NULL\n", ++total_checks);
	fifo = llfifo_create(0);
	test_llfifo_compare_return(llfifo_enqueue(fifo, NULL),ERROR);
	test_llfifo_compare_length(llfifo_length(fifo),0);
	test_llfifo_compare_capacity(llfifo_capacity(fifo), 0);
	printf("Test:%d - BOUNDARY CHECK - If Enqueued data is MAX "
			"INTEGER\n", ++total_checks);
	fifo = llfifo_create(0);
	test_llfifo_compare_return(llfifo_enqueue(fifo,(void*)MAX_SIZE),ONE);
	test_llfifo_compare_length(llfifo_length(fifo),1);
	test_llfifo_compare_capacity(llfifo_capacity(fifo),ONE);
	CHECK;
	printf("Total Checks Passed for LLFIFO: %d\n",checks_passed);
	printf("Total Tests Passed for LLFIFO: %d/%d\n",total_checks,total_checks);
	printf("Destroying both Linked List Instances\n");
	llfifo_destroy(fifo);
	llfifo_destroy(fifo2);
	printf("All Tests cases passed for LLFIFO.C\n");
	return 1;
}
