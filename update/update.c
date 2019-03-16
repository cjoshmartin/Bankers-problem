//
// Created by Josh Martin on 2019-03-16.
//

#include <printf.h>
#include "update.h"

int isGreaterThenZero(int val) {
    return val > 0 ? val : 0;
}

void calculateANeed(int i, int j, banker _them) {
    int amount = _them.maximum[i][j] - _them.allocation[i][j];
    _them.need[i][j] = isGreaterThenZero(amount);
}

void updateAvailable(int size, banker _them) {
    for (int j =0; j < size; j++){
        int sum = 0;
        for (int i = 0; i < size; ++i) {
            sum += _them.allocation[i][j];
        }
        _them.available[j] += sum;
    }

    printf("New Available: ");

    for (int i = 0; i < size; ++i) {
        printf("%d ", _them.available[size]);
    }
}

void updateNeed(banker _them) {
    int i =0 , j= 0;
    while (i < NUMBER_OF_CUSTOMERS ){
        while(j < NUMBER_OF_RESOURCES){
            calculateANeed(i,j++, _them);
        }
        i++;
    }
}
