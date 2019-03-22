
**Course:** CSCI 403 - Operating Systems

**Name:** Josh Martin

**HW:** 4

**Date**: 3/21/2019

# Introduction

In this project I will implement the Banker’s problem described in Chapter 7 of Ir book (p345/346). Use the Pthreads library and the VM that I built in HMW 1 to complete this project.

# Methodology

## Main

```c
void init(banker *_them) {
    int size_i = NUMBER_OF_CUSTOMERS,
            size_j = NUMBER_OF_RESOURCES;

    srand(time(NULL));

    for(int i = 0; i < size_i; i++){
        for (int j = 0; j < size_j; j++) {
            _them->maximum[i][j] = getRandomResource(_them->available[i] - 1) + 1;
            _them->allocation[i][j] = 0;
            _them->need[i][j] = 0;
        }
    }
    printer_init(_them);
    request_init(_them);
    printf("\nINITAL STATE OF MACHINE:");
    print_all();
    updateNeed(_them);
    printf("\n");
    print_need();
}

void getThreaded(banker * _this) {

    for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i) {
        pthread_create(
                &((*_this).customers[i]), // thread selected
                NULL, // ??
                customer, // function to send the resource_data to
                NULL // data being sent
        );
    }

    for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i) {
        pthread_join(
                ((*_this).customers[i]),
                NULL // return value from join
        );
    }

}

// (4 pts) overall working program
int main(int argc, char** argv){

// the available amount of each resource
    banker * _this = (banker *) (malloc(sizeof(banker)));

    for ( int i = 1; i < argc; ++i) {
        int resource = atoi(argv[i]);
        int index = i - 1;
        _this->available[index] = resource;
        _this->orginal[index] = resource;
    } // copy resources to av.

    init(_this);

// (4 pts) implementation of customer resource_data
    while(TRUE){
            getThreaded(_this);
    } // end of while loop

    free(_this);
    return 0;
}
```

## Header Files

```c
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
//
// Created by Josh Martin on 2019-03-16.
//

#ifndef H4_GENERAL_H
#define H4_GENERAL_H

#define NUMBER_OF_CUSTOMERS 5 // `n`
#define NUMBER_OF_RESOURCES 3 // `m`

#define TRUE 1
#define FALSE 0

#endif //H4_GENERAL_H

```


## Request/Release Algorithms

```c
//
// Created by Josh Martin on 2019-03-16.
//

#include "../printer/printer.h"
#include "../update/update.h"
#include "../utils/utils.h"
#include <stdio.h>
#include "resource.h"
#include "../safe/safe.h"


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

banker * _this;

void request_init(banker * _them){
    _this = _them;
}

int request_resources(int customer_num, int request[NUMBER_OF_RESOURCES]) { 
    int isGood = FALSE;

    int available[NUMBER_OF_RESOURCES],
    need[NUMBER_OF_RESOURCES],
    allocation[NUMBER_OF_RESOURCES];

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++){
        if (request[i] > _this->need[customer_num][i]) {
            printf("\n\nERROR: request[%d] = %d > _this->need[%d][%d]= %d\n\n", 
            i, request[i], customer_num, i, _this->need[customer_num][i]);
            return failure;
        }

       available[i] = _this->available[i] - request[i];

       if (available[i] < 0) {
           printf("\n\nERROR: avaiable[%d] = %d is less then 0\n\n", i, available[i]);
           return failure;
       }

       need[i] = _this->need[customer_num][i] - request[i];
       allocation[i] = _this->allocation[customer_num][i] + request[i];
    }

    isGood = isSafe(available, need, allocation);

    if (!isGood)
        return failure;

    allocation_resources(_this, customer_num, available, need, allocation);

    return success;

}

int release_resources(int customer_num, int release[NUMBER_OF_RESOURCES]) {
    int isGood = FALSE;

    int available[NUMBER_OF_RESOURCES],
            need[NUMBER_OF_RESOURCES],
            allocation[NUMBER_OF_RESOURCES];

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++){
        int temp_ava = _this->available[i] + release[i];
        if (temp_ava > _this->orginal[i]) {
            printf("\n\nERROR: temp avaiable[%d] = %d > orginal[%d]= %d\n\n",
            i,temp_ava, i, _this->orginal[i] );
            return failure;
        }

        available[i] = temp_ava;
        need[i] = _this->need[customer_num][i] + release[i];
        allocation[i] = _this->allocation[customer_num][i] - release[i];
        if (allocation[i] < 0)

            printf("\n\nERROR: Allocation would be less then zero\n\n");

            return 0;
    }

    isGood = isSafe(available, need, allocation);

    if (!isGood)
        return failure;

    free_resources(_this, customer_num, available, need, allocation);

    return success;
}

void * customer(void *args){

    int n = getRandomResource(NUMBER_OF_CUSTOMERS),
        is_request = getRandomResource(2),
            a_resource[NUMBER_OF_RESOURCES];
    int output;


    pthread_mutex_lock(&mutex);
    for (int k = 0; k < NUMBER_OF_RESOURCES; ++k) {
        a_resource[k] =  getRandomResource( 
        is_request ? 
        (_this->need[n][k])
        : (_this->allocation[n][k])
        );
    }
    printf("P%d: ", n+1);
    (is_request ? print_request : print_release)(a_resource);
    output = (is_request ? request_resources : release_resources)(n, a_resource);

    if(output == failure) {
        printf("❌: P%d has failed \n\n", n + 1);
        }
        else
        printf("✅: P%d was successful \n\n", n+1 );

    pthread_mutex_unlock(&mutex);

    return (void *)output;
}
```

