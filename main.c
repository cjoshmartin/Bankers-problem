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

    updateAvailable(size_i, _them);
}

// (4 pts) overall working program
int main(int argc, char** argv){

// the available amount of each resource
    banker _this;

    for ( int i = 1; i < argc; ++i)
        _this.available[i-1] = atoi(argv[i]); // copy resources to av.

    init(&_this);


    return 0;
}


// (4 pts) implementation of customer threads
//    while(TRUE){
//isSafe(_this);
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

