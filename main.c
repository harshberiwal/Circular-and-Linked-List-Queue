/*
 * main.c includes int main() and calls the llfifo and cbfifo test functions
 *
 * Author: Harsh Beriwal
 * Compiler Used: gcc (MinGW.org GCC-6.3.0-1) 6.3.0
 * IDE Used: Eclipse Version: 2022-06 (4.24.0)
 * No Leveraged code or files
 *
 */

#include <stdio.h>

#include "test_llfifo.h"
#include "test_cbfifo.h"


int main()
{
	printf("TESTING LLFIFO....\n");
	int test_success = 1;
	test_success = test_llfifo();
	printf("\nTESTING CBFIFO....\n");
	test_success &= test_cbfifo();
	if(test_success)
	{
		printf("\nAll Tests Passed and Functions worked successfully\n");
	}
	else
	{
		printf("\nTests Failed to run as expected\n");
	}




}
