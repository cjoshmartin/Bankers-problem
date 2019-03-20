//
// Created by Josh Martin on 2019-03-16.
//

#ifndef H4_STRUCTS_H
#define H4_STRUCTS_H

#include <pthread.h>
#include "general.h"

//#define NUMBER_OF_CUSTOMERS 5 // `n`
//#define NUMBER_OF_RESOURCES 3 // `m`

typedef struct banker_resources {
    int available[NUMBER_OF_RESOURCES];
    int orginal[NUMBER_OF_RESOURCES]; // Used for check if available has hit its max
    // the maximum demand of each customer
    int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    // the amount of currently allocated to each customer
    int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    pthread_t customers[NUMBER_OF_CUSTOMERS];
} banker;

#endif //H4_STRUCTS_H
