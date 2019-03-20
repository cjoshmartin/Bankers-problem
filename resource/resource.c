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
    return success;

}

int release_resources(int customer_num, int release[NUMBER_OF_RESOURCES]) {
    int isGood = FALSE;

    int available[NUMBER_OF_RESOURCES],
            need[NUMBER_OF_RESOURCES],
            allocation[NUMBER_OF_RESOURCES];

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++){
        int temp_ava = _this->available[i] + release[i];
        if (temp_ava > _this->orginal[i])
            return  failure;

        available[i] = temp_ava;
        need[i] = _this->need[customer_num][i] + release[i];
        allocation[i] = _this->allocation[customer_num][i] - release[i];
    }
    isGood = isSafe(available, need, allocation);

    if (!isGood)
        return failure;

    free_resources(_this, available, need, allocation);
    return success;
}

void * request_resources_process(void *args){
    pthread_mutex_lock(&mutex);
    print_reqest();
    void * output= (void *)request_resources(_this->resource_data.request_n, _this->resource_data.request);
    pthread_mutex_unlock(&mutex);
    pthread_exit(output);
   return output;
}

void * release_resources_process(void *args){
    pthread_mutex_lock(&mutex);
    print_release();
    void * output = (void *)release_resources(_this->resource_data.release_n, _this->resource_data.release);
    pthread_mutex_unlock(&mutex);
    pthread_exit(output);
    return  output;
}

