//
// Created by Josh Martin on 2019-03-16.
//

#include <stdio.h>
#include "safe.h"
#include "../update/update.h"

int isSafe(int available[NUMBER_OF_RESOURCES], int need[NUMBER_OF_RESOURCES], int allocation[NUMBER_OF_RESOURCES]) {

    int working[NUMBER_OF_RESOURCES],
            j =0;

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++){
        working[i]= available[j];
    }

    int found = FALSE;
    while ( j < NUMBER_OF_RESOURCES && need[j] < working[j] ) {
        j++;
    } // end of while

    if (j == NUMBER_OF_RESOURCES){
        for(int k= 0; k < NUMBER_OF_RESOURCES; k++)
            working[k] += allocation[k];
        found = TRUE;

    } // end of if

    return found;
}
