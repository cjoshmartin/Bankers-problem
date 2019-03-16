#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <pthread.h>

enum bool {FALSE=0, TRUE=1};

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
//-----------------------------------------------------------------------------
*/
/* In this project you will implement the Banker’s problem described in Chapter
   7 of your book (p345/346). Use the Pthreads library and the VM that you built
   in HMW 1 to complete this project. */

#define NUMBER_OF_CUSTOMERS 5 // `n`
#define NUMBER_OF_RESOURCES 3 // `m`

// the available amount of each resource
int available[NUMBER_OF_RESOURCES];

void updateAvailable(int size);

// the maximum demand of each customer
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

// the amount of currently allocated to each customer
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES] = { 0 };
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES] = { 0 };

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


int isGreaterThenZero(int val){
    return val > 0 ? val : 0;
}
void calculateANeed(int i, int j ) {
    int amount = maximum[i][j] - allocation[i][j];
    need[i][j] = isGreaterThenZero(amount);
}

void updateNeed() {
    int i =0 , j= 0;
    while (i < NUMBER_OF_CUSTOMERS ){
        while(j < NUMBER_OF_RESOURCES){
            calculateANeed(i,j++);
        }
        i++;
    }
}

// (4 pts) implementation of safety algorithm
int isSafe(){

    int finish[NUMBER_OF_RESOURCES] = {FALSE},
            safeSeq[NUMBER_OF_CUSTOMERS],
            working[NUMBER_OF_CUSTOMERS],
            i =0,
            j =0;

    updateNeed();

    for (j = 0; j < NUMBER_OF_CUSTOMERS; j++){
        working[j]= available[j];
    }

    while ( i < NUMBER_OF_CUSTOMERS){

        int found = FALSE;

        for(int process = 0; process < NUMBER_OF_CUSTOMERS; process++){

            if(finish[process] == FALSE){
                j=0;
                while (
                        j < NUMBER_OF_CUSTOMERS
                        && need[process][j] > working[j]
                        ) {
                    j++;
                } // end of while

                if (j == NUMBER_OF_RESOURCES){
                    for(int k= 0; k < NUMBER_OF_RESOURCES; k++)
                        working[k] += allocation[process][k];

                    safeSeq[i++] = process;

                    finish[process] = TRUE;

                    found = TRUE;

                } // end of if
            } // end of if
        } // end of for

        if(found == FALSE){
            printf("System failed");
            return FALSE;
        }
    } // end of while , TODO: Could make this into thread

    printf("System is in safe state.\nSafe sequence is: ");
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
        printf("%d ", safeSeq[i]);

    return TRUE;
}



/* (4 pts) implementation of request_resources
// TODO: These functions should return 0 if successful otherwise -1
// TODO: NEEDS MUTEX LOCKS */

enum safeState { success= 0, failure = -1 };

struct thread
{
    int customer_num;
    int * process; // same for all
};


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/7_Deadlocks.html

int request_resources(int customer_num, int request[]){

    if (!isSafe())
        return failure;

    for (int i = 0; i < NUMBER_OF_CUSTOMERS ; i++){
        for (int j = 0; j < NUMBER_OF_RESOURCES ; ++j) {
            if ( request[i] > need[i][j])
                return failure;
        }
    }

    while (request[customer_num] > available[customer_num]) {//TODO: Look at last TODO LOL
        pthread_mutex_lock(&mutex);
    }
    pthread_mutex_unlock(&mutex);

    // TODO

    /*
     * Check to see if the request can be granted safely, by pretending it has been granted and then seeing if the
     * resulting state is safe. If so, grant the request, and if not, then the process must wait until its request
     * can be granted safely.The procedure for granting a request ( or pretending to for testing purposes ) is:
     * - Available = Available - Request
     * - Allocation = Allocation + Request
     * - Need = Need - Request
     */

    available[customer_num]  -= request[customer_num];

    for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i) {
        allocation[customer_num][i] += request[customer_num]; // TODO: maybe is wrong
        need[customer_num][i] -= request[i];
    }

    return success;

//    pthread_exit(NULL);
}

int release_resources(int customer_num, int release[]) {
    if (!isSafe())
        return failure;

    return success;
}

void *customer(void *strut) {

    struct thread _instance = *(struct thread*)strut;

    int customer_num = _instance.customer_num,
            * customers = _instance.process;

    request_resources(customer_num, customers);
    release_resources(customer_num, customers);
    return NULL;
}

// (4 pts) overall working program
int main(int argc, char** argv){
    pthread_t customers[NUMBER_OF_CUSTOMERS];
    struct thread threads[NUMBER_OF_CUSTOMERS];
    srand(time(NULL));

    for (int i = 1; i < argc; ++i)
        available[i-1] = atoi(argv[i]); // copy resources to av.

    int size = argc - 1;

    for(int i = 0; i < size; i++){
        for (int j = 0; j < size; j++) {
            maximum[i][j] = rand() % available[i]; // allcat. random values to max based on values passed to available[]
            allocation[i][j] = rand() % available[i];
        }
    }

    updateAvailable(size);
    
    // TODO: allocation is never set
    // (4 pts) implementation of customer threads
//    while(TRUE){
        isSafe();
//        for (int n = 0; n < NUMBER_OF_CUSTOMERS; n++){
//            threads[n].customer_num = n;
//            threads[n].process = available;// TODO: This is probably wrong
//
//            pthread_create( &customers[n], // thread
//                    NULL, // ??
//                    customer, // function to send the threads to
//                    &threads[n]
//                    );
//
//            pthread_join(
//                    customers[n],
//                    NULL // return value from join
//                    );
//        }
//    }

    return 0;
}

void updateAvailable(int size) {
    for (int j =0; j < size; j++){
        int sum = 0;
        for (int i = 0; i < size; ++i) {
            sum += allocation[i][j];
        }
        available[j] += sum;
    }

    printf("New Available: ");

    for (int i = 0; i < size; ++i) {
        printf("%d ", available[size]);
    }
}
