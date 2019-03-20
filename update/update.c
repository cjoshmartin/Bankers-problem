//
// Created by Josh Martin on 2019-03-16.
//

#include <printf.h>
#include "update.h"
#include "printer.h"

int isGreaterThenZero(int val) {
    if (val < 0) {
        printf("VALUE IS INVALID, JOSH! CHECK YOUR CODE HOMIE!");
        return 0;
    }

    return val;
}

void updateAvailable(int n, banker * _them) {
        for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
             _them->available[i] += _them->allocation[n][i]; // TODO this is wrong
        }
        print_available();
    }

void updateNeed(banker _them) {
void updateNeed(banker * _them) {
    while (i < NUMBER_OF_CUSTOMERS ){
        while(j < NUMBER_OF_RESOURCES){
            int amount = _them->maximum[i][j] - _them->allocation[i][j];
        }
        i++;
    }
}
