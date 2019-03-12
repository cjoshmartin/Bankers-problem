#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/* # BANKER'S Algorthim
 *
 * For this projet, you will write a multithreaded program that implements 
 * the banker's algorithm discussed in Section 7.5.3. Several customers request
 * and release resources from the bank. The banker will grant a request only 
 * if it leaves the system in a safe state. A request that leaves the system in
 * an unsafe state will be deniced. The programming assignment combines
 * three separate topics: 
 *  1) Multithreading 
 *  2) preventing race conditions
 *  3) deadlock Avoidance
 *
 * ## The Banker
 * The banker consider requests from `n` customers from 
 * `m` resources types (section 7.5.3). The banker will keep track of the
 * resource using the following data structures.
 *
 * TODO
//----------------------------------------------------------------------------- 
*/
/* In this project you will implement the Banker’s problem described in Chapter
   7 of your book (p345/346). Use the Pthreads library and the VM that you built
   in HMW 1 to complete this project. */

#define NUMBER_OF_CUSTOMERS 5 // `n`
#define NUMBER_OF_RESOURCES 3 // `m`

// the available amount of each resource
int available[NUMBER_OF_RESOURCES];
// the maximum demand of each customer
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

// the amount of currently allocated to each customer
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

// the remaining need of each customer
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

/*You may assume that you have three resources with the following number of
  instances (available array) The number of customers, n, can vary.  Initialize
  your maximum array with random numbers less than available array Every time
  you make an allocation show the following:
 * The request
 * Allocation
 * Available
 * Maximum
 * Need
 Indicate whether the request was successful or denied In your report show an
 example of a denied request and a granted request and explain the results.
 Why was the request denied or granted. */

// (4 pts) implementation of safety algorithm
int safety(){
    int finish[NUMBER_OF_CUSTOMERS] = {FALSE},
        i =0, 
        j =0;

    while ( i < NUMBER_OF_CUSTOMERS && !finish[i] /*&& Need <= work  */){
        // work[i] += allocation
        finish[i] = TRUE;
        i++;
    }

    for (j= 0; j < i ;j++)
        if (!finish[j]) // if a process == False then not in a safe state
            return FALSE;

    

    return TRUE; 
}

/* (4 pts) implementation of request_resources
// TODO: These functions should return 0 if successful otherwise -1
// TODO: NEEDS MUTEX LOCKS */
int request_resources(int customer_num, int request[]);
int release_resources(int customer_num, int release[]);

int main(int argc, char** argv){
    int  i;

    for (i=1; i < argc; ++i){
        available[i] = atoi(argv[i]); // copy resources to avav.
    }

    // (4 pts) implementation of customer threads

    // (4 pts) overall working program

    return 0;
} 
//----------------------------------------------------------------------------- 
