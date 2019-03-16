#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <pthread.h>

#include "general.h"
#include "my_structs.h"

int isGreaterThenZero(int val) {
    return val > 0 ? val : 0;
}

void calculateANeed(int i, int j, banker _them) {
    int amount = _them.maximum[i][j] - _them.allocation[i][j];
    _them.need[i][j] = isGreaterThenZero(amount);
}

void updateNeed(banker _them) {
    int i =0 , j= 0;
    while (i < NUMBER_OF_CUSTOMERS ){
        while(j < NUMBER_OF_RESOURCES){
            calculateANeed(i,j++, _them);
        }
        i++;
    }
}

void updateAvailable(int size, banker _them) {
    for (int j =0; j < size; j++){
        int sum = 0;
        for (int i = 0; i < size; ++i) {
            sum += _them.allocation[i][j];
        }
        _them.available[j] += sum;
    }

//    printf("New Available: ");

//    for (int i = 0; i < size; ++i) {
//        printf("%d ", _them.available[size]);
//    }
}

// (4 pts) implementation of safety algorithm
int isSafe(banker _them){

    int finish[NUMBER_OF_RESOURCES] = {FALSE},
            safeSeq[NUMBER_OF_CUSTOMERS],
            working[NUMBER_OF_CUSTOMERS],
            i =0,
            j =0;

    updateNeed(_them);

    for (j = 0; j < NUMBER_OF_CUSTOMERS; j++){
        working[j]= _them.available[j];
    }

    while ( i < NUMBER_OF_CUSTOMERS){

        int found = FALSE;

        for(int process = 0; process < NUMBER_OF_CUSTOMERS; process++){

            if(finish[process] == FALSE){
                j=0;
                while (
                        j < NUMBER_OF_CUSTOMERS
                        && _them.need[process][j] > working[j]
                        ) {
                    j++;
                } // end of while

                if (j == NUMBER_OF_RESOURCES){
                    for(int k= 0; k < NUMBER_OF_RESOURCES; k++)
                        working[k] += _them.allocation[process][k];

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




pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/7_Deadlocks.html

int request_resources(int customer_num, int request[], banker _them){

    if (!isSafe(_them))
        return failure;

    for (int i = 0; i < NUMBER_OF_CUSTOMERS ; i++){
        for (int j = 0; j < NUMBER_OF_RESOURCES ; ++j) {
            if ( request[i] > _them.need[i][j])
                return failure;
        }
    }

    while (request[customer_num] > _them.available[customer_num]) {//TODO: Look at last TODO LOL
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

    _them.available[customer_num]  -= request[customer_num];

    for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i) {
        _them.allocation[customer_num][i] += request[customer_num]; // TODO: maybe is wrong
        _them.need[customer_num][i] -= request[i];
    }

    return success;

//    pthread_exit(NULL);
}

int release_resources(int customer_num, int release[], banker _them) {
    if (!isSafe(_them))
        return failure;

    return success;
}

void *customer(void *strut) {

    banker _instance = *(banker *)strut;

    int customer_num = _instance.threads[customer_num].customer_num,
            * customers = _instance.threads[customer_num].process;

    request_resources(customer_num, customers, _instance);
    release_resources(customer_num, customers, _instance);
    return NULL;
}



// (4 pts) overall working program
int main(int argc, char** argv){
// the available amount of each resource
    srand(time(NULL));
    banker _this;
    for (int i = 1; i < argc; ++i)
        _this.available[i-1] = atoi(argv[i]); // copy resources to av.

    int size = argc - 1;

    for(int i = 0; i < size; i++){
        for (int j = 0; j < size; j++) {
            _this.maximum[i][j] = rand() % _this.available[i]; // allcat. random values to max based on values passed to available[]
            _this.allocation[i][j] = rand() % _this.available[i];
        }
    }

    updateAvailable(size, _this);
    
    // TODO: allocation is never set
    // (4 pts) implementation of customer threads
//    while(TRUE){
        isSafe(_this);
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


