//
// Created by Josh Martin on 2019-03-16.
//

#include <printf.h>
#include <stdlib.h>
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
            if ((_them->available[i] + _them->allocation[n][i]) > _them->orginal[i]){
                printf("YOU BROKE SOMETHING");
                exit(1);
            }
             _them->available[i] += _them->allocation[n][i]; // TODO this is wrong
        }
        print_available();
    }


void updateNeed(banker * _them) {
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++){
        for (int j =0; j < NUMBER_OF_RESOURCES; j++) {
            int amount = _them->maximum[i][j] - _them->allocation[i][j];
            _them->need[i][j] = isGreaterThenZero(amount);
        }
    }
}
