//
// Created by Josh Martin on 2019-03-16.
//

#include "resource.h"
#include "safe/safe.h"


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int request_resources(int customer_num, int *request, banker _them) {

    if (!isSafe(_them))
        return failure;

    for (int i = 0; i < NUMBER_OF_CUSTOMERS ; i++){
        for (int j = 0; j < NUMBER_OF_RESOURCES ; ++j) {
            if ( request[i] > _them.need[i][j])
                return failure;
        }
    }

    while (request[customer_num] > _them.available[customer_num]) {//TODO: Look at last TODO LOL
        pthread_mutex_lock(&mutex);
    }
    pthread_mutex_unlock(&mutex);

    // TODO

    /*
     * Check to see if the request can be granted safely, by pretending it has been granted and then seeing if the
     * resulting state is safe. If so, grant the request, and if not, then the process must wait until its request
     * can be granted safely.The procedure for granting a request ( or pretending to for testing purposes ) is:
     * - Available = Available - Request
     * - Allocation = Allocation + Request
     * - Need = Need - Request
     */

    _them.available[customer_num]  -= request[customer_num];

    for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i) {
        _them.allocation[customer_num][i] += request[customer_num]; // TODO: maybe is wrong
        _them.need[customer_num][i] -= request[i];
    }

    return success;

//    pthread_exit(NULL);
}

int release_resources(int customer_num, int *release, banker _them) {
    if (!isSafe(_them))
        return failure;

    return success;
}

void *customer(void *strut) {

    banker _instance = *(banker *)strut;

    int customer_num = _instance.threads[customer_num].customer_num,
            * customers = _instance.threads[customer_num].process;

    request_resources(customer_num, customers, _instance);
    release_resources(customer_num, customers, _instance);
    return NULL;
}

