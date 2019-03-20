//
// Created by Josh Martin on 2019-03-16.
//

#include <printf.h>
#include <stdlib.h>
#include "update.h"
#include "printer/printer.h"

int isGreaterThenZero(int val) {
    if (val < 0) {
        printf("VALUE IS INVALID, JOSH! CHECK YOUR CODE HOMIE!");
        return 0;
    }

    return val;
}
void allocation_resources(banker * _this,int n, int available[NUMBER_OF_RESOURCES], int need[NUMBER_OF_RESOURCES], int allocation[NUMBER_OF_RESOURCES]){
    for (int i = 0; i < NUMBER_OF_RESOURCES ; ++i) {
        _this->need[n][i] = need[i];
        _this->available[i] = available[i];
        _this->allocation[n][i] = allocation[i];
    }

    print_all();

}

void free_resources(banker * _this, int n, int available[NUMBER_OF_RESOURCES], int need[NUMBER_OF_RESOURCES], int allocation[NUMBER_OF_RESOURCES]){
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
