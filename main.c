#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <pthread.h>

#include "general.h"
#include "my_structs.h"
#include "resource/resource.h"
#include "update/update.h"
#include "safe/safe.h"
#include "printer.h"

void init(banker * _them){
    int size_i = NUMBER_OF_CUSTOMERS,
            size_j = NUMBER_OF_RESOURCES;

    srand(time(NULL));

    for(int i = 0; i < size_i; i++){
        for (int j = 0; j < size_j; j++) {
            if (_them->available[i] > 0)
                _them->maximum[i][j] = (rand() % (_them->available[i] - 1 )) + 1; // allcat. random values to max based on values passed to available[]
            _them->allocation[i][j] = 0;
            _them->need[i][j] = 0;
        }
    }
    printer_init(_them);
    print_all();

    updateNeed(_them);
}

int getRandomResource() { return rand() % NUMBER_OF_CUSTOMERS; }

// (4 pts) overall working program
int main(int argc, char** argv){

// the available amount of each resource
    banker _this;

    for ( int i = 1; i < argc; ++i)
        _this.available[i-1] = atoi(argv[i]); // copy resources to av.

    init(&_this);

// (4 pts) implementation of customer resource_data
    int i = 0;
    while(TRUE){
        int n_request = getRandomResource(),
        n_release = getRandomResource();

        _this.resource_data.customer_num = n_request;

        for (int k = 0; k < NUMBER_OF_RESOURCES; ++k) { // TODO: Should 2d arrays be [][]
            _this.resource_data.request[k] =  rand() % _this.need[n_request][k];
            _this.resource_data.release[k] = rand() % _this.allocation[n_release][k];
        }

        pthread_create( &_this.customers[i], // resource
                        NULL, // ??
                        customer, // function to send the resource_data to
                        &_this.resource_data
        );

        pthread_join(
                _this.customers[n_request],
                NULL // return value from join
        );

        i < NUMBER_OF_CUSTOMERS ? (i++) : (i=0);

    } // end of while loop

    return 0;
}