## Safety Algorthim

```c


//
// Created by Josh Martin on 2019-03-16.
//

#include <stdio.h>
#include <printer/printer.h>
#include "safe.h"
#include "../update/update.h"

int isSafe(
int available[NUMBER_OF_RESOURCES], 
int need[NUMBER_OF_RESOURCES], 
int allocation[NUMBER_OF_RESOURCES]
) {

    int working[NUMBER_OF_RESOURCES],
            j =0;

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++){
        working[i]= available[j];
    }

    int found = FALSE;
    printf("\n\n");
    _print_lines(50);
    printf("Is Safe Check:\n");
    _print_lines(50);
    printf("NeeD :\n");
    _printer_n(need);
    printf("Allocation\n");
    _printer_n(allocation);
    printf("Available\n");
    _printer_n(available);
    _print_lines(50);
    printf("\n");
    _print_lines(50);

    while ( j < NUMBER_OF_RESOURCES && need[j] <= working[j] ) {
        j++;
    } // end of while

    if (j == NUMBER_OF_RESOURCES){
        found = TRUE;

    } // end of if

    return found;
}

```

## Free/Alocate resoucres

```c
//
// Created by Josh Martin on 2019-03-16.
//

#include <stdio.h>
#include <stdlib.h>
#include "update.h"
#include "../printer/printer.h"

int isGreaterThenZero(int val) {
    if (val < 0) {
        printf("VALUE IS INVALID, JOSH! CHECK YOUR CODE HOMIE!");
        return 0;
    }

    return val;
}
void allocation_resources(
banker * _this,int n, 
int available[NUMBER_OF_RESOURCES], int need[NUMBER_OF_RESOURCES], 
int allocation[NUMBER_OF_RESOURCES]
){
    for (int i = 0; i < NUMBER_OF_RESOURCES ; ++i) {
        _this->need[n][i] = need[i];
        _this->available[i] = available[i];
        _this->allocation[n][i] = allocation[i];
    }

    print_all();

}

void free_resources(
banker * _this, 
int n, int available[NUMBER_OF_RESOURCES], 
int need[NUMBER_OF_RESOURCES], 
int allocation[NUMBER_OF_RESOURCES]
){
    for (int i = 0; i < NUMBER_OF_RESOURCES ; ++i) {
        _this->need[n][i] = need[i];
        _this->available[i] = available[i];
        _this->allocation[n][i] = allocation[i];
    }

    print_all();

}

void updateNeed(banker * _them) {
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++){
        for (int j =0; j < NUMBER_OF_RESOURCES; j++) {
            int amount = _them->maximum[i][j] - _them->allocation[i][j];
            _them->need[i][j] = isGreaterThenZero(amount);
        }
    }
}

```

## Utils

```c


//
// Created by Josh Martin on 2019-03-20.
//

#include "utils.h"
#include <stdlib.h>
#include "../bankers_struct.h"

int getRandomResource(int val) {
    int ran = rand();
    if (val < 1)
        return 0;

    int output = ran % val;
    return output;
}
```


# Results

<!--Indicate whether the request was successful or denied In Ir report show an example of a denied request and a granted request and explain the results. Why was the request denied or granted.-->

