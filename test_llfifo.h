/*
 * test_llfifo.h includes all the declarations of functions used in test_llfifo().
 * The details of each function is given below.
 *
 * Author: Harsh Beriwal
 * Compiler Used: gcc (MinGW.org GCC-6.3.0-1) 6.3.0
 * IDE Used: Eclipse Version: 2022-06 (4.24.0)
 * No Leveraged code or files
 *
 */

#ifndef TEST_LLFIFO_H_
#define TEST_LLFIFO_H_

#define CHECK if(test_failed)return 0;
#define ONE 1
#define ZERO 0
#define TWENTY 20
#define ERROR -1
#define MAX_SIZE 4294967295

#endif /* TEST_LLFIFO_H_ */


/*
 * Thoroughly checks llfifo.c
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   If All tests are successful, it returns 1 otherwise 0 in case of any failed test.
 */
int test_llfifo();

/*
 * Compares Dequeued Element with Expected
 *
 * Parameters:
 *   Val1 - Actual Output
 *   Val2 - Expected Output
 *
 * Returns:
 *   If both val1 and val2 matches, it prints passed otherwise fails and sets test_failed
 *   flag
 */
void test_llfifo_dequeued(char val1, char val2);


/*
 * Compares Enqueues Return Value with Expected
 *
 * Parameters:
 *   Val1 - Actual Output
 *   Val2 - Expected Output
 *
 * Returns:
 *   If both val1 and val2 matches, it prints passed otherwise fails and sets test_failed
 *   flag
 */
void test_llfifo_compare_return(int val_1, int val_2);


/*
 * Compares Actual Capacity with Expected capacity
 *
 * Parameters:
 *   Val1 - Actual capacity
 *   Val2 - Expected capacity
 *
 * Returns:
 *   If both val1 and val2 matches, it prints passed otherwise fails and sets test_failed
 *   flag
 */
void test_llfifo_compare_capacity(int val_1, int val_2);


/*
 * Compares Actual Length with Expected Length
 *
 * Parameters:
 *   Val1 - Actual Length
 *   Val2 - Expected Length
 *
 * Returns:
 *   If both val1 and val2 matches, it prints passed otherwise fails and sets test_failed
 *   flag
 */
void test_llfifo_compare_length(int val_1, int val_2);


/*
 * Compares Linked List nodes for NULL and checks for Invalid Input
 *
 * Parameters:
 *   Val1 - LINKED LIST QUEUE ADDRESS
 *   Val2 - EXPECTED ADDRESS
 *
 * Returns:
 *   If both val1 and val2 matches, it prints passed otherwise fails and sets test_failed
 *   flag
 */
void test_fifo_NULL(int val1, int val2);
