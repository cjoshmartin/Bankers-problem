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