```
./a.out 10 5 7

INITAL STATE OF MACHINE:
--------------------------------------------------
Available system resources are:
    A  B  C
    10  5  7
MAXIMUM RESOURCES:
    A  B  C
P1  9  9  9
P2  3  1  1
P3  4  4  2
P4  1  6  1
P5  3  2  4
ALLOCATED RESOURCES:
    A  B  C
P1  0  0  0
P2  0  0  0
P3  0  0  0
P4  0  0  0
P5  0  0  0
NEED, UPDATED:
    A  B  C
P1  0  0  0
P2  0  0  0
P3  0  0  0
P4  0  0  0
P5  0  0  0
--------------------------------------------------

NEED, UPDATED:
    A  B  C
P1  9  9  9
P2  3  1  1
P3  4  4  2
P4  1  6  1
P5  3  2  4

P4: REQUESTING RESOURCES ARRAY:
--------------------------------------------------
    A  B  C
     0  3  0
--------------------------------------------------


--------------------------------------------------
Is Safe Check:
--------------------------------------------------
NeeD :
    A  B  C
     1  3  1
Allocation
    A  B  C
     0  3  0
Available
    A  B  C
    10  2  7
--------------------------------------------------

--------------------------------------------------

--------------------------------------------------
Available system resources are:
    A  B  C
    10  2  7
MAXIMUM RESOURCES:
    A  B  C
P1  9  9  9
P2  3  1  1
P3  4  4  2
P4  1  6  1
P5  3  2  4
ALLOCATED RESOURCES:
    A  B  C
P1  0  0  0
P2  0  0  0
P3  0  0  0
P4  0  3  0
P5  0  0  0
NEED, UPDATED:
    A  B  C
P1  9  9  9
P2  3  1  1
P3  4  4  2
P4  1  3  1
P5  3  2  4
--------------------------------------------------
✅: P4 was successful

P3: REQUESTING RESOURCES ARRAY:
--------------------------------------------------
    A  B  C
     2  3  0
--------------------------------------------------

ERROR: avaiable[1] = -1 is less then 0

❌: P3 has failed


```

# Summary

# Appendix

## References


## Printer Code

```c
#include <stdio.h>
#include "printer.h"

#define Number_of_lines 50
banker * _this;

void _print_title(int size){

    printf("%2c", ' ');

    for (int j = 0; j < size; ++j) {
        char title_letter = 65 + j;
        printf("%3c", title_letter);
    }

    printf("\n");
}

void _print_lines(int size){
    for (int i = 0; i <size ; ++i) {
        printf("-");
    }
    printf("\n");
}

void _printer_n(int arr[NUMBER_OF_RESOURCES]){
    int size_i = NUMBER_OF_RESOURCES;

    _print_title(size_i);
    printf("%3c", ' ');

    for (int i = 0; i < size_i; ++i)
        printf("%3d", arr[i]);

    printf("\n");

}

void _printer_nXm(int arr[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]) {

    int size_i = NUMBER_OF_CUSTOMERS,
            size_j = NUMBER_OF_RESOURCES;

    _print_title(size_j);

    for (int i = 0; i < size_i; ++i) {
        printf("P%d", i+1);
        for (int j = 0; j < size_j; ++j)
            printf("%3d", arr[i][j] );

        printf("\n");
    }
}

void printer_init(banker * them) {
    _this = them;
}

void print_available(){
    printf("Available system resources are:\n");
    _printer_n(_this->available);
}

void print_request(int request [NUMBER_OF_RESOURCES]) {
    printf("REQUESTING RESOURCES ARRAY:\n");
    _print_lines(Number_of_lines);
    _printer_n(request);
    _print_lines(Number_of_lines);
}

void print_release(int release[NUMBER_OF_RESOURCES]) {
    printf("RELEASING RESOURCES ARRAY:\n");
    _print_lines(Number_of_lines);
    _printer_n(release);
    _print_lines(Number_of_lines);
}

void print_maximum() {
    printf("MAXIMUM RESOURCES:\n");
    _printer_nXm(_this->maximum);
}

void print_allocation(){
    printf("ALLOCATED RESOURCES:\n");
    _printer_nXm(_this->allocation);
}

void print_need() {
    printf("NEED, UPDATED:\n");
    _printer_nXm(_this->need);
}

void print_all(){
    printf("\n");
    _print_lines(Number_of_lines);
    print_available();
    print_maximum();
    print_allocation();
    print_need();
    _print_lines(Number_of_lines);
}
```
