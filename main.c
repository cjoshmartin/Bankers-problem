#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <pthread.h>
#include <resource/resource.h>
#include <update/update.h>

#include "general.h"
#include "bankers_struct.h"
#include "utils/utils.h"
#include "printer/printer.h"

void init(banker *_them) {
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


