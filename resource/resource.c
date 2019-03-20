//
// Created by Josh Martin on 2019-03-16.
//

#include <printer.h>
#include <update/update.h>
#include "resource.h"
#include "safe/safe.h"


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

banker * _this;

void request_init(banker * _them){
    _this = _them;
}

int request_resources(int customer_num, int request[NUMBER_OF_RESOURCES]) {  // request  = resource allication request
    int isGood = FALSE;
//    pthread_mutex_lock(&mutex);

    int available[NUMBER_OF_RESOURCES],
    need[NUMBER_OF_RESOURCES],
    allocation[NUMBER_OF_RESOURCES];

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++){
        /*
         * Check to see if the request can be granted safely, by pretending it has been granted and then seeing if the
         * resulting state is safe. If so, grant the request, and if not, then the request must wait until its request
         * can be granted safely.The procedure for granting a request ( or pretending to for testing purposes ) is:
         * - Available = Available - Request
         * - Need = Need - Request
         */
        if (request[i] > _this->need[customer_num][i])
            return failure;

       available[i] = _this->available[i] - request[i];
       need[i] = _this->need[customer_num][i] - request[i];
       allocation[i] = _this->allocation[customer_num][i] + request[i];
    }

    isGood = isSafe(available, need, allocation);

    if (!isGood)
        return failure;
    
    allocation_resources(_this, available, need, allocation);
//    pthread_mutex_unlock(&mutex);
    return success;

//    pthread_exit(NULL);
}

int release_resources(int customer_num, int release[NUMBER_OF_RESOURCES]) {

//    pthread_mutex_lock(&mutex);

    int available[NUMBER_OF_RESOURCES],
            need[NUMBER_OF_RESOURCES],
            allocation[NUMBER_OF_RESOURCES];

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++){
        available[i] = _this->available[i] + release[i];
        need[i] = _this->need[customer_num][i] + release[i];
        allocation[i] = _this->allocation[customer_num][i] - release[i];
    }

    if (!isSafe(available, need, allocation))
        return failure;

    free_resources(_this, available, need, allocation);
//    pthread_mutex_unlock(&mutex);
    return success;
}

void * request_resources_process(void *args){
    print_reqest();
   return (void *)request_resources(_this->resource_data.request_n, _this->resource_data.request);
}

void * release_resources_process(void *args){
    print_release();
    return (void *)release_resources(_this->resource_data.release_n, _this->resource_data.release);
}

