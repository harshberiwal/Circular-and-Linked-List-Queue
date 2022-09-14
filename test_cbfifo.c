/*
 * test_cbfifo.c includes all the functions used in test_cbfifo(). The details of each function
 * is given in test_cbfifo.h
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
#include <string.h>

#include "test_cbfifo.h"
#include "cbfifo.h"



static int total_checks = 0;
static int test_failed = 0;
static int checks_passed =0;

char test_arr[128];

void test_cbfifo_compare_length(int val_1, int val_2)
{
	if(!test_failed){
		if(val_1 == val_2){
			printf("Test:%d - Passed. Length as Expected "
					"(Value - %d)\n", total_checks, val_2);
			checks_passed++;
		}
		else{
			printf("Test:%d - Failed. Length not same as "
					"(Value - %d)\n", total_checks, val_2);
			test_failed =ONE;
		}
	}
}

void test_cbfifo_compare_capacity(int val_1, int val_2)
{
	if(!test_failed){
		if(val_1 == val_2){
			printf("Test:%d - Passed. Capacity as Expected "
					"(Value - %d)\n", total_checks, val_2);
			checks_passed++;
		}
		else{
			printf("Test:%d - Failed. Capacity not same as "
					"(Value - %d)\n", total_checks, val_2);
			test_failed =ONE;
		}
	}
}


void test_cbfifo_compare_return(int val_1, int val_2)
{
	if(!test_failed){
		if(val_1 == val_2){
			printf("Test:%d - Passed. Enqueue Returned %d as"
					" Expected\n", total_checks, val_2);
			checks_passed++;
		}
		else{
			printf("Test:%d - Failed. Enqueue Return not same "
					"as %d\n", total_checks, val_2);
			test_failed =ONE;
		}
	}
}

void test_cbfifo_dequeued(int val1, int val2)
{
	if(!test_failed){
		if(val1 == val2){
			printf("Test:%d - Passed. Expected Dequeued bytes - %d "
					"received\n", total_checks, val2);
			checks_passed++;
		}
		else{
			printf("Test:%d - Failed for Valid Input. "
					"Expected - %d\n", total_checks, val2);
			test_failed =ONE;
		}
	}
}

void test_dequeued_elements(int val1, int val2)
{
	if(!test_failed){
		if(val1 ==val2){
			printf("Test:%d - Matching %c\n", total_checks, val1);
			checks_passed++;
		}
		else{
			printf("Test:%d - Not matching %c\n", total_checks, val2);
			test_failed =ONE;
		}
	}
}

int test_cbfifo()
{
	char str[]= "If you look at what you have in life, "
				"you'll always have more. If you look at what "
				"you don't have in life, you'll never have enough. "
				"-Oprah Winfrey";
	char *buf = NULL;
	printf("Test:%d - Testing when buf Pointer is NULL\n", ++total_checks);
	test_cbfifo_compare_return(cbfifo_enqueue((void*)buf, 4), -1);
	CHECK;
	printf("Test:%d - Enqueuing NULL character\n", ++total_checks);
	test_cbfifo_compare_return(cbfifo_enqueue('\0', 4), -1);
	test_cbfifo_compare_length(cbfifo_length(),0);
	CHECK;
	printf("Test:%d - Directly calling dequeue while Queue is "
			"NULL\n", ++total_checks);
	test_cbfifo_dequeued(cbfifo_dequeue((void*)&test_arr[0], 1), 0);
	test_cbfifo_compare_length(cbfifo_length(),0);
	CHECK;
	printf("Test:%d - Testing Enqueue function until full "
			"capacity\n", ++total_checks);
	test_cbfifo_compare_capacity(cbfifo_capacity(),SIZE);
	test_cbfifo_compare_return(cbfifo_enqueue((void*)&str[0], SIZE), SIZE);
	CHECK;
	printf("Test:%d - Testing Dequeue function until zero "
			"length\n", ++total_checks);
	test_cbfifo_dequeued(cbfifo_dequeue((void*)&test_arr[0], SIZE), SIZE);
	printf("Test:%d - Comparing Dequeued Array with "
			"Expected\n", total_checks);
	for(int i=0; i<SIZE;i++){
		test_dequeued_elements(test_arr[i], str[i]);
	}
	test_cbfifo_compare_length(cbfifo_length(),0);
	CHECK;
	printf("Test:%d - Enqueing when nbytes greater than "
			"capacity(150 Bytes)\n", ++total_checks);
	test_cbfifo_compare_return(cbfifo_enqueue((void*)&str[0], 150), 128);
	test_cbfifo_compare_length(cbfifo_length(),128);
	test_cbfifo_compare_capacity(cbfifo_capacity(),128);
	CHECK;
	printf("Test:%d - Testing when Dequeue output Buf doesn't "
			"point anywhere\n", ++total_checks);
	test_cbfifo_dequeued(cbfifo_dequeue(NULL, 1), 0);
	test_cbfifo_compare_length(cbfifo_length(),128);
	CHECK;
	printf("Test:%d - Enqueuing when length is 128\n", ++total_checks);
	test_cbfifo_compare_return(cbfifo_enqueue((void*)&str[0], 20), 0);
	test_cbfifo_compare_length(cbfifo_length(),128);
	test_cbfifo_compare_capacity(cbfifo_capacity(),128);
	CHECK;
	printf("Test:%d - Dequeuing more than QUEUE SIZE\n", ++total_checks);
	test_cbfifo_dequeued(cbfifo_dequeue((void*)&test_arr[0], 150), 128);
	test_cbfifo_compare_length(cbfifo_length(),0);
	CHECK;
	printf("Test:%d - Enqueuing more, dequeue less, then enqueue "
			"again\n", ++total_checks);
	test_cbfifo_compare_return(cbfifo_enqueue((void*)&str[50], 100), 100);
	test_cbfifo_dequeued(cbfifo_dequeue((void*)&test_arr[0], 50), 50);
	test_cbfifo_compare_length(cbfifo_length(),50);
	test_cbfifo_compare_return(cbfifo_enqueue((void*)&str[0], 60), 60);
	test_cbfifo_compare_length(cbfifo_length(),110);
	CHECK;
	printf("Test:%d - BOUNDARY CHECK, Enqueuing nbytes is MAX size_t "
			"value\n", ++total_checks);
	test_cbfifo_dequeued(cbfifo_dequeue((void*)&test_arr[0], 110), 110);
	test_cbfifo_compare_length(cbfifo_length(),0);
	test_cbfifo_compare_return(cbfifo_enqueue((void*)&str[0], MAX_SIZE), 128);
	test_cbfifo_compare_length(cbfifo_length(),128);
	CHECK;
	printf("Test:%d - BOUNDARY CHECK, Enqueuing 0 nbytes value\n", ++total_checks);
	test_cbfifo_dequeued(cbfifo_dequeue((void*)&test_arr[0], 128), 128);
	test_cbfifo_compare_length(cbfifo_length(),0);
	test_cbfifo_compare_return(cbfifo_enqueue((void*)&str[0], 0), 0);
	test_cbfifo_compare_length(cbfifo_length(),0);
	CHECK;
	printf("Test:%d - INTEGER CHECK\n", ++total_checks);
	int x=310;
	test_cbfifo_compare_return(cbfifo_enqueue((void*)&x, 4), 4);
	test_cbfifo_compare_length(cbfifo_length(),4);
	CHECK;
	printf("Total Checks Passed for CBFIFO: %d\n",checks_passed);
	printf("Total Tests Passed for CBFIFO: %d/%d\n",total_checks,total_checks);
	printf("All Tests cases passed for CBFIFO.C\n");
	return 1;
}






