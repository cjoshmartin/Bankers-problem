//
// Created by Josh Martin on 2019-03-16.
//

#include <printer.h>
#include <update/update.h>
#include <utils.h>
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
        if (request[i] > _this->need[customer_num][i])
            return failure;

       available[i] = _this->available[i] - request[i];
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
        if (temp_ava > _this->orginal[i])
            return  failure;

        available[i] = temp_ava;
        need[i] = _this->need[customer_num][i] + release[i];
        allocation[i] = _this->allocation[customer_num][i] - release[i];
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
    void *output;


    pthread_mutex_lock(&mutex);
    for (int k = 0; k < NUMBER_OF_RESOURCES; ++k) {
        a_resource[k] =  getRandomResource(  is_request ? (_this->need[n][k]) : (_this->allocation[n][k]) );
    }

    output = (void *) (is_request ? request_resources : release_resources)(n, a_resource);
    (is_request ? print_request : print_release)(a_resource);

    pthread_mutex_unlock(&mutex);
    pthread_exit(output);

    return output;
}