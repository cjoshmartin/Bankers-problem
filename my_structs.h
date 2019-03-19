//
// Created by Josh Martin on 2019-03-16.
//

#ifndef H4_STRUCTS_H
#define H4_STRUCTS_H

#include <pthread.h>
#include "general.h"
//#define NUMBER_OF_CUSTOMERS 5 // `n`
//#define NUMBER_OF_RESOURCES 3 // `m`

struct thread
{
    int customer_num;
    int * process; // same for all
};

typedef struct banker_resourse {
    int available[NUMBER_OF_CUSTOMERS];
    // the maximum demand of each customer
    int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    // the amount of currently allocated to each customer
    int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    pthread_t customers[NUMBER_OF_CUSTOMERS];
    struct thread threads[NUMBER_OF_CUSTOMERS];
} banker;

#endif //H4_STRUCTS_H
