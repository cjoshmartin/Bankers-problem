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

int getRandomResource(int val) {
    int ran = rand();
    if (val < 1)
        return 0;

    int output = ran % val;
    return output;
}

void init(banker * _them){
    int size_i = NUMBER_OF_CUSTOMERS,
            size_j = NUMBER_OF_RESOURCES;

    srand(time(NULL));

    for(int i = 0; i < size_i; i++){
        for (int j = 0; j < size_j; j++) {
            _them->maximum[i][j] = getRandomResource(_them->available[i] - 1) + 1; // allcat. random values to max based on values passed to available[]
            _them->allocation[i][j] = 0;
            _them->need[i][j] = 0;
        }
    }
    printer_init(_them);
    request_init(_them);
    print_all();
    updateNeed(_them);
    printf("\n");
    print_need();
}


int iter(int i) { return i < NUMBER_OF_CUSTOMERS ? (++i) : (0); }

void getThreaded(banker *_this, int i) {

    pthread_create(&(*_this).customers[i], // thread selected
                        NULL, // ??
                        request_resources_process, // function to send the resource_data to
                        NULL // data being sent
        );

    pthread_create( &(*_this).customers[iter(i)], // thread selected
                        NULL, // ??
                        release_resources_process, // function to send the resource_data to
                        NULL // data being sent
        );

    pthread_join(
                (*_this).customers[i],
                NULL // return value from join
        );

    pthread_join(
                (*_this).customers[iter(i)],
                NULL // return value from join
        );
}

// (4 pts) overall working program
int main(int argc, char** argv){

// the available amount of each resource
    banker _this;
    int shouldThread = TRUE;

    for ( int i = 1; i < argc; ++i) {
        int resource = atoi(argv[i]);
        int index = i - 1;
        _this.available[index] = resource;
        _this.orginal[index] = resource;
    } // copy resources to av.

    init(&_this);

// (4 pts) implementation of customer resource_data
    int i = 0;
    while(TRUE){
        int n_request = getRandomResource(NUMBER_OF_CUSTOMERS),
        n_release = getRandomResource(NUMBER_OF_CUSTOMERS);

        for (int k = 0; k < NUMBER_OF_RESOURCES; ++k) {
            _this.resource_data.request[k] =  getRandomResource(_this.need[n_request][k]);
            _this.resource_data.release[k] = getRandomResource(_this.allocation[n_release][k]);
        }

        _this.resource_data.request_n = n_request;
        _this.resource_data.release_n = n_release;

        if (shouldThread)
            getThreaded(&_this, i);
        else{
            void * noop;
            request_resources_process(noop);
            release_resources_process(noop);
        }

        i = iter(i);

    } // end of while loop

    return 0;
}


