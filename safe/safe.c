//
// Created by Josh Martin on 2019-03-16.
//

#include <stdio.h>
#include <printer/printer.h>
#include "safe.h"
#include "../update/update.h"

int isSafe(int available[NUMBER_OF_RESOURCES], int need[NUMBER_OF_RESOURCES], int allocation[NUMBER_OF_RESOURCES]) {

    int working[NUMBER_OF_RESOURCES],
            j =0;

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++){
        working[i]= available[j];
    }

    int found = FALSE;
    printf("\n\n");
    _print_lines(50);
    printf("Is Safe Check:\n");
    _print_lines(50);
    printf("NeeD :\n");
    _printer_n(need);
    printf("Allocation\n");
    _printer_n(allocation);
    printf("Available\n");
    _printer_n(available);
    _print_lines(50);
    printf("\n");
    _print_lines(50);

    while ( j < NUMBER_OF_RESOURCES && need[j] <= working[j] ) {
        j++;
    } // end of while

    if (j == NUMBER_OF_RESOURCES){
        found = TRUE;

    } // end of if

    return found;
}
